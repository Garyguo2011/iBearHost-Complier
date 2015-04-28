/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* exprs.cc: AST subclasses related to expressions. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "dast.h"
#include "dast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/*****   Typed_Tree   *****/

Type_Ptr
Typed_Tree::getType ()
{
    if (_type == NULL)
        setType (computeType ());
    return _type;
}

void
Typed_Tree::setType (Type_Ptr type)
{
    _type = type;
}

AST_Ptr
Typed_Tree::post_make ()
{
    if (arity () > 0 && child (arity () - 1)->isType ()) {
        setType (child (arity () - 1)->asType ());
        replace (arity () - 1, make_list ());
    }
    return this;
}


/*****   NONE, TRUE, FALSE     *****/

static Type_Ptr noneType;

class None_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (None_AST, Typed_Tree);

    Type_Ptr computeType () {
        if (noneType == NULL)
            noneType = noneDecl->asType ();
        return noneType;
    }

};

NODE_FACTORY(None_AST, NONE);

static Type_Ptr boolType;

class True_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (True_AST, Typed_Tree);

    Type_Ptr computeType () {
        if (boolType == NULL)
            boolType = boolDecl->asType ();
        return boolType;

    }

    void codeGen () {
        cout << "__cons_bool__ ("
             << 1
             << ")";
    }

};

NODE_FACTORY(True_AST, TRUE);


class False_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (False_AST, Typed_Tree);

    Type_Ptr computeType () {
        if (boolType == NULL)
            boolType = boolDecl->asType ();
        return boolType;
    }

    void codeGen () {
        cout << "__cons_bool__ ("
             << 0
             << ")";
    }

};

NODE_FACTORY(False_AST, FALSE);


/*****   CALLS    *****/

/** The supertype of "callable" things, including ordinary calls,
 *  binary operators, unary operators, subscriptions, and slices. */

class Callable : public Typed_Tree {
protected:

    NODE_BASE_CONSTRUCTORS (Callable, Typed_Tree);
    
    /** Returns the expression representing the quantity that is
     *  called to evaluate this expression. */
    virtual AST_Ptr calledExpr () {
        return child (0);
    }

    /** Returns the number of actual parameters in this call. */
    virtual int numActuals () {
        return arity () - 1;
    }

    /** Return the Kth actual parameter in this call. */
    virtual AST_Ptr actualParam (int k) {
        return child (k + 1);
    }

    /** Set the Kth actual parameter in this call to EXPR. */
    virtual void setActual (int k, AST_Ptr expr) {
        replace (k + 1, expr);
    }

public:

};

/** A function call. */
class Call_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Call_AST, Callable);

    void codeGen() {
        // Don't know whether add semi-colon or not
        cout << child(0)->as_string() << "(";
        for (unsigned int i = 1; i < arity(); i++) {
            child(i)->codeGen();
            if (i < arity()-1)
            {
                cout << ", ";   
            }
        }
        cout << ")" << endl;
    }

};

NODE_FACTORY (Call_AST, CALL);

/***** CALL1 *****/

/** __init__(new T, ...)      */
class Call1_AST : public Call_AST {
protected:

    NODE_CONSTRUCTORS (Call1_AST, Call_AST);

};

NODE_FACTORY (Call1_AST, CALL1);

/***** NEW *****/

/**  new T     */
class New_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (New_AST, Typed_Tree);

};

NODE_FACTORY (New_AST, NEW);


/** A binary operator. */
class Binop_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Binop_AST, Callable);

    void codeGen() {
        child(0)->codeGen();
        cout << "(";
        child(1)->codeGen();
        cout << ", ";
        child(2)->codeGen();
        cout << ")";
    }

};    

NODE_FACTORY (Binop_AST, BINOP);

/***** COMPARE *****/

/** A comparison yielding bool */
class Compare_AST : public Binop_AST {
protected:

    NODE_CONSTRUCTORS (Compare_AST, Binop_AST);

};

NODE_FACTORY (Compare_AST, COMPARE);


/***** LEFT_COMPARE *****/

