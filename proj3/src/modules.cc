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

        cout << "int count_loop; //For keep tracking else stmt belongs to loop." << endl;

        /** Generate code for class definitions*/
        for_each_child(c, this) {
            if (c->oper()->syntax() == CLASS) {
                c->codeGenParams();
                c->codeGen();
            }
        } end_for;


        for_each_child(c, this) {
            if (c->oper()->syntax() != CLASS) {
                c->codeGenParams();
            }
        } end_for;


        /** Generate code for function definitions*/
        for_each_child(c, this) {
            if (c->oper()->syntax() == DEF) {
                c->codeGen();
            } 
            else if (c->oper()->syntax() == ASSIGN) {
                c->codeGenVarDecl();
            }
        } end_for;


        /** Generate code for main function*/
        cout << "void" << endl
             << "__main__()" << endl
             << "{" << endl;

        for_each_child_var(c, this) {
            if (c->oper()->syntax() == CLASS) {
                if (user_defined(c)) {
                    for (unsigned int i = 2; i < c->arity(); i++) {
                        AST_Ptr ch = c->child(i);
                        if (ch->oper()->syntax() != METHOD) {
                            if (ch->oper()->syntax() == ASSIGN) {
                                ch->codeGenVarDeclRegardless();
                            }
                            ch->codeGen();
                            ch->codeGenSemicolonForCall();
                        }
                    }
                }
            }

            if (c->oper()->syntax() != DEF 
                && c->oper()->syntax() != CLASS) {
                c->codeGen();
            }
             /** 
             * Kludge to add semicolon after function call
             * if it makes up a whole statement
             */
            c->codeGenSemicolonForCall();
        } end_for;
        cout << endl;
        if (child(arity()-1)->oper()->syntax() == PRINT) {
            cout << "__newline__();" << endl;
        }
        cout << "}" << endl;
    }

    NODE_CONSTRUCTORS (Module_AST, AST_Tree);

};

NODE_FACTORY (Module_AST, MODULE);

