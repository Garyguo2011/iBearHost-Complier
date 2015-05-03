/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "dast.h"
#include "dast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/** All ids used so far */
vector<string> names; 
/** All local ids used so far */
vector<string> names_local;
vector<string> names_func;

/** Bookkeeping for names*/
/** If name is new add to names, same with local*/
bool add_to_names(string temp) {
    if (find(names.begin(), names.end(), temp) == names.end()) {
        names.push_back (temp);
        return true;
    }
    return false;
}

bool add_to_names_local(string temp) {
    if (find(names_local.begin(), names_local.end(), temp) == names_local.end()) {
        names_local.push_back (temp);
        return true;
    }
    return false;
}

/** The peek versions, doesn't do add*/
bool add_to_names_peek(string temp) {
    if (find(names.begin(), names.end(), temp) == names.end()) {
        return true;
    }
    return false;
}

bool add_to_names_local_peek(string temp) {
    if (find(names_local.begin(), names_local.end(), temp) == names_local.end()) {
        return true;
    }
    return false;
}
/***** PRINT *****/

class Print_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Print_AST, AST_Tree);

    /** Output code which invokes __print__ function
     * 
     */
    void codeGen ()
    {
        cout << "__print__(";
        cout << arity();
        if (arity() != 0) {
            cout << ", ";
        }
        for (unsigned int i = 0; i < arity(); i++) {
            child(i)->codeGen();
            if (i < arity()-1) {
                cout << ", ";
            }
        }
        cout << ");" << endl;
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

    /** Same as the print node but call __newline__ to 
     * generate the newline.
     */
    void codeGen() {
        Print_AST::codeGen();
        cout << "__newline__();" << endl;
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

    /* Output return type followed by function header 
     * and then function body wrapped in struct to carry
     * local variables from outer scope
     */
    void codeGen() {
        stringstream ss0;
        ss0 << getId()->as_string() << "_" << getId()->getDecl()->getIndex();
        names_func.push_back(ss0.str());

        cout << "struct " << ss0.str() << "_local ";
        cout << " : public PyObject {" << endl;
        cout << convertAsPyType((Type_Ptr) child(2));
        cout << " ";
        getId()->codeGen();
        cout << "(";
        child(1)->codeGen();
        cout << ")" << endl <<  "{" << endl;
        /** Case of native function
         *  Output return followed by native code
         */
        if (child(3)->oper()->syntax() == NATIVE) {
            cout << "return ";
            child(3)->child(0)->codeGenNative();
            cout << "(";
            for (unsigned int i = 0; i < child(1)->arity(); i++) {
                child(1)->child(i)->child(0)->codeGen();
                if (i < child(1)->arity()-1) {
                    cout << ", ";
                }
            }
            cout << ");" << endl;
        }else {
            /** First initialize all local variables*/
            for (unsigned int i = 3; i < arity(); i++) {
                AST_Ptr c = child(i);

                if (c->oper()->syntax() == ASSIGN) {
                    AST_Ptr my_id = c->child(0);
                    stringstream ss;
                    ss << my_id->as_string() << "_" << my_id->getDecl()->getIndex();
                    string temp;
                    ss >> temp;
                    if (add_to_names_peek(temp) && add_to_names_local_peek(temp)) {
                        cout << "static ";
                    }
                    c->codeGen();
                } 
            }
            for (unsigned int i = 3; i < arity()-1; i++) {
                AST_Ptr c = child(i);
                if (c->oper()->syntax() != ASSIGN) {
                    c->codeGen();
                    c->codeGenSemicolonForCall();
                } 
            }
            if (child(arity()-1)->oper()->syntax() != RETURN) {
                if (child(arity()-1)->oper()->syntax() != ASSIGN) {
                    child(arity()-1)->codeGen();
                    child(arity()-1)->codeGenSemicolonForCall();
                }
                cout << "return __cons_str__(\"None\");" << endl;
            } else {
                child(arity()-1)->codeGenRecursiveCall(this);
            }
        }
        cout << "}" << endl;
        cout << "} ";
        cout << getId()->as_string() << "_" << getId()->getDecl()->getIndex() << ";" << endl;
        cout << "\n";
    }

    // void codeGenInternalFunc() {
    //     cout << "struct " << getId()->as_string() << getId()->getDecl()->getIndex() << "_local ";
    //     cout << "{" << endl;
    //     codeGen();
    //     cout << "} ";
    //     cout<< getId()->as_string() << "_" << getId()->getDecl()->getIndex() << ";" << endl;

    // }
};

NODE_FACTORY (Def_AST, DEF);

/***** METHOD *****/

/**  def ID(...): ... (in class)     */
class Method_AST : public Def_AST {
protected:

    NODE_CONSTRUCTORS (Method_AST, Def_AST);

/** Generate code for method, no need to wrap in struct
     * in case of __init__ replace with class name
     */
    void codeGen() {
        stringstream ss0;
        ss0 << getId()->as_string() << "_" << getId()->getDecl()->getIndex();
        names_func.push_back(ss0.str());

        cout << convertAsPyType((Type_Ptr) child(2));
        cout << " ";
        getId()->codeGen();
        cout << "(";
        child(1)->codeGen();
        cout << ")" << endl <<  "{" << endl;
        /** Case of native function
         *  Output return followed by native code
         */
        if (child(3)->oper()->syntax() == NATIVE) {
            cout << "return ";
            child(3)->child(0)->codeGenNative();
            cout << "(";
            for (unsigned int i = 0; i < child(1)->arity(); i++) {
                child(1)->child(i)->child(0)->codeGen();
                if (i < child(1)->arity()-1) {
                    cout << ", ";
                }
            }
            cout << ");" << endl;
        }else {
            for (unsigned int i = 3; i < arity(); i++) {
                child(i)->codeGen();
            }
            if (child(arity()-1)->oper()->syntax() != RETURN) {
                cout << "return NULL;" << endl;
            }
        }
        cout << "}" << endl;
    }


    /** codeGen for __init__ */
    void codeGenInit(AST_Ptr myclass) {
        AST_Ptr class_id = myclass->getId();
        cout << (std::string) (class_id->as_string().c_str());
        cout << " (";
        child(1)->codeGen();
        cout << ")" << endl <<  "{" << endl;
        /** Initialize all instance variables in constructor*/
        for (unsigned int i = 2; i < myclass->arity(); i++) {
            AST_Ptr c = myclass->child(i);
            if (c->oper()->syntax() == ASSIGN) {
                c->codeGen();
            }
        }
        for (unsigned int i = 3; i < arity(); i++) {
            child(i)->codeGen();
        }
        cout << "}" << endl;

    }

};

NODE_FACTORY (Method_AST, METHOD);

/***** FORMALS_LIST *****/

/** ... (E1, ...)  */
class FormalsList_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (FormalsList_AST, AST_Tree);

    /** Join code of each formal with commas */
    void codeGen() {
        for (unsigned int i = 0; i < arity(); i++) {
            stringstream ss;
            ss << child(i)->child(0)->as_string() << "_" << child(i)->child(0)->getDecl()->getIndex();
            string temp;
            ss >> temp;
            // if (find(names.begin(), names.end(), temp) == names.end()) {
            //     names.push_back (temp);
            //     // cout << convertAsPyType(child(i)->getType()) << " ";
            // } 
            if (find(names_local.begin(), names_local.end(), temp) == names_local.end()) {
                names_local.push_back (temp);
                // cout << convertAsPyType(child(i)->getType()) << " ";
            }
            child(i)->codeGen();
            if (i < arity()-1
                && ((std::string) child(i)->getId()->as_string().c_str()).compare("self") != 0) {
                cout << ", ";
            }
        }
    }

};

