/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class Println_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Println_AST, AST_Tree);

    const char* externalName () {
	return "println";
    }

};

NODE_FACTORY (Println_AST, PRINTLN);

/** Print AST Tree for print, inherited from Println_AST. */
class Print_AST : public Println_AST {
protected:
    NODE_CONSTRUCTORS(Print_AST, Println_AST);
};

NODE_FACTORY(Print_AST, PRINT);

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

/** Return AST Tree for return, inherited from AST_Tree. */
class Return_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Return_AST, AST_Tree);

    // void collectDecls (Decl* enclosing)
    // {
    //     const Environ* env = enclosing->getEnviron();
    //     DB(env);
    //     for_each_child_var (c, this) {
    //         if (env->find(c->as_string()) != NULL) {
    //             c->collectDecls (enclosing);
    //         } else {
    //             error(loc(), "return expr declaration not found.");
    //         }
    //     } end_for;
    // }

    // /* DEBUGGING */

    // void
    // DB (const Environ* env)
    // {
    //     if (env == NULL) {
    //         fprintf (stderr, "NULL\n");
    //     } else {
    //         const char* label;
    //         label = "Immediate";
    //         while (env != NULL) {
    //             const Decl_Vector& members = env->get_members ();
    //             fprintf (stderr, "%s:\n", label);
    //             for (size_t i = 0; i < members.size (); i += 1) {
    //                 fprintf (stderr, "   %s @%p\n", members[i]->getName ().c_str (),
    //                          members[i]);
    //             }
    //             env = env->get_enclosure ();
    //             label = "Enclosed by";
    //         }
    //     }
    // }
};

NODE_FACTORY(Return_AST, RETURN);

/** Break AST Tree for break, inherited from AST_Tree. */
class Break_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Break_AST, AST_Tree);
};

NODE_FACTORY(Break_AST, BREAK);

/** Continue AST Tree for continue, inherited from AST_Tree. */
class Continue_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Continue_AST, AST_Tree);
};

NODE_FACTORY(Continue_AST, CONTINUE);

/** If AST Tree for if, inherited from AST_Tree. */
class If_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(If_AST, AST_Tree);

    /** Throw an erro if the first child's type(condition) is not a boolDecl. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes (context, subst);
        if (!unify(child(0)->getType(), boolDecl->asType(), subst)) {
            error(loc(), "If expresion is not bool");
            throw logic_error("");
        }
    }
};

NODE_FACTORY(If_AST, IF);

/** While AST Tree for while, inherited from AST_Tree. */
class While_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(While_AST, AST_Tree);

    /** Throw an erro if the first child's type(condition) is not a boolDecl. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes(context, subst);

        if (!unify(child(0)->getType(), boolDecl->asType(), subst)) {
            error(loc(), "While expresion is not bool");
            throw logic_error("");
        }
    }    
};

NODE_FACTORY(While_AST, WHILE);

/** For AST Tree for for, inherited from AST_Tree. */
class For_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(For_AST, AST_Tree);

    /** First child would a target. Then for every child, recursively call
     *  collectDecls to ENCLOSING. Finally addTargetDecls from target to ENCLOSING.*/
    void collectDecls (Decl* enclosing) {
        AST_Ptr target = child(0);
        for (size_t i = 1; i < arity (); i += 1) {
            child (i)->collectDecls (enclosing);
        }
        target->addTargetDecls (enclosing);
    }

    /** For T in E. Typechecking on E's type $a and T's type $b.
     *  Do nothing if $a is one of list($b), range or str
     *  and $a is list($b)
     *  or $a is range and $b is int
     *  or $a and $b are str. Otherwise throw an error. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes(context, subst);

        Type_Ptr t_type = child(0)->getType();
        Type_Ptr e_type = child(1)->getType();

        // E: $a, T: $b where $a is one of list($b)
        if ((unify(e_type, listDecl->asType(1, &t_type),subst)) ||
            (   unify(e_type, rangeDecl->asType(),subst) &&
                unify(t_type, intDecl->asType(), subst)       ) ||
            (   unify(e_type, strDecl->asType(), subst)  &&
                unify(t_type, strDecl->asType(), subst)       ))
        {
            return;
        } else {
            error(loc(), "For statements variable doesn't have proper types");
        }
    }
};

NODE_FACTORY(For_AST, FOR);

/** Def AST Tree for def, inherited from AST_Tree.  */
class Def_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Def_AST, AST_Tree);

    /** Recursively can resolveSimpleIds within the scope of first child'decl environment,
     *  for every child variable. */
    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        AST_Ptr id = child(0);
        const Environ* func_env = id->getDecl()->getEnviron();
        for_each_child_var (c, this) {
            c = c->resolveSimpleIds(func_env);
        } end_for;
        return this;
    }

    /** Add declaration to Id if it can be added DefDecl. Then recursively
     *  can it for every child. Throw an error if the child's name equal to
     *  the Id's name.  */
    void collectDecls (Decl* enclosing)
    {
        AST_Ptr id = child(0);
        Decl* decl = enclosing->addDefDecl(id);
        if (decl != NULL) {
            id->addDecl(decl);
            for_each_child(c, this) {
                if (c->arity() > 1 && c->oper()->syntax() == DEF
                    && id->as_string() == c->child(0)->as_string()) {
                    error(loc(), "child name can't be equal to the Def!");
                }
                c->collectDecls(decl);
            } end_for;
        }
    }
};