/** A comparison yielding its second operand's type. */
class LeftCompare_AST : public Binop_AST {
protected:

    NODE_CONSTRUCTORS (LeftCompare_AST, Binop_AST);

};

NODE_FACTORY (LeftCompare_AST, LEFT_COMPARE);


/** A unary operator. */
class Unop_AST : public Callable {

    NODE_CONSTRUCTORS (Unop_AST, Callable);

    void codeGen() {
        child(0)->codeGen();
        cout << "(";
        child(1)->codeGen();
        cout << ")";
    }

};    

NODE_FACTORY (Unop_AST, UNOP);


/***** SUBSCRIPTION *****/

/** E1[E2] */
class Subscription_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Subscription_AST, Callable);

    void codeGen() {
        child(0)->codeGen();
        cout << "(";
        child(1)->codeGen();
        cout << ", ";
        child(2)->codeGen();
        cout << ")";

    }

};

NODE_FACTORY (Subscription_AST, SUBSCRIPT);

class Subscript_Assign_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Subscript_Assign_AST, Callable);

};

NODE_FACTORY (Subscript_Assign_AST, SUBSCRIPT_ASSIGN);
    
    
/***** SLICING *****/

/** E1[E2:E3] */
class Slicing_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Slicing_AST, Callable);

    void codeGen() {
        child(0)->codeGen();
        cout << "(";
        child(1)->codeGen();
        cout << ", ";
        child(2)->codeGen();
        cout << ", ";
        child(3)->codeGen();
        cout << ")";
    }

};

NODE_FACTORY (Slicing_AST, SLICE);

class Slicing_Assign_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Slicing_Assign_AST, Callable);

};

NODE_FACTORY (Slicing_Assign_AST, SLICE_ASSIGN);
    

/***** ATTRIBUTEREF *****/

/** E.ID */
class AttributeRef_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (AttributeRef_AST, Typed_Tree);

    AST_Ptr getId () {
        return child (1);
    }

    Decl* getDecl () {
        return getId ()->getDecl ();
    }

};

NODE_FACTORY (AttributeRef_AST, ATTRIBUTEREF);

/***** TUPLE *****/

/** (E1, ...)  */
class Tuple_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (Tuple_AST, Typed_Tree);

    void codeGen() {
        switch (arity()) {
            case 0:
                cout << "__cons_tuple0__()";
                break;
            case 1:
                cout << "__cons_tuple1__(";
                child(0)->codeGen();
                cout << ")";
                break;
            case 2:
                cout << "__cons_tuple2__(";
                child(0)->codeGen();
                cout << ", ";
                child(1)->codeGen();
                cout << ")";
                break;
            case 3:
                cout << "__cons_tuple3__(";
                child(0)->codeGen();
                cout << ", ";
                child(1)->codeGen();
                cout << ", ";
                child(2)->codeGen();
                cout << ")";
                break;
        }
    }

};

NODE_FACTORY (Tuple_AST, TUPLE);

/***** TARGET_LIST *****/

/** (TARGET, ...) on left-hand side of assignment, for. */
class TargetList_AST : public Tuple_AST {
protected:

    NODE_CONSTRUCTORS (TargetList_AST, Tuple_AST);

};

NODE_FACTORY (TargetList_AST, TARGET_LIST);


/***** LIST_DISPLAY *****/

/** [E1, ...]  */
class ListDisplay_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (ListDisplay_AST, Typed_Tree);

    void codeGen() {
        cout << "__cons_list__("
             << arity();
        if (arity() != 0) {
            cout << ", ";
        }
        for (unsigned int i = 0; i < arity(); i++) {
            child(i)->codeGen();
            if (i < arity()-1) {
                cout << ", ";
            }
        }
        cout << ")";
    }

};

NODE_FACTORY (ListDisplay_AST, LIST_DISPLAY);


/***** DICT_DISPLAY *****/

