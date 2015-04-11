/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* exprs.cc: AST subclasses related to expressions. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/* The Horn framework has a provision (the NODE_FACTORY macro) that
 * allows AST subclasses to "register" themselves with the parser and
 * associate themselves with a particular syntactic category so that
 * the parser will create instances of the appropriate subclass when
 * asked to produce an AST node with a particular operator.  The
 * NODE_..._CONSTRUCTOR... macros set up the necessary constructors
 * and factory declarations in any given class.  To associate a
 * class with a given operator token, pass the (int) value of that
 * token's syntactic category to the NODE_FACTORY macro (for
 * one-character tokens, the character itself is usually the syntactic
 * category; for other tokens, use the name declared in the Horn
 * source file (those definitions appear in ast-parser.hh, included above).
 * There are examples in this and other files.
 */

/*****   Typed_Tree   *****/

Type_Ptr
Typed_Tree::getType ()
{
    if (_type == NULL)
        _type = computeType ();
    return _type;
}

bool
Typed_Tree::setType (Type_Ptr type, Unifier& subst)
{
    if (_type == NULL)
        _type = Type::makeVar ();
    return unify (_type, type, subst);
}

void
Typed_Tree::resolveTypes (Decl* context, Unifier& subst)
{
    AST_Tree::resolveTypes (context, subst);
    getType ();
}

Type_Ptr
Typed_Tree::computeType ()
{
    return Type::makeVar ();
}

/* The following is an EXAMPLE of a potentially useful AST class
 * structure, showing the macros you can use to set up base classes
 * and their subtypes. */

/*****   NONE, TRUE, FALSE     *****/

class None_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (None_AST, Typed_Tree);

};

NODE_FACTORY(None_AST, NONE);

class True_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (True_AST, Typed_Tree);

    Type_Ptr computeType () {
        return boolDecl->asType ();
    }

    void resolveTypes (Decl* context, Unifier& subst) {
        setType(computeType(), subst);
    }

};

NODE_FACTORY(True_AST, TRUE);


class False_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (False_AST, Typed_Tree);

    Type_Ptr computeType () {
        return boolDecl->asType ();
    }

    void resolveTypes (Decl* context, Unifier& subst) {
        setType(computeType(), subst);
    }
};

NODE_FACTORY(False_AST, FALSE);


/*****   CALLS    *****/

/** The supertype of "callable" things, including ordinary calls,
 *  binary operators, unary operators, subscriptions, and slices. */

class Callable : public Typed_Tree {
protected:

    NODE_BASE_CONSTRUCTORS (Callable, Typed_Tree);
    
    /** Returns the expression representing the quantity that is
     *  called to evaluate this expression. */
    virtual AST_Ptr calledExpr () {
        return child (0);
    }

    /** Returns the number of actual parameters in this call. */
    virtual int numActuals () {
        return arity () - 1;
    }

    /** Return the Kth actual parameter in this call. */
    virtual AST_Ptr actualParam (int k) {
        return child (k + 1);
    }

    /** Set the Kth actual parameter in this call to EXPR. */
    virtual void setActual (int k, AST_Ptr expr) {
        replace (k + 1, expr);
    }

    // PUT COMMON CODE DEALING WITH TYPE-CHECKING or SCOPE RULES HERE.

};

/** A function call. */
class Call_AST : public Callable {

protected:

    AST_Ptr resolveAllocators (const Environ* env){
        if (this->child(0)->oper()->syntax() == TYPE){
            AST_Ptr init_tree = make_id("__init__", "0");
            gcstring name = this->child(0)->child(0)->as_string();
            Decl* decl = classes->find(name);
            Decl* init_decl = decl->getEnviron()->find_immediate("__init__");
            if (init_decl != NULL){
                init_tree->addDecl(init_decl);
                // AST_Ptr new_tree = consTree(NEW, this->child(0));
                std::vector <AST_Ptr> temp;
                temp.push_back(init_tree);
                temp.push_back(consTree(NEW, this->child(0)));
                if (this->arity() >= 2){
                    // AST_Ptr expr_tree = this->child(1);
                    for (unsigned int i = 1; i < this->arity(); i++){
                    temp.push_back(this->child(i));
                    }
                }
                // AST_Ptr* new_args = &temp[0];
                // AST_Ptr new_expr_tree = AST::make_tree(EXPR_LIST, new_args, new_args + sizeof (new_args) / sizeof(new_args[0]));
                // return AST::make_tree(CALL1, new_args, new_args + sizeof (new_args) / sizeof(new_args[0]));
                return AST::make_tree(CALL1, &temp[0], &temp[temp.size()]);    
            } else {
                error(loc(), "No __init__ method found.");   
            }
            
        } else {
            for_each_child_var (c, this) {
                c = c->resolveAllocators (env);
            } end_for;
        }
        return this;
    }

