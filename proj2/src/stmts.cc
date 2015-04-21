/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/***** PRINT *****/

/**       */
class Print_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Print_AST, AST_Tree);

};

NODE_FACTORY (Print_AST, PRINT);




/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class Println_AST : public Print_AST {
protected:

    NODE_CONSTRUCTORS (Println_AST, Print_AST);

    const char* externalName () {
	return "println";
    }

};

NODE_FACTORY (Println_AST, PRINTLN);

/***** STMT_LIST *****/

/** A list of statements. */
class StmtList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (StmtList_AST, AST_Tree);

    AST_Ptr doOuterSemantics () {
        for_each_child_var (c, this) {
            c = c->doOuterSemantics ();
        } end_for;
        return this;
    }

};

NODE_FACTORY (StmtList_AST, STMT_LIST);


/***** DEF *****/

/** def ID(...): ... */
class Def_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Def_AST, AST_Tree);

    Decl* getDecl (int k = 0) {
        return child (0)->getDecl ();
    }

    AST_Ptr getId () {
        return child (0);
    }

    void freezeDecls (bool frozen) {
        Decl* me = getDecl ();
        if (me != NULL)
            me->setFrozen (frozen);
        child (3)->freezeDecls (frozen);
    }

    void collectDecls (Decl* enclosing) {
        AST_Ptr id = child (0);
        AST_Ptr params = child (1);
        AST_Ptr returnType = child (2);
        gcstring name = id->as_string ();
        Decl* me = enclosing->addDefDecl(child(0), params->arity ());
        id->addDecl (me);
        params->collectDecls (me);
        params->collectTypeVarDecls (me);
        returnType->collectTypeVarDecls (me);
        PASSDOWN (this, collectDecls (me), 3);
    }

    AST_Ptr resolveSimpleIds (const Environ* env) {
        PASSDOWN (this, resolveSimpleIds (getDecl ()->getEnviron ()), 3);
        return this;
    }

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        Decl* me = getDecl ();
        Type_Ptr funcType = me->getType ();
        Type_Ptr returnType = child (2)->asType ();
        AST_Ptr formals = child (1);
        getId ()->resolveTypes (me, subst, resolver);
        formals->resolveTypes (me, subst, resolver);
        if (!unify (funcType->returnType (), returnType, subst))
            error (this, "inconsistent return type");
        for (size_t i = 0; i < formals->arity (); i += 1) {
            if (!unify (formals->child (i)->getType (),
                        funcType->paramType (i), subst)) {
                error (this, "inconsistent parameter type");
            }
        }
        PASSDOWN (this, resolveTypes (me, subst, resolver), 3);
        assert ((int) me->getType ()->binding ()->numParams () ==
                (int) formals->arity ());
    }

};

NODE_FACTORY (Def_AST, DEF);

/***** METHOD *****/

/**  def ID(...): ... (in class)     */
class Method_AST : public Def_AST {
protected:

    NODE_CONSTRUCTORS (Method_AST, Def_AST);

    void collectDecls (Decl* enclosing) {
        AST_Ptr params = child (1);
        if (params->arity () == 0) {
            error (this, "method must have at least one parameter");
            params->insert (0, make_id ("__self__", loc ()));
        }
        Def_AST::collectDecls (enclosing);
    }


};

NODE_FACTORY (Method_AST, METHOD);


    

/***** FORMALS_LIST *****/

/** ... (E1, ...)  */
class FormalsList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (FormalsList_AST, AST_Tree);

    void collectDecls (Decl* enclosing) {
        for_each_child (c, this) {
            AST_Ptr id = c->getId ();
            gcstring name = id->as_string ();
            c->addDecl (enclosing->addParamDecl(id, c_i_));
        } end_for;

        for_each_child (c, this) {
            c->collectTypeVarDecls (enclosing);
        } end_for;
    }

};

NODE_FACTORY (FormalsList_AST, FORMALS_LIST);





/***** CLASS *****/

/** class ID of [...]: ...  */
class Class_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Class_AST, AST_Tree);

    Decl* getDecl (int k = 0) {
        return child (0)->getDecl ();
    }

    void collectDecls (Decl* enclosing) {
        AST_Ptr id = child (0);
        gcstring name = id->as_string ();
        AST_Ptr params = child (1);
        const Environ* env = enclosing->getEnviron ();

        Decl* me = makeClassDecl (name, params);

        if (env->find_immediate (name) != NULL) {
            error (id, "attempt to redefine %s", name.c_str ());
        } else {
            enclosing->addMember (me);
        }

        setBuiltinDecl (me);

        id->addDecl (me);
        params->collectDecls (me);
        PASSDOWN(this, collectDecls (me), 2);
    }

    AST_Ptr resolveSimpleIds (const Environ* env) {
        PASSDOWN (this, resolveSimpleIds (getDecl ()->getEnviron ()), 2);
        return this;
    }

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        PASSDOWN (this, resolveTypes (getDecl (), subst, resolver), 2);
    }

