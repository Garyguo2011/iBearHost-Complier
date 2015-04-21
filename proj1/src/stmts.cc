/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "apyc-parser.hh"

using namespace std;

/** Make sure garbage collection is initialized. */
static GCINIT _gcdummy;

/*****   MODULE    *****/

/** A module, representing a complete source file. */
class Module_AST : public AST_Tree {
public:

    int lineNumber () {
	return 0;
    }

    NODE_CONSTRUCTORS (Module_AST, AST_Tree);

protected:

    const char* externalName () {
	return "module";
    }

};

NODE_FACTORY (Module_AST, MODULE);




/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class Println_AST : public AST_Tree {
public:

    NODE_CONSTRUCTORS (Println_AST, AST_Tree);

protected:

    const char* externalName () {
	return "println";
    }

};

NODE_FACTORY (Println_AST, PRINTLN);



/*****  TYPE_VAR *****/

class Type_Var_Token : public AST_Token {

    void print (ostream& out, int indent) {
        out << "(type_var " << lineNumber () << " " << as_string () << ")";
    }

    TOKEN_CONSTRUCTORS(Type_Var_Token, AST_Token);

};

TOKEN_FACTORY(Type_Var_Token, TYPE_VAR);
