/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "dast.h"
#include "dast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/***** PRINT *****/

/**       */
class Print_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Print_AST, AST_Tree);
    void codeGen ()
    {
        cout << "__print__(";
        for_each_child_var(c, this) {
            c->codeGen();
        } end_for;
        cout << ");" << endl;
        //PASSDOWN (this, codeGen(), 0);
    }

};

NODE_FACTORY (Print_AST, PRINT);


/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class Println_AST : public Print_AST {
protected:

    NODE_CONSTRUCTORS (Println_AST, Print_AST);

    const char* externalName () {
	return "println";
    }

};

NODE_FACTORY (Println_AST, PRINTLN);


/***** STMT_LIST *****/

/** A list of statements. */
class StmtList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (StmtList_AST, AST_Tree);

};

NODE_FACTORY (StmtList_AST, STMT_LIST);


/***** DEF *****/

/** def ID(...): ... */
class Def_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Def_AST, AST_Tree);

    Decl* getDecl (int k = 0) {
        return child (0)->getDecl ();
    }

    AST_Ptr getId () {
        return child (0);
    }

    void codeGen() {
        const char* temp = child(2)->child(0)->as_string().c_str();
        if (((std::string) temp).compare("int") != 0 && ((std::string) temp).compare("bool") != 0) {
            if (((std::string) temp).compare("str") == 0) {
                temp = "char*";
            } else {
                temp = "void";
            }
        }
        //fprintf(stderr, "haha:%s\n", temp);
        cout << temp;
        cout << " " << getId()->as_string();
        cout << "(";
        child(1)->codeGen();
        cout << ")" << endl <<  "{" << endl;
        for (unsigned int i = 2; i < arity(); i++) {
            child(i)->codeGen();
        }
        cout << "}" << endl;
    }

};

NODE_FACTORY (Def_AST, DEF);

/***** METHOD *****/

/**  def ID(...): ... (in class)     */
class Method_AST : public Def_AST {
protected:

    NODE_CONSTRUCTORS (Method_AST, Def_AST);

};

NODE_FACTORY (Method_AST, METHOD);

/***** FORMALS_LIST *****/

/** ... (E1, ...)  */
class FormalsList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (FormalsList_AST, AST_Tree);

};

NODE_FACTORY (FormalsList_AST, FORMALS_LIST);


/***** NATIVE *****/

/** native "foreign function name" */
class Native_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Native_AST, AST_Tree);

    void codeGen () {
        
    }


};

NODE_FACTORY (Native_AST, NATIVE);

/***** CLASS *****/

/** class ID of [...]: ...  */
class Class_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Class_AST, AST_Tree);

    Decl* getDecl (int k = 0) {
        return child (0)->getDecl ();
    }

private:
};

NODE_FACTORY (Class_AST, CLASS);

/***** TYPE_FORMALS_LIST *****/

/** of [$T, ...]      */
class TypeFormalsList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (TypeFormalsList_AST, AST_Tree);

};

NODE_FACTORY (TypeFormalsList_AST, TYPE_FORMALS_LIST);


/***** ASSIGN *****/

/** TARGET(s) = EXPR */
class Assign_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (Assign_AST, Typed_Tree);

};

NODE_FACTORY (Assign_AST, ASSIGN);

/***** BREAK *****/

/** break */
class Break_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Break_AST, AST_Tree);

};

NODE_FACTORY (Break_AST, BREAK);

/***** CONTINUE *****/

/** continue */
class Continue_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Continue_AST, AST_Tree);

};

NODE_FACTORY (Continue_AST, CONTINUE);


/***** FOR *****/

/**  for target in exprs: body [ else: body ]     */
class For_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (For_AST, AST_Tree);

};

NODE_FACTORY (For_AST, FOR);


/***** RETURN *****/

/**  return EXPR */
class Return_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Return_AST, AST_Tree);

    void codeGen() {
        cout << "return ";
        PASSDOWN(this, codeGen(), 0);
        cout << ";" << endl;
    }

};

NODE_FACTORY (Return_AST, RETURN);


/***** IF *****/

/** if COND: STMT else: STMT */
class If_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (If_AST, AST_Tree);
    
    void codeGen ()
    {
        cout << "if (";
        child(0)->codeGen();
        cout << ") {" << endl;
        child(1)->codeGen();
        cout << "}" << endl;
        if (arity() > 2) {
            cout << "else {" << endl;
            child(2)->codeGen();
            cout << "}" << endl;
        }
    }

};

NODE_FACTORY (If_AST, IF);


/***** WHILE *****/

/** while COND: STMT else: STMT */
class While_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (While_AST, AST_Tree);

    void codeGen ()
    {
        cout << "while (";
        child(0)->codeGen();
        cout << ") {" << endl;
        child(1)->codeGen();
        cout << "}" << endl;
        if (arity() > 2) {
            cout << "else {" << endl;
            child(2)->codeGen();
            cout << "}" << endl;
        }
    }

};

NODE_FACTORY (While_AST, WHILE);