NODE_FACTORY (FormalsList_AST, FORMALS_LIST);


/***** NATIVE *****/

/** native "foreign function name" */
class Native_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Native_AST, AST_Tree);
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

    AST_Ptr getId() {
        return child(0);
    }

    /** Generate code for class definition */
    void codeGen() {
        std::string class_name = (std::string)(child(0)->as_string().c_str());
        /** Only generate code if not predefined class */
        if (class_name.compare("str") != 0 &&
            class_name.compare("int") != 0 &&
            class_name.compare("bool") != 0 &&
            class_name.compare("range") != 0 &&
            class_name.compare("dict") != 0 &&
            class_name.compare("list") != 0 &&
            class_name.compare("tuple0") != 0 &&
            class_name.compare("tuple1") != 0 &&
            class_name.compare("tuple2") != 0 &&
            class_name.compare("tuple3") != 0
            ) {
            cout << "class ";
            cout << class_name;
            cout << " : public PyObject {" << endl;
            cout << "public :" << endl;
            /** First generate all variable initializations*/
            for (unsigned int i = 2; i < arity(); i++) {
                AST_Ptr c = child(i);
                if (c->oper()->syntax() == ASSIGN) {
                    c->codeGenVarDecl();
                    cout << ";" << endl;
                }
            }

            /** Then generate all method code */
            for (unsigned int i = 2; i < arity(); i++) {
                AST_Ptr c = child(i);
                if (c->oper()->syntax() == METHOD) {
                    if (((std::string) c->child(0)->as_string().c_str()).compare("__init__") == 0) {
                        c->codeGenInit(this);
                    }
                    else {
                        c->codeGen();
                    }
                }
            }
            cout << "};" << endl;
        }
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

    void codeGen() {
        // print(cerr, 4);
        // cerr << ", assign, with arity of " << arity() << "\n";
        // cerr << "child 0 arity :" << child(0)->arity() << "\n";
        // cerr << "child 1 arity :" << child(1)->arity() << "\n";
        // getType()->print(cerr, 4);
        // cerr << ", as type\n";

        int depth = 0;
        AST_Ptr temp = this;
        while (temp->child(1)->oper()->syntax() == ASSIGN) {
            depth++;
            temp = temp->child(1);
        }
        for (int i0 = 0; i0 <= depth; i0++) {
            if (getAst(1, i0)->child(0)->oper()->syntax() == SUBSCRIPT_ASSIGN){
                getAst(1, i0)->child(0)->child(0)->codeGen();
                cout << "_" << getAst(1, i0)->child(0)->child(0)->getDecl()->getIndex() << ".";
                getAst(1, i0)->child(0)->child(0)->codeGen();
                cout << "(";
                getAst(1, i0)->child(0)->child(1)->codeGen();
                cout << ",";
                getAst(1, i0)->child(0)->child(2)->codeGen();
                cout << ",";
                getAst(1, depth)->child(1)->codeGen();
                cout << ");\n";
            } else if (getAst(1, i0)->child(0)->oper()->syntax() == SLICE_ASSIGN) {
                // def __setslice__(S::list of $a, a::int, b::int, val::list of $a)::list of $a:
                getAst(1, i0)->child(0)->child(0)->codeGen();
                cout << "_" << getAst(1, i0)->child(0)->child(0)->getDecl()->getIndex() << ".";
                getAst(1, i0)->child(0)->child(0)->codeGen();     //__setslice__
                cout << "(";
                getAst(1, i0)->child(0)->child(1)->codeGen();     // S::list of $a
                cout << ",";
                getAst(1, i0)->child(0)->child(2)->codeGen();     // a::int
                cout << ",";
                getAst(1, i0)->child(0)->child(3)->codeGen();     // b::int
                cout << ",";
                getAst(1, depth)->child(1)->codeGen();               // val::list of $a
                cout << ");\n";
            // } else if () {
                // def __setitem__(S::dict of [int, $b], k::int, val::$b)::$b:

            } else if (getAst(1, i0)->child(0)->oper()->syntax() == TYPED_ID && arity() == 2) {
                stringstream ss;
                ss << getAst(1, i0)->child(0)->child(0)->as_string() << "_" << getAst(1, i0)->child(0)->child(0)->getDecl()->getIndex();
                string temp;
                ss >> temp;
                if (add_to_names(temp) && add_to_names_local(temp)) {
                    cout << convertAsPyType(getAst(1, i0)->child(0)->getType()) << " ";
                }
                getAst(1, i0)->child(0)->child(0)->codeGen();
                cout << " = ";
                getAst(1, depth)->child(1)->codeGen();
                cout << ";\n";
            } else if (getAst(1, i0)->child(0)->oper()->syntax() == ATTRIBUTEREF) {
                getAst(1, i0)->child(0)->codeGen();
                cout << " = ";
                getAst(1, depth)->child(1)->codeGen();
                cout << ";" << endl;
            }
            else {
                if (getAst(1, i0)->child(0)->arity() == 0) {
                    if (getAst(1, i0)->child(0)->getDecl()->assignable()) {
                        stringstream ss;
                        ss << getAst(1, i0)->child(0)->as_string() << "_" << getAst(1, i0)->child(0)->getDecl()->getIndex();
                        string temp;
                        ss >> temp;
                        if (add_to_names(temp) && add_to_names_local(temp)) {
                            cout << convertAsPyType(getType()) << " ";
                        }
                        getAst(1, i0)->child(0)->codeGen();
                        cout << " = ";
                        getAst(1, depth)->child(1)->codeGen();
                        cout << ";\n";
                    } else {
                        fatal("This ID can't be assigned.");
                    }
                } else {
                    for (unsigned int i = 1; i < getAst(1, i0)->getType()->arity(); i++) {
                        if (getAst(1, i0)->child(0)->child(i-1)->oper()->syntax() == TYPED_ID) {
                            stringstream ss;
                            ss << getAst(1, i0)->child(0)->child(i-1)->child(0)->as_string() << "_" << getAst(1, i0)->child(0)->child(i-1)->child(0)->getDecl()->getIndex();
                            string temp;
                            ss >> temp;
                            if (add_to_names(temp) && add_to_names_local(temp)) {
                                cout << convertAsPyType((Type_Ptr) getAst(1, i0)->getType()->child(i)) << " ";
                            }
                            getAst(1, i0)->child(0)->child(i-1)->child(0)->codeGen();
                            cout << " = ";
                            getAst(1, depth)->child(1)->child(i-1)->codeGen();
                            cout << ";" << endl;
                        }
                        else {
                            if (getAst(1, i0)->child(0)->child(i-1)->getDecl()->assignable()) {
                                stringstream ss;
                                ss << getAst(1, i0)->child(0)->child(i-1)->as_string()
                                   << "_" << getAst(1, i0)->child(0)->child(i-1)->getDecl()->getIndex();
                                string temp;
                                ss >> temp;

                                if (add_to_names(temp) && add_to_names_local(temp)) {
                                    cout << convertAsPyType((Type_Ptr) getAst(1, i0)->getType()->child(i)) << " ";
                                }

                                getAst(1, i0)->child(0)->child(i-1)->codeGen();
                                cout << " = ";
                                getAst(1, depth)->child(1)->child(i-1)->codeGen();
                                cout << ";" << endl;
                            } else {
                                fatal("This ID can't be assigned.");
                            }
                        }
                    }
                }
            }
        }
    }

    void codeGenVarDecl() {
        if (child(0)->oper()->syntax() == TYPED_ID && arity() == 2) {
            stringstream ss;
            ss << child(0)->child(0)->as_string() << "_" << child(0)->child(0)->getDecl()->getIndex();
            string temp;
            ss >> temp;
            if (add_to_names(temp)) {
                cout << convertAsPyType(child(0)->getType()) << " ";
                child(0)->child(0)->codeGen();
            }

        } else {
            if (child(0)->arity() == 0) {
                stringstream ss;
                ss << child(0)->as_string() << "_" << child(0)->getDecl()->getIndex();
                string temp;
                ss >> temp;
                if (add_to_names(temp)) {
                    cout << convertAsPyType(getType()) << " ";
                    child(0)->codeGen();
                }
            } else {
                for (unsigned int i = 1; i < getType()->arity(); i++) {
                    if (child(0)->child(i-1)->oper()->syntax() == TYPED_ID) {
                        stringstream ss;
                        ss << child(0)->child(i-1)->child(0)->as_string() << "_" << child(0)->child(i-1)->child(0)->getDecl()->getIndex();
                        string temp;
                        ss >> temp;
                        if (add_to_names(temp)) {
                            cout << convertAsPyType((Type_Ptr) getType()->child(i)) << " ";
                            child(0)->child(i-1)->child(0)->codeGen();
                        }
                        cout << ";" << endl;
                    } else {
                        stringstream ss;
                        ss << child(0)->child(i-1)->as_string()
                           << "_" << child(0)->child(i-1)->getDecl()->getIndex();
                        string temp;
                        ss >> temp;

                        if (add_to_names(temp)) {
                            cout << convertAsPyType((Type_Ptr) getType()->child(i)) << " ";
                            child(0)->child(i-1)->codeGen();
                        }
                        cout << ";" << endl;
                    }
                }
            }
        }
    }

};

