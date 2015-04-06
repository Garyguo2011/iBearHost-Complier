/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* types.cc: AST subclasses related to types. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

/***** AST *****/

static GCINIT _gcdummy;

void
AST::resolveTypesOuter (Decl* context) 
{
    freezeDecls (true);
    freezeDecls (false);
}


/*****   UNIFIER  *****/

const Unifier IdentityUnifier;

bool
Unifier::isBound (Type_Ptr x) const
{
    TypeMap::const_iterator m = bindings.find (x);
    return m != bindings.end () && (*m).second != x;
}

Type_Ptr
Unifier::binding (Type_Ptr x) const
{
    while (true) {
        TypeMap::const_iterator k = bindings.find (x);
        if (k == bindings.end () || x == (*k).second)
            return x;
        x = k->second;
    }
}

void
Unifier::bind (Type_Ptr x, Type_Ptr y)
{
    Type_Ptr x1 = binding (x);
    if (x1->isTypeVariable () && bindings.count (x1) == 0)
        _numBound += 1;
    bindings[x1] = binding (y);
}
    
void
Unifier::swap (Unifier& other)
{
    bindings.swap (other.bindings);
}


void
Unifier::setBindings ()
{
    for (TypeMap::iterator k = bindings.begin (); k != bindings.end (); k++)
        k->first->setTypeBinding (k->second);
}


/** As for unify, but SUBST has an undefined state if result is
 *  false. */
static bool
unify1 (Type_Ptr t0, Type_Ptr t1, Unifier& subst)
{
    t0 = subst.binding (t0);
    t1 = subst.binding (t1);
    if (t0 == t1)
        return true;
    if (t0->isTypeVariable ()) {
        subst.bind (t0, t1);
        return true;
    }
    subst.bind (t1, t0);
    if ((t0->getId () == NULL) != (t1->getId () == NULL))
        return false;
    if (t0->getId () != NULL) {
        if (t0->getId ()->getDecl () != t1->getId ()->getDecl ())
            return false;
    }
    if (t0->numTypeParams () != t1->numTypeParams ())
        return false;
    for (int i = 0; i < t0->numTypeParams (); i += 1) {
        if (!unify1 (t0->typeParam (i), t1->typeParam (i), subst))
            return false;
    }
    return true;
}

bool
unify (Type_Ptr t0, Type_Ptr t1, Unifier& subst)
{
    Unifier s (subst);
    if (unify1 (t0, t1, subst))
        return true;
    s.swap (subst);
    return false;
}

bool
unify (Type_Ptr t0, Type_Ptr t1)
{
    Unifier subst;
    if (unify1 (t0, t1, subst)) {
        subst.setBindings ();
        return true;
    } else
        return false;
}

bool
unifies (Type_Ptr t0, Type_Ptr t1, const Unifier& subst)
{
    Unifier s (subst);
    return unify1 (t0, t1, s);
}


/*****    TYPE    *****/

Type_Ptr
Type::getType ()
{
    error (this, "a type may not be used as a value in this dialect");
    return makeVar ();
}

AST_Ptr
Type::getId ()
{
    if (isFunctionType() && isUnbound()) {
        return NULL;
    } else {
        return this->child(0);
    }
}

int
Type::numParams ()
{
    if (isFunctionType()) {
        return this->child(1)->arity();
    }
    return -1;
}

Type_Ptr
Type::returnType ()
{
    if (isFunctionType()) {
        return (Type_Ptr) this->child(0);
    }
    return NULL;
}

Type_Ptr
Type::paramType (int k)
{
    if (isFunctionType()) {
        if (0 <= k && k < numParams()) {
            return (Type_Ptr) this->child(1)->child(k);
        } else {
            throw range_error ("function type has no parameters");
        }
    }
}

int
Type::numTypeParams ()
{
    return numParams() + 1;
}

Type_Ptr
Type::typeParam (int k)
{
    if (0 <= k && k < numTypeParams()) {
        if (k == 0) {
            return this->returnType();
        } else {
            return this->paramType(k-1);
        }
    } else {
        throw range_error ("type has no type parameters");
    }
}

Type_Ptr
Type::boundFunctionType ()
{
    if (isFunctionType()){
        if (this->arity() <= 1){
            return NULL;
        } else {
            std::vector <AST_Ptr> new_list;
            for (int i = 1; i < this->child(1)->arity(); i++){
                new_list.push_back(this->child(1)->child(i));
            }
            Type_Ptr new_type_list = (Type_Ptr) AST::make_tree(TYPE_LIST, &new_list[0], &new_list[new_list.size()]);
            return (Type_Ptr) consTree(FUNCTION_TYPE, this->child(0), new_type_list);
        }
    }
    return NULL;
}
    
const Environ*
Type::getEnviron ()
{
    return this->getDecl()->getEnviron();
}

Type_Ptr
Type::makeVar ()
{
    AST_Ptr dummy[1];

    Type_Ptr result = AST::make_tree (TYPE_VAR, dummy, dummy)->asType ();
    result->addDecl (makeTypeVarDecl (result->as_string (), result));
    return result;
}

Type_Ptr
Type::binding ()
{
    return this;
}

bool
Type::isTypeVariable ()
{
    return false;
}

bool
Type::hasFreeVariables (Type_Ptr type)
{
    ASTSet visited;
    return type->hasFreeVariables (visited);
}