NODE_FACTORY(Def_AST, DEF);

/** AST Tree for Method definition, inherited from the Def_AST */
class Method_AST : public Def_AST {
protected:
    NODE_CONSTRUCTORS(Method_AST, Def_AST);

    /** First check whether the first parameter is "self". If not, throw an error.
     *  Otherwise, add declaration to Id if it can be added DefDecl. Then recursively
     *  can it for every child. Throw an error if the child's name equal to
     *  the Id's name.  */
    void collectDecls (Decl* enclosing)
    {
        if ((std::string) child(1)->child(0)->child(0)->as_string().c_str() == (std::string) "self") {
            AST_Ptr id = child(0);
            Decl* decl = enclosing->addDefDecl(id);
            if (decl != NULL) {
                id->addDecl(decl);
                for_each_child(c, this) {
                    if (c->arity() > 1 && c->oper()->syntax() == DEF
                        && id->as_string() == c->child(0)->as_string()) {
                        error(loc(), "child name can't be equal to the Def!");
                    }
                    c->collectDecls(decl);
                } end_for;
            }
        } else {
            error(loc(), "first parameter should be a self in a class method!");
        }
    }
};

NODE_FACTORY(Method_AST, METHOD);

/** Formalslist AST for Formals in grammar rule, inherited from AST_Tree. */
class Formalslist_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Formalslist_AST, AST_Tree);

    /** Add declaration to every child if it can be add Paramdecl, divided into
     *  two seperate scenarios, either child is a TYPED_ID or otherwise. */
    void collectDecls (Decl* enclosing)
    {
        int count = 0;
        for_each_child(c, this) {
            Decl* decl;
            if (c->oper()->syntax() == TYPED_ID) {
                decl = makeParamDecl(c->getId()->as_string(), 
                                        enclosing, 
                                        count, 
                                        c->child(1));
                c->getId()->addDecl(decl);
            } 
            else {
                decl = makeParamDecl(c->as_string(),
                                    enclosing,
                                    count,
                                    Type::makeVar());
                c->addDecl(decl);
            }
            count++;
            enclosing->addMember(decl);
        } end_for;
    }

};

NODE_FACTORY(Formalslist_AST, FORMALS_LIST);

/** Class AST Tree for class, inherited from AST_Tree. */
class Class_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS(Class_AST, AST_Tree);

    /** Recursively can resolveSimpleIds within the scope of first child'decl environment,
     *  for every child variable. */
    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        AST_Ptr id = child(0);
        const Environ* class_env = id->getDecl()->getEnviron();
        for_each_child_var (c, this){
            c = c->resolveSimpleIds (class_env);
        } end_for;
        return this;
    }

    /** Add declarations that result from occurrences of type variables
     *  in type attributions to each child variable of the second child. */
    void collectTypeVarDecls (Decl* enclosing){
        AST_Ptr params = child(1);
        for_each_child_var(param, params) {
            AST_Ptr paramId = param->child(0);
            Decl* paramType = makeTypeVarDecl(paramId->as_string(), param);
            param->addDecl(paramType);
        } end_for;
    }

    /** If the class name comes from the prelude, then construct class declaration to
     *  specific decl that declared in decls.cc, otherwise add decl to Id if the decl
     *  is not NULL and Id's name hasn't been declared in the scope of ENCLOSING. */
    void collectDecls (Decl* enclosing) {
        
        AST_Ptr id = child(0);
        AST_Ptr params = child(1);
        const gcstring name = id->as_string();
        if (name == "str") {
            Decl* decl = makeClassDecl(name, consTree(TYPE_FORMALS_LIST));
            strDecl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "int") {
            Decl* decl = makeClassDecl(name, consTree(TYPE_FORMALS_LIST));
            intDecl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "bool") {
            Decl* decl = makeClassDecl(name, params);
            boolDecl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "range") {
            Decl* decl = makeClassDecl(name, params);
            rangeDecl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        // need inline substitution
        else if (name == "list") {
            Decl* decl = makeClassDecl(name, params);
            collectTypeVarDecls(decl);
            listDecl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "dict") {
            Decl* decl = makeClassDecl(name, params);
            collectTypeVarDecls(decl);
            dictDecl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "tuple0") {
            Decl* decl = makeClassDecl(name, params);
            tuple0Decl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "tuple1") {
            Decl* decl = makeClassDecl(name, params);
            collectTypeVarDecls(decl);
            tuple1Decl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "tuple2"){
            Decl* decl = makeClassDecl(name, params);
            collectTypeVarDecls(decl);
            tuple2Decl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        else if (name == "tuple3"){
            Decl* decl = makeClassDecl(name, params);
            collectTypeVarDecls(decl);
            tuple3Decl = decl;
            id->addDecl(decl);
            classes->define(decl);
            enclosing->addMember(decl);
        }
        /* END */
        
        else {
            const Environ* env = enclosing->getEnviron();
            if (env->find_immediate(name) != NULL) {
                error(loc(), "This name has been declared in this scope!");
            }
            Decl* decl = enclosing->addClassDecl(this);
            collectTypeVarDecls(decl);
            if (decl != NULL) {
                id->addDecl(decl);
                for_each_child (c, this) {
                    if (c->arity() > 1 && c->oper()->syntax() == METHOD && name == c->child(0)->as_string()) {
                        error(loc(), "child name can't be equal to the Class!");
                    }
                    c->collectDecls (decl);
                } end_for;
            }
        }
    }
};

NODE_FACTORY(Class_AST, CLASS);

/** Block AST Tree for break, inherited from AST_Tree. */
class Block_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Block_AST, AST_Tree);
};