NODE_FACTORY (Assign_AST, ASSIGN);

/***** BREAK *****/

/** break */
class Break_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Break_AST, AST_Tree);

    void codeGen() {
        cout << "break;";
    }

};

NODE_FACTORY (Break_AST, BREAK);

/***** CONTINUE *****/

/** continue */
class Continue_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Continue_AST, AST_Tree);

    void codeGen() {
        cout << "continue;";
    }

};

NODE_FACTORY (Continue_AST, CONTINUE);


/***** FOR *****/

/**  for target in exprs: body [ else: body ]     */
class For_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (For_AST, AST_Tree);

    void codeGen ()
    {

        stringstream ss0;
        ss0 << child(0)->as_string() << "_" << child(0)->getDecl()->getIndex();
        if (add_to_names(ss0.str())) {
            cout << AST::convertAsPyType(child(0)->getDecl()->getType ());
            cout << " ";
            if (child(0)->oper()->syntax() != TYPED_ID) {
                child(0)->codeGen();
            } else {
                child(0)->child(0)->codeGen();
            }
            cout << ";" << endl;
        }

        stringstream ss;
        ss << "index_";
        ss << child(0)->getDecl()->getIndex();
        string temp;
        ss >> temp;
        cout << "for (";
        cout << "int " << temp  << " = 0; ";
        cout << temp;
        cout << " < ";
        child(1)->codeGen();
        cout << "->getSize(); ";
        cout << temp << "++";
        cout << ") {" << endl;

        if (child(0)->oper()->syntax() == TYPED_ID) {
            child(0)->child(0)->codeGen();
        } else {
            child(0)->codeGen();
        }
        cout << " = ";
        cout << "(" << AST::convertAsPyType(child(0)->getDecl()->getType ()) << ") ";
        child(1)->codeGen();
        cout << "->get(" << temp << ");" << endl;
        child(2)->codeGen();

        cout << "}" << endl;
        if (arity() > 3) {
            // cout << "else {" << endl;
            child(3)->codeGen();
            // cout << "}" << endl;
        }
    }

};

