/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class Println_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Println_AST, AST_Tree);

    const char* externalName () {
	return "println";
    }

};

NODE_FACTORY (Println_AST, PRINTLN);

/** Print */
class Print_AST : public Println_AST {
protected:
    NODE_CONSTRUCTORS(Print_AST, Println_AST);
};

NODE_FACTORY(Print_AST, PRINT);

/***** STMT_LIST *****/

/** A list of statements. */
class StmtList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (StmtList_AST, AST_Tree);

    AST_Ptr doOuterSemantics () {
        for_each_child_var (c, this) {
            c = c->doOuterSemantics ();
        } end_for;
        return this;
    }

};

NODE_FACTORY (StmtList_AST, STMT_LIST);

/** return */
class Return_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Return_AST, AST_Tree);
};

NODE_FACTORY(Return_AST, RETURN);

/** Break */
class Break_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Break_AST, AST_Tree);
};

NODE_FACTORY(Break_AST, BREAK);

/** Continue */
class Continue_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Continue_AST, AST_Tree);
};

NODE_FACTORY(Continue_AST, CONTINUE);

/** If*/
class If_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(If_AST, AST_Tree);
};

NODE_FACTORY(If_AST, IF);

/** While */
class While_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(While_AST, AST_Tree);
};

NODE_FACTORY(While_AST, WHILE);

/** For */
class For_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(For_AST, AST_Tree);
};

NODE_FACTORY(For_AST, FOR);

/** def */
class Def_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Def_AST, AST_Tree);
};

NODE_FACTORY(Def_AST, DEF);

/** Method */
class Method_AST : public Def_AST {
protected:
    NODE_CONSTRUCTORS(Method_AST, Def_AST);
};

NODE_FACTORY(Method_AST, METHOD);

/** Formalslist*/
class Formalslist_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Formalslist_AST, AST_Tree);
};

NODE_FACTORY(Formalslist_AST, FORMALS_LIST);

/** Class */
class Class_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Class_AST, AST_Tree);
};

NODE_FACTORY(Class_AST, CLASS);

/** Native */
class Native_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Native_AST, AST_Tree);
};

NODE_FACTORY(Native_AST, NATIVE);

/** TypeFormalsList*/
class TypeFormalsList_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(TypeFormalsList_AST, AST_Tree);
};

NODE_FACTORY(TypeFormalsList_AST, TYPE_FORMALS_LIST);

/** TypedID */
class TypedID_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(TypedID_AST, AST_Tree);

    void addTargetDecls (Decl* enclosing) {
        child(0) -> addTargetDecls(enclosing);
    }
};

NODE_FACTORY(TypedID_AST, TYPED_ID);

/** Assign */
class Assign_AST : public AST_Tree {
protected:
    NODE_CONSTRUCTORS(Assign_AST, AST_Tree);
};

NODE_FACTORY(Assign_AST, ASSIGN);



