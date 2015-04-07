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