bool
Type::hasFreeVariables (ASTSet& visited)
{
    if (visited.count (this) == 0) {
        visited.insert (this);
        for_each_child (c, this) {
            if (c->asType ()->hasFreeVariables (visited))
                return true;
        } end_for;
    }
    return false;
}

void
Type::setTypeBinding (Type_Ptr type)
{
}

static Type_Ptr
freshen (Type_Ptr type, TypeMap& freshMap)
{
    Type_Ptr result;
    if (freshMap.count (type) != 0)
        return freshMap[type];

    Type_Ptr type1 = type->binding ();
    if (type1 != type)
        result = freshen (type1, freshMap);
    else if (type->isTypeVariable ())
        result = Type::makeVar ();
    else if (type->numTypeParams () == 0)
        result = type;
    else {
        result = consTree (type->oper ()->syntax ())->asType ();
        freshMap[type] = result;

        for (size_t i = 0; i < type->arity () - type->numTypeParams (); i += 1)
            result->append (type->child (i));
        for (int i = 0; i < type->numTypeParams (); i += 1) {
            Type_Ptr p0 = type->typeParam (i);
            result->append (freshen (p0, freshMap));
        }
    }
    freshMap[type] = result;
    return result;
}

Type_Ptr
freshen (Type_Ptr type)
{
    TypeMap freshMap;
    return freshen (type, freshMap);
}

void
freshen (gcvector<Type_Ptr>& types)
{
    TypeMap freshMap;

    for (size_t i = 0; i < types.size (); i += 1) {
        types[i] = freshen (types[i], freshMap);
    }
}

Type_Ptr
makeFuncType (int n)
{
    gcvector<AST_Ptr> params;
    for (int i = 0; i < n; i += 1)
        params.push_back(Type::makeVar ());
    AST_Ptr paramList = 
        AST::make_tree (TYPE_LIST, &params[0], &params[params.size()]);

    return consTree (FUNCTION_TYPE, Type::makeVar (), paramList)->asType ();
}

bool
makeFuncType (int n, Type_Ptr type, Unifier& subst)
{
    type = type->binding ();
    if (! type->isTypeVariable ())
        return (type->returnType () != NULL && type->numParams () == n);
    unify (type, makeFuncType (n));
    return true;
}

Type_Ptr
makeMethodType (int n, Decl* clas)
{
    gcvector<AST_Ptr> params;
    params.push_back (clas->asGenericType ());
    for (int i = 1; i < n; i += 1)
        params.push_back(Type::makeVar ());
    AST_Ptr paramList = 
        AST::make_tree (TYPE_LIST, &params[0], &params[params.size()]);

    return consTree (FUNCTION_TYPE, Type::makeVar (), paramList)->asType ();
}

/*****  TYPE VARIABLES *****/

class TypeVar_AST : public Type {
protected:
    
    NODE_CONSTRUCTORS_INIT (TypeVar_AST, Type, _me (NULL));

    bool isTypeVariable () {
        return true;
    }

    bool hasFreeVariables (ASTSet& visited) {
        Type_Ptr b = binding ();
        if (b == this)
            return true;
        else
            return b->hasFreeVariables (visited);
    }

    Type_Ptr binding () {
        Decl* me = getDecl ();
        if (me == NULL)
            return this;
        Type_Ptr b = me->getAst ()->asType ();
        if (b == NULL || b == this)
            return b;
        return b->binding ();
    }

    void setTypeBinding (Type_Ptr type) {
        Decl* me = getDecl ();
        assert (me != NULL);
        me->setAst (type);
    }

    void _print (ostream& out, int indent, ASTSet& visited) {
        Type_Ptr me = binding ();
        if (me == this || visited.count (me) > 0) {
            if (arity () == 1) {
                out << "(type_var " << lineNumber () << " " 
                    << child(0)->as_string ();
            } else
                out << "(type_var 0 $#" << uid;
            if (getDecl () != NULL)
                out << " " << getDecl ()->getIndex ();
            out << ")";
        } else
            print (me, out, indent, visited);
    }

    gcstring as_string () const {
        if (arity () == 1)
            return child (0)->as_string ();
        else {
            char numeral[14];
            sprintf(numeral, "$#%d", uid);
            return string(numeral);
        }
    }

    AST* post_make () {
        uid = next_uid;
        next_uid += 1;
        return this;
    }

    Decl* getDecl (int k = 0) {
        return _me;
    }

    void addDecl (Decl* decl) {
        assert (_me == NULL);
        _me = decl;
    }

private:

    Decl* _me;

    int uid;
    static int next_uid;
};

NODE_FACTORY (TypeVar_AST, TYPE_VAR);
int TypeVar_AST::next_uid = 0;


/***** FUNCTION TYPES *****/

class FunctionType_AST: public Type {

public:
    bool isFunctionType() {
        return true;
    }

protected:

    int numParams () {
        return child (1)->arity ();
    }

    Type_Ptr paramType (int k) {
        return child (1)->child (k)->asType ();
    }

    Type_Ptr returnType () {
        return child (0)->asType ();
    }

    NODE_CONSTRUCTORS (FunctionType_AST, Type);

};

NODE_FACTORY (FunctionType_AST, FUNCTION_TYPE);


/***** CLASSES *****/

class ClassType_AST: public Type {
protected:

    NODE_CONSTRUCTORS (ClassType_AST, Type);

    Decl* getDecl (int k = 0) {
        return child (0)->getDecl ();
    }

    void addDecl (Decl* decl) {
        child (0)->addDecl (decl);
    }

};

NODE_FACTORY (ClassType_AST, TYPE);