NODE_FACTORY (For_AST, FOR);


/***** RETURN *****/

/**  return EXPR */
class Return_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (Return_AST, AST_Tree);

    void codeGen() {
        cout << "return ";
        for (unsigned int i = 0; i < arity(); i++) {
            if (child(i)->oper()->syntax() == ID) {
                stringstream ss;
                ss << child(i)->as_string() << "_" << child(i)->getDecl()->getIndex();
                string temp;
                ss >> temp;
                if (find(names_func.begin(), names_func.end(), temp) != names_func.end()) {
                    cout << "(";
                    child(i)->codeGen();
                    cout << ") ";
                    child(i)->codeGen();
                    cout << ".";
                    child(i)->codeGen();
                    // cout << "()";
                } else {
                    child(i)->codeGen();
                }
            } else {
                    child(i)->codeGen();
            }
        }
        cout << ";" << endl;
    }

    void codeGenRecursiveCall(AST_Ptr func_id) {
        // func_id->print(cerr, 4);
        // cerr << "\n************************************\n";
        cout << "return ";
        for (unsigned int i = 0; i < arity(); i++) {
            if (child(i)->oper()->syntax() == CALL
                || child(i)->oper()->syntax() == BINOP
                || child(i)->oper()->syntax() == UNOP) {
                child(i)->codeGenRecursiveCall(func_id->getId());
            } else if (child(i)->oper()->syntax() == ID) {
                stringstream ss;
                ss << child(i)->as_string() << "_" << child(i)->getDecl()->getIndex();
                string temp;
                ss >> temp;
                // cerr << "number of func: " << names_func.size() << "\n";
                if (find(names_func.begin(), names_func.end(), temp) != names_func.end()) {
                    // cout << "(";
                    // child(i)->codeGen();
                    // cout << "::";
                    // child(i)->codeGen();
                    // cout << ") ";
                    // child(i)->codeGen();
                    // cout << ".";
                    child(i)->codeGen();
                    // cout << "()";
                } else {
                    child(i)->codeGen();
                }
            }
            else {
                child(i)->codeGen();
            }
        }
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
        cout << "if (__eval_bool__(";
        child(0)->codeGen();
        cout << ")) {" << endl;
        child(1)->codeGen();
        cout << "}" << endl;
        if (arity() > 2) {
            if (child(2)->oper()->syntax() == IF) {
                cout << "else ";
                // child(2)->print(cerr, 4);
                // cerr << ",lala \n";
                child(2)->codeGen();
            } else {
                cout << "else {" << endl;
                child(2)->codeGen();
                cout << "}" << endl;
            }
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
        for_each_child(c, this->child(1)) {
            c->codeGenVarDecl();
            cout << ";" << endl;
        } end_for;
        cout << "while (__eval_bool__(";
        child(0)->codeGen();
        cout << ")) {" << endl;
        child(1)->codeGen();
        cout << "}" << endl;
        if (arity() > 2) {
            // cout << "else {" << endl;
            child(2)->codeGen();
            // cout << "}" << endl;
        }
    }

};

NODE_FACTORY (While_AST, WHILE);
