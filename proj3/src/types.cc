/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* types.cc: AST subclasses related to types. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "dast.h"
#include "dast-parser.hh"

using namespace std;

/***** AST *****/

static GCINIT _gcdummy;

typedef pair<gcstring, gcstring> string_pair;
static string_pair OPNAMES[] = {
    string_pair("__getindex__", "indexing"),
    string_pair("__setindex__", "indexing"),
    string_pair("__add__", "addition"),
    string_pair("__mul__", "subtraction"),
    string_pair("__floordiv__", "division"),
    string_pair("__mod__", "mod operation"),
    string_pair("__pow__", "exponentiation"),
    string_pair("__neg__", "negation"),
    string_pair("__contains__", "membership test"),
};

static gcmap<gcstring, gcstring> 
OP_MAPPING(&OPNAMES[0], OPNAMES + sizeof(OPNAMES)/sizeof(string_pair));

/*****    TYPE    *****/

Type_Ptr
Type::getType ()
{
    return NULL;
}

AST_Ptr
Type::getId ()
{
    return NULL;
}

int
Type::numParams ()
{
    return -1;
}

Type_Ptr
Type::returnType ()
{
    return NULL;
}

Type_Ptr
Type::paramType (int k)
{
    throw range_error ("function type has no parameters");
}

int
Type::numTypeParams ()
{
    return 0;
}

Type_Ptr
Type::typeParam (int k)
{
    throw range_error ("attempt to reference nonexistent type parameter");
}

Type_Ptr
Type::boundFunctionType ()
{
    return NULL;
}
    
Type_Ptr
Type::binding ()
{
    Type_Ptr type;
    type = this;
    while (type->_binding != type)
        type = type->_binding;
    return type;
}

void
Type::bind (Type_Ptr type)
{
    assert (_binding == this);
    _binding = type;
}

void
Type::unbind ()
{
    _binding = this;
}

bool
Type::isTypeVariable ()
{
    return false;
}

void
Type::setTypeBinding (Type_Ptr type)
{
}

/*****  TYPE VARIABLES *****/

class TypeVar_AST : public Type {
protected:
    
    NODE_CONSTRUCTORS_INIT (TypeVar_AST, Type, _me (NULL));

    bool isTypeVariable () {
        return true;
    }

    Type_Ptr binding () {
        Decl* me = getDecl ();
        assert (me != NULL && me->getAst () != NULL);
        Type_Ptr b = me->getAst ()->asType ();
        if (b->_binding == this)
            return b;
        return b->_binding->binding ();
    }

    void setTypeBinding (Type_Ptr type) {
        Decl* me = getDecl ();
        assert (me != NULL);
        me->setAst (type);
    }

    void _print (ostream& out, int indent, ASTSet& visited) {
        Type_Ptr me = binding ();
        if (me == this || visited.count (me) > 0) {
            out << "(type_var " << lineNumber () << " " 
                << child(0)->as_string ();
            if (getDecl () != NULL)
                out << " " << getDecl ()->getIndex ();
            out << ")";
        } else
            print (me, out, indent, visited);
    }

    gcstring as_string () const {
        return child (0)->as_string ();
    }

    Decl* getDecl () {
        return _me;
    }

    void setDecl (Decl* decl) {
        _me = decl;
    }

private:

    Decl* _me;

};

NODE_FACTORY (TypeVar_AST, TYPE_VAR);


/***** FUNCTION TYPES *****/

class FunctionType_AST: public Type {
protected:

    bool isFunctionType () {
        return true;
    }

    int numParams () {
        return arity () - 1;
    }

    Type_Ptr paramType (int k) {
        return child (k + 1)->asType ();
    }

    Type_Ptr returnType () {
        return child (0)->asType ();
    }

    int numTypeParams () {
        return arity ();
    }

    Type_Ptr typeParam (int k) {
        return child (k)->asType ();
    }

    Type_Ptr boundFunctionType () {
        if (numParams () == 0)
            return NULL;
        Type_Ptr result = consTree (FUNCTION_TYPE, returnType ())->asType ();
        for (int i = 1; i < numParams (); i += 1)
            result->append(paramType (i));
        return result;
    }

    NODE_CONSTRUCTORS (FunctionType_AST, Type);

};

NODE_FACTORY (FunctionType_AST, FUNCTION_TYPE);


/***** CLASSES *****/

class ClassType_AST: public Type {
protected:

    NODE_CONSTRUCTORS (ClassType_AST, Type);

    AST_Ptr getId () {
        return child (0);
    }

    Decl* getDecl () {
        return getId ()->getDecl ();
    }

    void setDecl (Decl* decl) {
        child (0)->setDecl (decl);
    }

    int numTypeParams () {
        return arity () - 1;
    }

    Type_Ptr typeParam (int k) {
        return child (k + 1)->asType ();
    }

};

NODE_FACTORY (ClassType_AST, TYPE);



