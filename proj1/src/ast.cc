/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* ast.cc: Basic AST subclasses. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "apyc-parser.hh"

using namespace std;

/* Definitions of methods in base class AST. */

Type_Ptr
AST::as_type ()
{
    throw logic_error ("node does not represent a type");
}

/* Definitions of methods in base class AST_Tree. */

void
AST_Tree::print (ostream& out, int indent)
{
    out << "(" << external_name () << " " << lineNumber ();
    for_each_child (c, this) {
        out << endl << setw (indent + 4) << "";
        c->print (out, indent + 4);
    } end_for;
    out << ")";
}

const char*
AST_Tree::external_name ()
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

AST_Ptr
make_id (const char* text, const char* loc) 
{
    AST_Ptr result = AST::make_token (ID, strlen (text), text);
    result->set_loc (loc);
    return result;
}

/* Debugging utilities */

/** Output AST on the standard error output, using its print method. */
void
DB(AST* ast)
{
    if (ast == NULL) {
        cerr << "<null>" << endl;
    } else {
        ast->print(cerr, 0);
    }
}