    // void resolveTypes (Decl* context, Unifier& subst)
    // {
    //     context get environ find immediate id name 


    // }
    NODE_CONSTRUCTORS (Call_AST, Callable);

};

NODE_FACTORY (Call_AST, CALL);

class Call1_AST : public Callable {
protected:
    NODE_CONSTRUCTORS (Call1_AST, Callable);

    AST_Ptr getId () {
        return child(1)->child(0)->child(0);
    }

    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes(context, subst);
        Decl* classDecl = classes->find(getId()->as_string());
        if (classDecl != NULL) {
            setType(classDecl->asType(), subst);
        } else {
            error(loc(), "Class Declation missing");
        }
    }
};

NODE_FACTORY (Call1_AST, CALL1);

/** A binary operator. */
class Binop_AST : public Callable {
protected:
    NODE_CONSTRUCTORS (Binop_AST, Callable);

};    

NODE_FACTORY (Binop_AST, BINOP);

/** A unary operator. */
class Unop_AST : public Callable {
protected:
    NODE_CONSTRUCTORS (Unop_AST, Callable);

};    

NODE_FACTORY (Unop_AST, UNOP);

// FIXME: There are others as well.

// /** ID */
// class ID_AST : public AST_Tree {
// protected:
//     NODE_CONSTRUCTORS(ID_AST, AST_Tree);

//     AST_Ptr getId()
//     {
//         return child(0);
//     }


// };

// NODE_FACTORY(ID_AST, ID);

/** subscriptions */
class Subscript_AST : public Callable {
    NODE_CONSTRUCTORS(Subscript_AST, Callable);
};

NODE_FACTORY (Subscript_AST, SUBSCRIPT);

/** slices */
class Slice_AST : public Callable {
    NODE_CONSTRUCTORS(Slice_AST, Callable);
};

NODE_FACTORY (Slice_AST, SLICE);

/** Compare */
class Compare_AST : public Binop_AST {
protected:
    
    NODE_CONSTRUCTORS(Compare_AST, Binop_AST);

};

NODE_FACTORY(Compare_AST, COMPARE);

/** Left Compare */
class LeftCompare_AST : public Binop_AST {
protected:

    NODE_CONSTRUCTORS(LeftCompare_AST, Binop_AST);
};

NODE_FACTORY(LeftCompare_AST, LEFT_COMPARE);

/** Attributeref */
class Attributeref_AST : public Typed_Tree {
protected:
    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        int count = 0;
        for_each_child_var (c, this){
            if (count == 0){
                c = c->resolveSimpleIds(env);
            }
            count++;
        } end_for;
        return this;
    }
    NODE_CONSTRUCTORS(Attributeref_AST, Typed_Tree);

    AST_Ptr getId() {
        return child(1);
    }

    void addDecl(Decl* decl) {
        getId()->addDecl(decl);
    }

    AST_Ptr resolveStaticSelections (const Environ* env) {
        AST_Ptr id0 = this->child(0);
        Decl* decl = id0->getDecl();
        AST_Ptr id1 = getId();
        if (decl != NULL) {
            Decl_Vector decls;
            decl->getEnviron()->find(id1->as_string(), decls);

            for (Decl_Vector::const_iterator i = decls.begin ();
                     i != decls.end ();
                     i++)
            {
                if ((*i)->isMethod()) {
                    id1->addDecl((*i));
                    return id1;
                }
            }
        } else {
            fprintf(stderr, "Class not found.\n");
        }
        return id1;
    }
};

NODE_FACTORY(Attributeref_AST, ATTRIBUTEREF);

