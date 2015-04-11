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

/** Print */
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

/** return */
class Return_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Return_AST, AST_Tree);
};

NODE_FACTORY(Return_AST, RETURN);

/** Break */
class Break_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Break_AST, AST_Tree);
};

NODE_FACTORY(Break_AST, BREAK);

/** Continue */
class Continue_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Continue_AST, AST_Tree);
};

NODE_FACTORY(Continue_AST, CONTINUE);

/** If*/
class If_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(If_AST, AST_Tree);

    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes (context, subst);
        if (!unify(child(0)->getType(), boolDecl->asType(), subst)) {
            error(loc(), "If expresion is not bool");
            throw logic_error("");
        }
    }
};

NODE_FACTORY(If_AST, IF);

/** While */
class While_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(While_AST, AST_Tree);

    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes(context, subst);

        if (!unify(child(0)->getType(), boolDecl->asType(), subst)) {
            error(loc(), "While expresion is not bool");
            throw logic_error("");
        }
    }    
};

NODE_FACTORY(While_AST, WHILE);

/** For */
class For_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(For_AST, AST_Tree);

    void collectDecls (Decl* enclosing) {
        AST_Ptr target = child(0);
        for (size_t i = 1; i < arity (); i += 1) {
            child (i)->collectDecls (enclosing);
        }
        target->addTargetDecls (enclosing);

    }
};

NODE_FACTORY(For_AST, FOR);

/** def */
class Def_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Def_AST, AST_Tree);

    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        AST_Ptr id = child(0);
        const Environ* func_env = id->getDecl()->getEnviron();
        for_each_child_var (c, this) {
            c = c->resolveSimpleIds(func_env);
        } end_for;
        return this;
    }

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

/** Method */
class Method_AST : public Def_AST {
protected:
    NODE_CONSTRUCTORS(Method_AST, Def_AST);

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

/** Formalslist*/
class Formalslist_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Formalslist_AST, AST_Tree);

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

/** Class */
class Class_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS(Class_AST, AST_Tree);

    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        AST_Ptr id = child(0);
        const Environ* class_env = id->getDecl()->getEnviron();
        for_each_child_var (c, this){
            c = c->resolveSimpleIds (class_env);
        } end_for;
        return this;
    }

    void collectTypeVarDecls (Decl* enclosing){
        AST_Ptr params = child(1);
        for_each_child_var(param, params) {
            AST_Ptr paramId = param->child(0);
            Decl* paramType = makeTypeVarDecl(paramId->as_string(), param);
            param->addDecl(paramType);
        } end_for;
    }

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

/** Block */
class Block_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Block_AST, AST_Tree);
};

NODE_FACTORY(Block_AST, BLOCK);

/** Native */
class Native_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Native_AST, AST_Tree);
};

NODE_FACTORY(Native_AST, NATIVE);

/** TypeFormalsList*/
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

/** TypedID */
class TypedID_AST : public Typed_Tree {
    
protected:
    NODE_CONSTRUCTORS(TypedID_AST, Typed_Tree);

    AST_Ptr getId()
    {
        return child(0);
    }

    void addTargetDecls (Decl* enclosing) {
        AST_Ptr id = getId();
        Decl* decl = enclosing->addVarDecl(id);
        if (decl != NULL) {
            decl->setType((Type_Ptr)child(1));
            id->addDecl(decl);
        }
    }

    Type_Ptr getType()
    {
        return (Type_Ptr) child(1);
    }

    void resolveTypes (Decl* context, Unifier& subst)
    {
        if (arity() == 2 && child(1)->oper()->syntax() == TYPE){
            setType(getType(), subst);
        }
    }

};

NODE_FACTORY(TypedID_AST, TYPED_ID);

/** Assign */
class Assign_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(Assign_AST, Typed_Tree);

    void collectDecls (Decl* enclosing)
    {
        //fprintf(stderr, "collectDecls assign\n");
        child(0)->addTargetDecls(enclosing);
        child(1)->collectDecls(enclosing);
    }

    void resolveTypes (Decl* context, Unifier& subst)
    {
        AST::resolveTypes (context, subst);

        // consider more complex example
        if (unify(child(0)->getType(), child(1)->getType(),subst)) {
            setType(child(0)->getType(), subst);
        } else {
            error(loc(), "Assign left and right type inconsistency");
            throw logic_error("");
        }
    }
};

NODE_FACTORY(Assign_AST, ASSIGN);