private:
};

NODE_FACTORY (Class_AST, CLASS);

/***** TYPE_FORMALS_LIST *****/

/** of [$T, ...]      */
class TypeFormalsList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (TypeFormalsList_AST, AST_Tree);

    void collectDecls (Decl* enclosing) {
        const Environ* env = enclosing->getEnviron ();
        for_each_child (c, this) {
            gcstring name = c->as_string ();
            if (env->find_immediate (name) != NULL) {
                error (c, "duplicate type parameter: %s",
                       name.c_str ());
            } else {
                c->addDecl (enclosing->addTypeVarDecl (c));
            }
        } end_for;
    }

};

NODE_FACTORY (TypeFormalsList_AST, TYPE_FORMALS_LIST);

/***** TYPED_ID *****/

/** ID::TYPE */
class TypedId_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (TypedId_AST, AST_Tree);

    AST_Ptr getId () {
        return child (0);
    }

    Decl* getDecl (int k = 0) {
        return getId ()->getDecl (k);
    }

    Type_Ptr getType () {
        return child (1)->asType ();
    }

    void addTargetDecls (Decl* enclosing) {
        getId ()->addTargetDecls (enclosing);
    }
    
    void collectTypeVarDecls (Decl* enclosing) {
        child (1)->collectTypeVarDecls (enclosing);
    }

    void addDecl (Decl* decl) {
        getId ()->addDecl (decl);
    }

    
    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        getId ()->resolveTypes (context, subst, resolver);
        if (!getId ()->setType (child (1)->asType (), subst))
            error (this, "incompatible type assignment");
    }

};

NODE_FACTORY (TypedId_AST, TYPED_ID);


/***** ASSIGN *****/

/** TARGET(s) = EXPR */
class Assign_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (Assign_AST, Typed_Tree);

    void collectDecls (Decl* enclosing) {
        child(1)->collectDecls (enclosing);
        child(0)->addTargetDecls (enclosing);
    }

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        int errs0 = numErrors ();
        Typed_Tree::resolveTypes (context, subst, resolver);
        if (!unify (child (0)->getType (), child (1)->getType (), subst)
            && errs0 == numErrors ())
            error (this, "type mismatch in assignment");
        if (!setType (child (1)->getType (), subst) && errs0 == numErrors ())
            error (this, "type mismatch in assignment");
    }
    
};

NODE_FACTORY (Assign_AST, ASSIGN);

/***** FOR *****/

/**  for target in exprs: body [ else: body ]     */
class For_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (For_AST, AST_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        int errs0 = numErrors ();
        AST_Tree::resolveTypes (context, subst, resolver);
        if (errs0 != numErrors ())
            return;
        Type_Ptr seqType = child (1)->getType ()->binding ();

        if (seqType->isTypeVariable ()) {
            return;
        }

        Type_Ptr eltType;
        if (unifies (seqType, strDecl->asType ()))
            eltType = strDecl->asType ();
        else if (unifies (seqType, rangeDecl->asType ()))
            eltType = intDecl->asType ();
        else {
            eltType = Type::makeVar ();
            if (!unify (seqType, listDecl->asType (1, eltType), subst))
                error (this, "value cannot be iterated over");
        }
        if (!unify (eltType, child (0)->getType (), subst)) {
            error (this, "for loop target does not match element type");
        } 
    }
        
    void collectDecls (Decl* enclosing) {
        AST_Ptr target = child (0);
        for (size_t i = 1; i < arity (); i += 1)
            child (i)->collectDecls (enclosing);
        target->addTargetDecls (enclosing);
    }

};

NODE_FACTORY (For_AST, FOR);


/***** RETURN *****/

/**  return EXPR */
class Return_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Return_AST, AST_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        AST_Tree::resolveTypes (context, subst, resolver);
        AST_Ptr expr = child (0);
        Type_Ptr returnType = context->getType ()->returnType ();
        if (!unify (returnType, expr->getType (), subst))
            error (this, "inconsistent return type");
    }

};

NODE_FACTORY (Return_AST, RETURN);


/***** IF *****/

/** if COND: STMT else: STMT */
class If_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (If_AST, AST_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        AST_Tree::resolveTypes (context, subst, resolver);
        if (!unify (child (0)->getType (), boolDecl->asType (), subst)) {
            error (child (0), "condition must be boolean");
        }
    }
};

NODE_FACTORY (If_AST, IF);

/***** WHILE *****/

/** while COND: STMT else: STMT */
class While_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (While_AST, AST_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        AST_Tree::resolveTypes (context, subst, resolver);
        if (!unify (child (0)->getType (), boolDecl->asType (), subst)) {
            error (child (0), "condition must be boolean");
        }
    }
};

NODE_FACTORY (While_AST, WHILE);