/** { a: b, ... }  */
class DictDisplay_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (DictDisplay_AST, Typed_Tree);

    void codeGen() {
        // getType()->print(cerr, 4);
        // cerr << "\n";
        // cerr << getType()->arity() << ", size\n";
        const char* temp = getType()->child(1)->child(0)->as_string().c_str();
        cout << "__cons_dict";
        cout << temp;
        cout << "__("
            << arity() << ", ";
        for (unsigned int i = 0; i < arity(); i++) {
            child(i)->codeGen();
            if (i < arity()-1) {
                cout << ", ";
            }
        }
        cout << ")";
    }
};

NODE_FACTORY (DictDisplay_AST, DICT_DISPLAY);

class Pair_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (Pair_AST, Typed_Tree);

    void codeGen() {
        cout << "__cons_pair__(";
        for (unsigned int i = 0; i < arity(); i++) {
            child(i)->codeGen();
            if (i < arity()-1) {
                cout << ", ";
            }
        }
        cout << ")";
    }
};

NODE_FACTORY (Pair_AST, PAIR);


/** A class of expression in which its subexpressions must agree as to
 *  type and its value's type is that of its subexpressios. */
class BalancedExpr : public Typed_Tree {
protected:

    NODE_BASE_CONSTRUCTORS (BalancedExpr, Typed_Tree);

};

/***** IF_EXPR *****/

/**  E1 if Cond else E2  */
class IfExpr_AST : public BalancedExpr {
protected:

    NODE_CONSTRUCTORS (IfExpr_AST, BalancedExpr);

};              


NODE_FACTORY (IfExpr_AST, IF_EXPR);

/***** AND *****/

/** E1 and E2 */
class And_AST : public BalancedExpr {
protected:

    NODE_CONSTRUCTORS (And_AST, BalancedExpr);

};

NODE_FACTORY (And_AST, AND);

/***** OR *****/

/** E1 or E2 */
class Or_AST : public BalancedExpr {
protected:

    NODE_CONSTRUCTORS (Or_AST, BalancedExpr);

};

NODE_FACTORY (Or_AST, OR);


/***** NOT *****/

/** not E */
class Not_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (Not_AST, Typed_Tree);

};

NODE_FACTORY (Not_AST, NOT);


/***** NEXT_VALUE *****/

/** Used in slice_assign and subscript assign to indicate value. */
class NextValue_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (NextValue_AST, Typed_Tree);

};

NODE_FACTORY (NextValue_AST, NEXT_VALUE);

/***** TYPED_ID *****/

/** ID::TYPE */
class TypedId_AST : public AST_Tree {
protected:

    NODE_CONSTRUCTORS (TypedId_AST, AST_Tree);

    AST_Ptr getId () {
        return child (0);
    }

    Decl* getDecl () {
        return getId ()->getDecl ();
    }

    void setDecl (Decl* decl) {
        getId ()->setDecl (decl);
    }

    Type_Ptr getType () {
        return child (1)->asType ();
    }

    void codeGen() {
        // To be implemented. Right now assuming undefined type_var to be void at this time.
        const char* temp = getType()->child(0)->as_string().c_str();
        // if (((std::string) temp).compare("int") != 0 && ((std::string) temp).compare("bool") != 0) {
        //     if (((std::string) temp).compare("str") == 0) {
        //         temp = "char*";
        //     } else {
        //         temp = "PyObject";
        //     }
        // }
        // fprintf(stderr, "%s\n", temp);
        // if (getType()->arity() == 3) {
        //     cerr << getType()->child(1)->child(0)->as_string();
        //     cerr << "\n";
        // }
        

        if (((std::string) temp).compare("str") == 0) {
            temp = "PyStr*";
        }
        else if (((std::string) temp).compare("int") == 0) {
            temp = "PyInt*";
        }
        else if (((std::string) temp).compare("bool") == 0) {
            temp = "PyBool*";
        }
        else if (((std::string) temp).compare("str") == 0) {
            temp = "PyStr*";
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
        } else {
            temp = "PyValue";
        }
        cout << temp;
        cout << " " << getId()->as_string();
    }

};

NODE_FACTORY (TypedId_AST, TYPED_ID);
