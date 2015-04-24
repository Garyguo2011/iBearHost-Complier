/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* ast.cc: Basic AST subclasses. */

/* Authors:  P. N. Hilfinger */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/* Definitions of methods in base class AST. */

void
AST::copyChildren (int k, AST_Ptr node, int first, int len)
{
    for (int i = len - 1; i >= 0; i -= 1) {
        insert (k, node->child (first + i));
    }
}

AST_Ptr
AST::retypedNode (int syntax)
{
    AST_Ptr result = consTree(syntax);
    result->set_loc (loc ());
    result->copyChildren (0, this, 0, arity ());
    return result;
}

void
AST::print (ostream& out, int indent)
{
    ASTSet visiting;
    print(this, out, indent, visiting);
}

void
AST::print (AST_Ptr tree, std::ostream& out, int indent, ASTSet& visiting)
{
    tree->_print (out, indent, visiting);
}

void
AST::_print (ostream& out, int indent, ASTSet& visiting)
{
    visiting.insert (this);
    out << "(" << externalName () << " " << lineNumber ();
    for_each_child (c, this) {
        out << endl << setw (indent + 4) << "";
        print (c, out, indent + 4, visiting);
    } end_for;
    printOther (out, indent, visiting);
    out << ")";
    visiting.erase (this);
}

const char*
AST::externalName ()
{
    static string result;

    int syntax = oper ()->syntax ();
    const char* name;
    name = yyexternal_token_name (syntax);
    if (name == NULL)
        return "?";
    if (name[0] != '"')
        return name;
    name += 1;
    while (*name == '@')
        name += 1;
    
    if (name[0] == '\0')
        return "?";

    result = string (name, strlen (name)-1);
    return result.c_str();
}

void
AST::printOther (ostream& out, int indent, ASTSet& visiting)
{
}

Type_Ptr
AST::asType ()
{
    return NULL;
}

bool
AST::isType ()
{
    return false;
}

AST_Ptr
AST::getId ()
{
    UNIMPLEMENTED (getId);
}

int
AST::numDecls ()
{
    return 0;
}

Decl*
AST::getDecl (int k)
{
    throw logic_error ("node does not represent a named entity");
}

void
AST::addDecl (Decl*)
{
    throw logic_error ("node does not represent a named entity");
}

void
AST::removeDecl (int k)
{ 
    throw logic_error ("node does not represent a named entity");
}

Type_Ptr
AST::getType ()
{
    throw logic_error ("node does not represent something with a type");
}

void
AST::resolveSelectedType (Unifier& subst, Resolver& resolver)
{
    throw logic_error ("resolveSelectedType applies only to ids");
}

bool
AST::setType (Type_Ptr type, Unifier& subst)
{
    throw logic_error ("node does not represent something with a type");
}

/** Default collects declarations and resolves in the current
 *  module. */
AST_Ptr
AST::doOuterSemantics ()
{
    AST_Ptr tree;
    tree = this;
    tree->collectDecls (mainModule);
    tree->resolveSimpleTypeIds (outerEnviron);
    tree = tree->resolveSimpleIds (outerEnviron);
    tree = tree->resolveAllocators (outerEnviron);
    tree = tree->resolveStaticSelections (outerEnviron);
    tree->resolveTypesOuter (mainModule);
    tree->otherChecks ();
    return tree;
}

void
AST::collectDecls (Decl* enclosing)
{
    for_each_child (c, this) {
        c->collectDecls (enclosing);
    } end_for;
}

void
AST::collectTypeVarDecls (Decl*)
{
}

void
AST::addTargetDecls (Decl* enclosing)
{
    UNIMPLEMENTED (addTargetDecls);
}

AST_Ptr
AST::resolveSimpleIds (const Environ* env)
{
    for_each_child_var (c, this) {
        c = c->resolveSimpleIds (env);
    } end_for;
    return this;
}

void
AST::resolveSimpleTypeIds (const Environ* env)
{
    for_each_child (c, this) {
        c->resolveSimpleTypeIds (env);
    } end_for;
}
    
AST_Ptr
AST::resolveAllocators (const Environ* env)
{
    for_each_child_var (c, this) {
        c = c->resolveAllocators (env);
    } end_for;
    return this;
}

AST_Ptr
AST::resolveStaticSelections (const Environ* env)
{
    for_each_child_var (c, this) {
        c = c->resolveStaticSelections (env);
    } end_for;
    return this;
}

void
AST::freezeDecls (bool frozen)
{
    for_each_child (c, this) {
        c->freezeDecls (frozen);
    } end_for;
}

void
AST::getOverloadings (Resolver& resolver)
{
    for_each_child (c, this) {
        c->getOverloadings (resolver);
    } end_for;
}

void
AST::resolveTypes (Decl* context, Unifier& subst, Resolver& resolver)
{
    for_each_child_var (c, this) {
        c->resolveTypes (context, subst, resolver);
    } end_for;
}

void
AST::resolveTypes (Decl* context, Unifier& subst, Resolver& resolver,
                   Type_Ptr nextValueType)
{
    resolveTypes (context, subst, resolver);
}

void
AST::otherChecks ()
{
    for_each_child (c, this) {
        c->otherChecks ();
    } end_for;
}

bool
AST::errorReported ()
{
    return _erroneous;
}

void
AST::recordError ()
{
    _erroneous = true;
}

AST_Ptr
AST::replaceBindings ()
{
    ASTSet visiting;
    return replaceBindings(visiting);
}

AST_Ptr
AST::replaceBindings (ASTSet& visiting)
{
    if (visiting.count (this) == 0) {
        visiting.insert (this);
        for_each_child_var (c, this) {
            c = c->replaceBindings (visiting);
        } end_for;
        visiting.erase (this);
    }
    return this;
}

AST_Ptr
AST::replaceBindings (AST_Ptr p, ASTSet& visiting)
{
    return p->replaceBindings (visiting);
}


void
AST::findUsedDecls (DeclSet& used)
{
    for_each_child (c, this) {
        c->findUsedDecls (used);
    } end_for;
}

/* Definitions of methods in base class AST_Tree. */

AST_Ptr
make_id (const char* text, const char* loc) 
{
    AST_Ptr result = AST::make_token (ID, strlen (text), text);
    result->set_loc (loc);
    return result;
}

AST_Ptr
consTree (int syntax)
{
    AST_Ptr args[1];
    return AST::make_tree (syntax, args, args);
}

AST_Ptr
consTree (int syntax, AST_Ptr c0)
{
    AST_Ptr args[] = { c0 };
    return AST::make_tree (syntax, args, args + 1);
}

AST_Ptr
consTree (int syntax, AST_Ptr c0, AST_Ptr c1)
{
    AST_Ptr args[] = { c0, c1 };
    return AST::make_tree (syntax, args, args + 2);
}

AST_Ptr
consTree (int syntax, AST_Ptr c0, AST_Ptr c1,
          AST_Ptr c2)
{
    AST_Ptr args[] = { c0, c1, c2 };
    return AST::make_tree (syntax, args, args + 3);
}

AST_Ptr
consTree (int syntax, AST_Ptr c0, AST_Ptr c1,
          AST_Ptr c2, AST_Ptr c3)
{
    AST_Ptr args[] = { c0, c1, c2, c3 };
    return AST::make_tree (syntax, args, args + 4);
}

AST_Ptr
consTree (int syntax, AST_Ptr* first, AST_Ptr* limit)
{
    return AST::make_tree (syntax, first, limit);
}

