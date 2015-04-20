/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* post1.cc: Preliminary modifications of the AST received from phase 1. */

/* Authors:  P. N. Hilfinger */

#include "apyc.h"
#include "ast-parser.hh"

using namespace std;

static AST_Ptr prependChildren(AST_Ptr tree0, AST_Ptr tree1);
static AST_Ptr reviseTree(AST_Ptr tree, bool classp);
static AST_Ptr makeTypedId(AST_Ptr formal);

/** Assuming that PROG is the AST for a program produced by the parser
 *  compiler phase 1 and PRELUDE is the AST for the stsndard prelude
 *  produced by compiler phase 1, returns the result of destructively
 *  applying the following transformations:
 *
 *  1. The statements of PRELUDE are prepended to those of PROG.
 *  2. All "def" nodes that represent methods are converted to
 *     "method" nodes, which have the same children as defs.
 *  3. All missing return types are replaced by fresh anonymous type variables.
 *  4. All formal parameters are given fresh anonymous type variables as formal
 *     types.
 *  5. All "block" and type_list nodes are removed, and their children
 *     transferred to the enclosing node.
 */ 
AST_Ptr
post1 (AST_Ptr prog, AST_Ptr prelude)
{
    prog = prependChildren (prog, prelude);
    return reviseTree(prog, false);
}    

/** Return TREE0 after first inserting the children of TREE1 before
 *  TREE0's previous children. */
static AST_Ptr
prependChildren (AST_Ptr tree0, AST_Ptr tree1)
{
    for_each_child_reverse (stmt, tree1) {
        tree0->insert(0, stmt);
    } end_for;
    return tree0;
}


/** Perform phase 1 modifications (see phase1 above) on TREE,
 *  returhing modified tree. CLASSP is true iff TREE is a child
 *  of a class node block. */
static AST_Ptr
reviseTree (AST_Ptr tree, bool classp)
{
    if (tree == NULL)
        return NULL;

    switch (tree-> oper ()->syntax ()) {
    default:
        for_each_child_var (c, tree) {
            c = reviseTree (c, false);
        } end_for;
        break;

    case CLASS:
        for_each_child_var (c, tree) {
            c = reviseTree (c, true);
        } end_for;
        break;

    case BLOCK:
        for_each_child_var (c, tree) {
            c = reviseTree (c, classp);
        } end_for;
        break;

    }
        
    switch (tree->oper ()->syntax ()) {
    default:
        return tree;

    case DEF: {
        AST_Ptr body = tree->child (tree->arity () - 1);
        tree->replace (tree->arity () - 1, AST::make_list ());
        if (tree->arity () == 2) {
            tree->append (Type::makeVar ());
        }
        tree->copyChildren (tree->arity (), body, 0, body->arity ());
        if (classp) {
            return tree->retypedNode (METHOD);
        } else
            return tree;
    }

    case CLASS: case FUNCTION_TYPE: case TYPE: {
        AST_Ptr body = tree->child (tree->arity () - 1);
        tree->replace (tree->arity () - 1, AST::make_list ());
        tree->copyChildren (tree->arity (), body, 0, body->arity ());
        return tree;
    }

    case FORMALS_LIST:
        for_each_child_var (c, tree) {
            c = makeTypedId (c);
        } end_for;
        return tree;
        
    }

}

/** Return FORMAL (an id or typed id) as a typed id.  This is the
 *  identity on TYPE_ID nodes.  It returns a TYPED_ID with a fresh
 *  type variable for plain ID nodes. */
static AST_Ptr
makeTypedId (AST_Ptr formal)
{
    switch (formal->syntax ()) {
    default:
        return formal;
    case ID:
        return consTree (TYPED_ID, formal, Type::makeVar ());
    }
}

