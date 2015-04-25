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
        fprintf(stderr, "outside main: \n");
        //PASSDOWN (this, codeGen (), 0);
        cout << "void" << endl
             << "__main__()" << endl
             << "{" << endl;
        fprintf(stderr, "inside main:\n");
        for_each_child_var(c, this) {
            c->codeGen();
        } end_for;
        cout << endl;
        cout << "}" << endl;
    }

    NODE_CONSTRUCTORS (Module_AST, AST_Tree);

};

NODE_FACTORY (Module_AST, MODULE);

