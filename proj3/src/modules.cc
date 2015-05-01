/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* modules.cc: Describes programs or libraries.  Contains top-level routines. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "dast.h"
#include "dast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

Decl* mainModule;

/*****   MODULE    *****/

/** A module, representing a complete source file. */
class Module_AST : public AST_Tree {
protected:

    const char* lineNumber () {
	return "0";
    }

    // FIXME: Dummy implementation.
    void codeGen () {
        cout << "#include \"runtime.h\"" << endl;

        /** Generate code for class definitions*/
        for_each_child(c, this) {
            if (c->oper()->syntax() == CLASS) {
                c->codeGen();
            }
        } end_for;

        /** Generate code for function definitions*/
        for_each_child(c, this) {
            if (c->oper()->syntax() == DEF) {
                c->codeGen();
            }
        } end_for;

        /** Generate code for main function*/
        cout << "void" << endl
             << "__main__()" << endl
             << "{" << endl;
        for_each_child_var(c, this) {
            if (c->oper()->syntax() != DEF 
                && c->oper()->syntax() != CLASS) {
                c->codeGen();
            }
             /** 
             * Kludge to add semicolon after function call
             * if it makes up a whole statement
             */
            if (c->oper()->syntax() == CALL ||
                c->oper()->syntax() == CALL1) {
                // c->codeGen();
                cout << ";" << endl;
            }
        } end_for;
        cout << endl;
        cout << "}" << endl;
    }

    NODE_CONSTRUCTORS (Module_AST, AST_Tree);

};

NODE_FACTORY (Module_AST, MODULE);

