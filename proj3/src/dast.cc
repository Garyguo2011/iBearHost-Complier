/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* ast.cc: Basic AST subclasses. */

/* Authors:  P. N. Hilfinger */

#include <iostream>
#include "apyc.h"
#include "dast.h"
#include "dast-parser.hh"

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

void
AST::print (ostream& out, int indent)
{
    ASTSet visited;
    print(this, out, indent, visited);
}

void
AST::print (AST_Ptr tree, std::ostream& out, int indent, ASTSet& visited)
{
    tree->_print (out, indent, visited);
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

Decl*
AST::getDecl ()
{
    throw logic_error ("node does not represent a named entity");
}

Type_Ptr
AST::getType ()
{
    return NULL;
}

void
AST::setDecl (Decl* decl)
{
    UNIMPLEMENTED ("setDecl");
}

void
AST::setType (Type_Ptr type)
{
}

Type_Ptr
AST::computeType ()
{
    return NULL;
}

long
AST::intValue ()
{
    return 0;
}

void
AST::codeGen ()
{
    PASSDOWN (this, codeGen (), 0);
}

void
AST::codeGenNative ()
{
    PASSDOWN (this, codeGenNative (), 0);
}

void
AST::codeGenInternalFunc()
{
    PASSDOWN(this, codeGenInternalFunc(), 0);
}
void
AST::codeGenVarDecl()
{
    PASSDOWN(this, codeGenVarDecl(), 0);
}

void
AST::codeGenInit(AST_Ptr class_id)
{
    PASSDOWN(this, codeGenInit(class_id), 0);
}

void
AST::codeGenRecursiveCall(AST_Ptr func_id)
{
    PASSDOWN(this, codeGenRecursiveCall(func_id), 0);
}

void
AST::codeGenSemicolonForCall()
{
    if (oper()->syntax() == CALL ||
        oper()->syntax() == CALL1 ||
        oper()->syntax() == AND ||
        oper()->syntax() == OR ||
        oper()->syntax() == BINOP ||
        oper()->syntax() == UNOP ||
        oper()->syntax() == IF_EXPR ||
        oper()->syntax() == STRING_LITERAL ||
        oper()->syntax() == INT_LITERAL ||
        oper()->syntax() == TUPLE ||
        oper()->syntax() == LIST_DISPLAY) {
        cout << ";" << endl;
    }
}

string
AST::convertAsPyType(Type_Ptr TP)
{
    const char* temp = TP->child(0)->as_string().c_str();
    if (((std::string) temp).compare("str") == 0) {
        temp = "PyStr*";
    }
    else if (((std::string) temp).compare("int") == 0) {
        temp = "PyInt*";
    }
    else if (((std::string) temp).compare("bool") == 0) {
        temp = "PyBool*";
    }
    else if (((std::string) temp).compare("range") == 0) {
        temp = "PyRange*";
    }
    else if (((std::string) temp).compare("list") == 0) {
        temp = "PyList*";
    }
    else if (((std::string) temp).compare("dict") == 0) {
        temp = "PyDict*";
        if (((std::string) getType()->child(1)->child(0)->as_string().c_str()).compare("int") == 0)
        {
            temp = "PyDictInt*";
        } else if (((std::string) getType()->child(1)->child(0)->as_string().c_str()).compare("str") == 0) {
            temp = "PyDictStr*";
        } else if (((std::string) getType()->child(1)->child(0)->as_string().c_str()).compare("bool") == 0) {
            temp = "PyDictBool*";
        }
    }
    else if (((std::string) temp).compare("tuple0") == 0) {
        temp = "PyTuple0*";
    }
    else if (((std::string) temp).compare("tuple1") == 0) {
        temp = "PyTuple1*";
    }
    else if (((std::string) temp).compare("tuple2") == 0) {
        temp = "PyTuple2*";
    }
    else if (((std::string) temp).compare("tuple3") == 0) {
        temp = "PyTuple3*";
    } 
    else if (TP->oper()->syntax() == TYPE) {
        temp = (((std::string)temp) + "*").c_str();
    }
    else {
        temp = "PyValue";
    }
    return temp;
}

AST_Ptr
AST::getAst(int child, int depth)
{
    AST_Ptr result = this;
    while (depth > 0) {
        result = result->child(child);
        depth--;
    }
    return result;
}


/* Definitions of methods in base class AST_Tree. */

void
AST_Tree::_print (ostream& out, int indent, ASTSet& visited)
{
    visited.insert (this);
    out << "(" << externalName () << " " << lineNumber ();
    for_each_child (c, this) {
        out << endl << setw (indent + 4) << "";
        print (c, out, indent + 4, visited);
    } end_for;
    out << ")";
    visited.erase (this);
}

const char*
AST_Tree::externalName ()
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