NODE_FACTORY(Block_AST, BLOCK);

/** Native AST Tree for native, inherited from AST_Tree. */
class Native_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Native_AST, AST_Tree);
};

NODE_FACTORY(Native_AST, NATIVE);

/** TypeFormalsList AST Tree for TypeFormals from grammar rule, inherited from AST_Tree.*/
class TypeFormalsList_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(TypeFormalsList_AST, AST_Tree);

    // void collectDecls(Decl* enclosing)
    // {
    //     //fprintf(stderr, "collectDecls TypeFormalsList\n");
    //     for (unsigned int count = 0; count < this -> arity(); count++) {
    //         AST_Ptr c = child(count);
    //         const Environ* env = enclosing->getEnviron();
    //         const gcstring name = c->as_string();
    //         if (env->find(name) != NULL) {
    //             fprintf(stderr, "This type has been defined previously. \n");
    //         } else {
    //             Decl* temp = makeTypeVarDecl(name, c);
    //             c->addDecl(temp);
    //         }
    //     }
    // }

};

NODE_FACTORY(TypeFormalsList_AST, TYPE_FORMALS_LIST);

/** TypedID AST Tree for TypedId from the grammar rule, inherited from Typed_Tree. */
class TypedID_AST : public Typed_Tree {
    
protected:
    NODE_CONSTRUCTORS(TypedID_AST, Typed_Tree);

    AST_Ptr getId()
    {
        return child(0);
    }

    /** If the Id could be add as Variable Declaration, then set my type to this delcation
     *  and add it to the ID. */
    void addTargetDecls (Decl* enclosing) {
        AST_Ptr id = getId();
        Decl* decl = enclosing->addVarDecl(id);
        if (decl != NULL) {
            decl->setType((Type_Ptr)child(1));
            id->addDecl(decl);
        }
    }

    /** Return the second child as a Type_Ptr. */
    Type_Ptr getType()
    {
        return (Type_Ptr) child(1);
    }

    /** Set type to my type iff it is a TYPE node with an arity of 2. */
    void resolveTypes (Decl* context, Unifier& subst)
    {
        if (arity() == 2 && child(1)->oper()->syntax() == TYPE){
            setType(getType(), subst);
        }
    }

};

NODE_FACTORY(TypedID_AST, TYPED_ID);

/** Assign AST Tree for assign, inherited from Typed_Tree. */
class Assign_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(Assign_AST, Typed_Tree);

    /** Add target declarations from first child to ENCLOSING.
     *  Add declarations from the second child to ENCLOSING. */
    void collectDecls (Decl* enclosing)
    {
        child(0)->addTargetDecls(enclosing);
        child(1)->collectDecls(enclosing);
    }

    /** Typechecking on first child and second child. Set the type to it
     *  if types for these two children can be unified, otherwise throw an error. */
    void resolveTypes (Decl* context, Unifier& subst)
    {
        AST::resolveTypes (context, subst);

        if (unify(child(0)->getType(), child(1)->getType(),subst)) {
            setType(child(0)->getType(), subst);
        } else {
            error(loc(), "Assign left and right type inconsistency");
            throw logic_error("");
        }
    }
};

NODE_FACTORY(Assign_AST, ASSIGN);
