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
};

NODE_FACTORY(If_AST, IF);

/** While */
class While_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(While_AST, AST_Tree);
};

NODE_FACTORY(While_AST, WHILE);

/** For */
class For_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(For_AST, AST_Tree);

    void collectDecls (Decl* enclosing) {
        //fprintf(stderr, "collectDecls For\n");
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
    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        AST_Ptr id = child(0);
        const Environ* func_env = id->getDecl()->getEnviron();
        for_each_child_var (c, this) {
            c = c->resolveSimpleIds(func_env);
        } end_for;
        return this;
    }
    NODE_CONSTRUCTORS(Def_AST, AST_Tree);

    void collectDecls (Decl* enclosing)
    {
        //fprintf(stderr, "collectDecls def\n");
        AST_Ptr id = child(0);
        Decl* decl = enclosing->addDefDecl(id);
        if (decl != NULL) {
            id->addDecl(decl);
            for_each_child(c, this) {
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
                decl = makeParamDecl(c->as_string(), 
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
        for (unsigned int count = 0; count < params->arity(); count++){
            AST_Ptr param = params->child(count);
            AST_Ptr paramId = param->child(0);
            Decl* paramType = makeTypeVarDecl(paramId->as_string(), param);
            param->addDecl(paramType);
        }
    }

    NODE_CONSTRUCTORS(Class_AST, AST_Tree);

    void collectDecls (Decl* enclosing) {
        //fprintf(stderr, "collectDecls class\n");
        AST_Ptr id = child(0);
        AST_Ptr typeFormals = child(1);
        AST_Ptr block = child(2);
        const gcstring name = id->as_string();

        Decl* decl = makeClassDecl(name, typeFormals);
        if (decl != NULL) {
            if (name == "str") {
                strDecl = decl;
            }
            else if (name == "int") {
                intDecl = decl;
            }
            else if (name == "bool") {
                boolDecl = decl;
            }
            else if (name == "range") {
                rangeDecl = decl;
            }
            else if (name == "list") {
                listDecl = decl;
            }
            else if (name == "dict") {
                dictDecl = decl;
            }
            else if (name == "tuple0") {
                tuple0Decl = decl;
            }
            else if (name == "tuple1") {
                tuple1Decl = decl;
            }
            else if (name == "tuple2"){
                tuple2Decl = decl;
            }
            else if (name == "tuple3"){
                tuple3Decl = decl;
            }
            this->collectTypeVarDecls(decl);
            id->addDecl(decl);
            block->collectDecls(decl);
            classes->define(decl);
            enclosing->addMember(decl);
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
class TypedID_AST : public AST_Tree {
    
protected:
    NODE_CONSTRUCTORS(TypedID_AST, AST_Tree);

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

    /* DEBUGGING */

    void
    DB (const Environ* env)
    {
        if (env == NULL) {
            fprintf (stderr, "NULL\n");
        } else {
            const char* label;
            label = "Immediate";
            while (env != NULL) {
                const Decl_Vector& members = env->get_members ();
                fprintf (stderr, "%s:\n", label);
                for (size_t i = 0; i < members.size (); i += 1) {
                    fprintf (stderr, "   %s @%p\n", members[i]->getName ().c_str (),
                             members[i]);
                }
                env = env->get_enclosure ();
                label = "Enclosed by";
            }
        }
    }
};

NODE_FACTORY(TypedID_AST, TYPED_ID);

/** Assign */
class Assign_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Assign_AST, AST_Tree);

    void collectDecls (Decl* enclosing)
    {
        //fprintf(stderr, "collectDecls assign\n");
        child(0)->addTargetDecls(enclosing);
        child(1)->collectDecls(enclosing);
    }
};

NODE_FACTORY(Assign_AST, ASSIGN);

// class Type_AST : public AST_Tree {
// protected:
//     NODE_CONSTRUCTORS(Type_AST, AST_Tree);

//     AST_Ptr resolveSimpleIds (const Environ* env)
//     {
//         fprintf(stderr, "Type\n");
//         AST_Ptr id = child(0);
//         gcstring name = id->as_string();
//         Decl* decl = classes->find(name);
//         if (decl != NULL && id->numDecls() == 0){
//             id->addDecl(decl);
//         }
//         return this;
//     }

//     void resolveSimpleTypeIds (const Environ* env)
//     {
//         AST_Ptr id = child(0);
//         Decl* decl = classes->find(id->as_string());
//         if (decl != NULL){
//             this->addDecl(decl);
//         }
//     }
// };

// NODE_FACTORY(Type_AST, TYPE);