/** Tuple */
class Tuple_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS(Tuple_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes (context, subst);

        switch (arity())
        {
            case 0:
            {
                setType(tuple0Decl->asType(), subst);
                break;
            }
            case 1:
            {
                Type_Ptr type_list[1];
                type_list[0] = child(0)->getType();
                setType(tuple1Decl->asType(arity(), type_list), subst);
                break;
            }
            case 2:
            {
                Type_Ptr type_list[2];
                type_list[0] = child(0)->getType();
                type_list[1] = child(1)->getType();
                setType(tuple2Decl->asType(arity(), type_list), subst);
                break;
            }
            case 3:
            {
                Type_Ptr type_list[3];
                type_list[0] = child(0)->getType();
                type_list[1] = child(1)->getType();
                type_list[2] = child(2)->getType();
                setType(tuple3Decl->asType(arity(), type_list), subst);
                break;
            }
            default:
            {
                error(loc(), "Tuple has more than 3 children");
            }
        }
    }

};

NODE_FACTORY(Tuple_AST, TUPLE);

/** TargetList (to be modified) */
class TargetList_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS(TargetList_AST, Typed_Tree);
};

NODE_FACTORY(TargetList_AST, TARGET_LIST);

/** List Display */
class ListDisplay_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(ListDisplay_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes (context, subst);
        if (arity() == 0) {
            setType(listDecl->asType(1, Type::makeVar()), subst);
        } else {
            Type_Ptr elements[1];
            elements[0] = child(0)->getType();
            Type_Ptr first_type = elements[0];
            for (unsigned int i = 1; i < arity() ; i++) {
                if (!unify(first_type, child(i)->getType(), subst)) {
                    error (loc (), "Elements in list are not same types");
                }
            }
            setType(listDecl->asType(1, elements), subst);
        }
    }
};

NODE_FACTORY(ListDisplay_AST, LIST_DISPLAY);

/** Dictionary Display */
class DictDisplay_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(DictDisplay_AST, Typed_Tree);
    void resolveTypes (Decl* context, Unifier& subst) 
    {
        AST::resolveTypes (context, subst);
        if (arity() == 0) {
            Type_Ptr type_list[2];
            type_list[0] = Type::makeVar();
            type_list[1] = Type::makeVar();
            setType(dictDecl->asType (2, type_list), subst);
        } else {
            Type_Ptr keyType = child(0)->child(0)->getType();

            if (unify(keyType, boolDecl->asType(), subst) || 
                unify(keyType, intDecl->asType(), subst) || 
                unify(keyType, strDecl->asType(), subst)) {
                Type_Ptr elements[2];
                elements[0] = child(0)->child(0)->getType();
                elements[1] = child(0)->child(1)->getType();
                Type_Ptr first_type = dictDecl->asType(2, elements);
                for (unsigned int i = 1; i < arity() ; i++) {
                    Type_Ptr rest[2];
                    rest[0] = child(i)->child(0)->getType();
                    rest[1] = child(i)->child(1)->getType();
                    Type_Ptr rest_type = dictDecl->asType(2, rest);
                    if (!unify(first_type, rest_type, subst)) {
                        error (loc (), "Elements in dict are not same types");
                    }
                }
                setType(first_type, subst);
            } else {
                error(loc(), "invalid key type");
            }
            
        }
    }
};

NODE_FACTORY(DictDisplay_AST, DICT_DISPLAY);

/** If expression (to be organized. )*/
class IfExpr_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(IfExpr_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst) 
    {
        AST::resolveTypes (context, subst);

        if (!unify(child(0)->getType(), boolDecl->asType(), subst)) {
            error(loc(), "IF_EXPR expression is not bool");
        }

        if (unify(child(1)->getType(), child(2)->getType(), subst)) {
            setType(child(1)->getType(), subst);
        } else {
            error(loc(), "IF_EXPR Inconsistent Types");
        }
    }
};

NODE_FACTORY(IfExpr_AST, IF_EXPR);

/** And (to be organized) */
class And_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(And_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst) {
        AST_Tree::resolveTypes (context, subst);

        if (!unify(child(0)->getType(), child(1)->getType(), subst)) {
            error (loc (), "And Statement Expressions doesn't match");
        } else {
            setType(child(0)->getType(), subst);    
        }
    }
};

NODE_FACTORY(And_AST, AND);

/** OR (to be organized) */
class Or_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(Or_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst) {
        AST_Tree::resolveTypes (context, subst);

        if (!unify(child(0)->getType(), child(1)->getType(), subst)) {
            error (loc (), "Or Statement Expressions doesn't match");
        } else {
            setType(child(0)->getType(), subst);    
        }
    }
};

NODE_FACTORY(Or_AST, OR);


