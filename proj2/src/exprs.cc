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

};

NODE_FACTORY(True_AST, TRUE);


class False_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (False_AST, Typed_Tree);

    Type_Ptr computeType () {
        return boolDecl->asType ();
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
            init_tree->addDecl(init_decl);
            AST_Ptr new_tree = consTree(NEW, this->child(0));
            std::vector <AST_Ptr> temp;
            temp.push_back(init_tree);
            temp.push_back(consTree(NEW, this->child(0)));
            if (this->arity() >= 2){
                // AST_Ptr expr_tree = this->child(1);
                for (int i = 1; i < this->arity(); i++){
                temp.push_back(this->child(i));
                }
            }
            AST_Ptr* new_args = &temp[0];
            // AST_Ptr new_expr_tree = AST::make_tree(EXPR_LIST, new_args, new_args + sizeof (new_args) / sizeof(new_args[0]));
            // return AST::make_tree(CALL1, new_args, new_args + sizeof (new_args) / sizeof(new_args[0]));
            return AST::make_tree(CALL1, &temp[0], &temp[temp.size()]);
        } else {
            for_each_child_var (c, this) {
                c = c->resolveAllocators (env)l;
            } end_for;
        }
        return this;
    }
    NODE_CONSTRUCTORS (Call_AST, Callable);


};

NODE_FACTORY (Call_AST, CALL);

/** A binary operator. */
class Binop_AST : public Callable {

    NODE_CONSTRUCTORS (Binop_AST, Callable);

};    

NODE_FACTORY (Binop_AST, BINOP);

/** A unary operator. */
class Unop_AST : public Callable {

    NODE_CONSTRUCTORS (Unop_AST, Callable);

};    

NODE_FACTORY (Unop_AST, UNOP);

// FIXME: There are others as well.

/** ID */
class ID_AST : public AST_Tree {
    NODE_CONSTRUCTORS(ID_AST, AST_Tree);

    void addTargetDecls (Decl* enclosing) {
        Decl* decl = enclosing -> addVarDecl(this);
        if (decl != NULL) {
            this->addDecl(decl);
        }
    }

    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        Decl_Vector decls;
        gcstring name = id->as_string();
        Decl* decl = classes->find(name);
        if (decl != NULL && this->numDecls() == 0){
            this->addDecl(decl);
            return consTree(TYPE, this, consTree(TYPE_LIST));
        }
        env->find(name, decls);
        if (decls.size() == 0){
            fprintf(stderr, "decl not found\n");
        } else {
            for (Decl_Vector::const_iterator i = decls.begin(); 
                i != decls.end();
                i++){
                this->addDecl(*i);
            }
        }
        return this;
    }
};

NODE_FACTORY(ID_AST, ID);

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
};

NODE_FACTORY(Attributeref_AST, ATTRIBUTEREF);

/** Tuple */
class Tuple_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS(Tuple_AST, Typed_Tree);
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
};

NODE_FACTORY(ListDisplay_AST, LIST_DISPLAY);

/** Dictionary Display */
class DictDisplay_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(DictDisplay_AST, Typed_Tree);
};

NODE_FACTORY(DictDisplay_AST, DICT_DISPLAY);

/** If expression (to be organized. )*/
class IfExpr_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(IfExpr_AST, Typed_Tree);
};

NODE_FACTORY(IfExpr_AST, IF_EXPR);

/** And (to be organized) */
class And_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(And_AST, Typed_Tree);
};

NODE_FACTORY(And_AST, AND);

/** OR (to be organized) */
class Or_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(Or_AST, Typed_Tree);
};

NODE_FACTORY(Or_AST, OR);


