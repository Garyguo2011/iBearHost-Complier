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
    // FILL THIS IN
    Unifier* subst = new Unifier();
    // for_each_child()
    
    resolveTypes(context, *subst);
        // for_each_child (c, this) {
        // } end_for;

    // switch (this->oper()->syntax()) {
    //     // case AND:
    //     // case TRUE:
    //     // case FALSE:
    //     case LIST_DISPLAY:
    //     case IF_EXPR:
    //     case TUPLE:
    //     {
    //         this->print(cerr, 4);
    //         cerr << "\n";
    //         getType()->print(cerr, 4);
    //         break;   
    //     }
    //     case WHILE:
    //     case IF:
    //     {
    //         this->print(cerr, 4);
    //         cerr << "\n";
    //         // getType()->print(cerr, 4);
    //         break;
    //     }
    //     default:
    //         break;

    // }
    
    // cerr << "\n";

    subst->setBindings();
    freezeDecls (false);
}


/*****   UNIFIER  *****/

bool
Unifier::isBound (Type_Ptr x) const
{
    return x->binding () != x;
}

Type_Ptr
Unifier::binding (Type_Ptr x) const
{
    return x->binding ();
}

void
Unifier::bind (Type_Ptr x, Type_Ptr y)
{
    assert (x != NULL && y != NULL);
    x = x->binding ();
    y = y->binding ();
    _bindings.push_back (x);
    x->bind (y);
    _numBound += 1;
}
    
void
Unifier::setBindings ()
{
    _bindings.clear ();
    _numBound = 0;
}

void
Unifier::transfer (Unifier& other)
{
    _bindings.insert (_bindings.end (), 
                      other._bindings.begin (), other._bindings.end ());
    other._bindings.clear ();
}


Unifier::~Unifier ()
{
    for (size_t k = 0; k < _bindings.size (); k += 1)
        _bindings[k]->unbind ();
}

/** As for unify, but SUBST has an undefined state if result is
 *  false. */
static bool
unify1 (Type_Ptr t0, Type_Ptr t1, Unifier& subst)
{
    t0 = t0->binding ();
    t1 = t1->binding ();
    if (t0 == t1)
        return true;
    if (t0->isTypeVariable ()) {
        subst.bind (t0, t1);
        return true;
    }
    subst.bind (t1, t0);
    if (t1->isTypeVariable ())
        return true;
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
    Unifier s;
    if (unify1 (t0, t1, subst)) {
        subst.transfer (s);
        return true;
    }
    return false;
}

bool
unifies (Type_Ptr t0, Type_Ptr t1)
{
    Unifier s;
    return unify (t0, t1, s);
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
    return child(0);
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
    return -1;
}

Type_Ptr
Type::typeParam (int k)
{
    throw range_error ("type has no type parameters");
}

Type_Ptr
Type::boundFunctionType ()
{
    return NULL;
}
    
const Environ*
Type::getEnviron ()
{
    return theEmptyEnviron;
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
    else if (type1->isTypeVariable ())
        result = Type::makeVar ();
    else {
        result = consTree (type1->oper ()->syntax ())->asType ();
        freshMap[type] = result;
        for_each_child (c, type1) {
            AST_Ptr c1;
            if (c->asType () != NULL)
                c1 = freshen (c->asType (), freshMap);
            else 
                c1 = c;
            result->append (c1);
        } end_for;
    }
    freshMap[type] = result;
    return result;
}

Type_Ptr
freshen (Type_Ptr type)
{
    if (type->hasFreeVariables (type)) {
        TypeMap freshMap;
        return freshen (type, freshMap);
    } else
        return type->binding ();
}

void
freshen (gcvector<Type_Ptr>& types)
{
    TypeMap freshMap;

    for (size_t i = 0; i < types.size (); i += 1) {
        if (Type::hasFreeVariables (types[i])) {
            for (size_t j = 0; j < types.size (); j += 1)
                types[j] = freshen (types[j], freshMap);
            break;
        }
    }
}

Type_Ptr
makeFuncType (int n)
{
    gcvector<AST_Ptr> params;
    for (int i = 0; i <= n; i += 1)
        params.push_back(Type::makeVar ());
    return AST::make_tree (FUNCTION_TYPE, &params[0], &params[params.size()])
        ->asType ();
}

bool
makeFuncType (int n, Type_Ptr type, Unifier& subst)
{
    type = type->binding ();
    if (! type->isTypeVariable ())
        return (type->returnType () != NULL && type->numParams () == n);
    unify (type, makeFuncType (n), subst);
    return true;
}

Type_Ptr
makeMethodType (int n, Decl* clas)
{
    gcvector<AST_Ptr> params;
    params.push_back (Type::makeVar ());
    params.push_back (clas->asGenericType ());
    for (int i = 1; i < n; i += 1)
        params.push_back(Type::makeVar ());
    return AST::make_tree (FUNCTION_TYPE, &params[0], &params[params.size()])
        ->asType();
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
        if (me == NULL || me->getAst () == NULL)
            return this;
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

    Decl* getDecl (int k = 0) {
        return child (0)->getDecl ();
    }

    void addDecl (Decl* decl) {
        child (0)->addDecl (decl);
    }

    AST_Ptr resolveSimpleIds (const Environ* env) {
        Decl_Vector decls;
        AST_Ptr id = getId();
        gcstring name = id->as_string();
        Decl* decl = classes->find(name);
        if (decl != NULL && id->numDecls() == 0){
            id->addDecl(decl);
        }
        return this;
    }

    void resolveSimpleTypeIds (const Environ* env)
    {
        AST_Ptr id = this->child(0);
        Decl* decl = classes->find(id->as_string());
        if (decl != NULL) {
            this->addDecl(decl);
        }
        for_each_child (c, this) {
            c->resolveSimpleTypeIds (env);
        } end_for;
    }
};

NODE_FACTORY (ClassType_AST, TYPE);

/** TypeList0 */
class TypeList0_AST : public Type {
protected:
    NODE_CONSTRUCTORS(TypeList0_AST, Type);
};

NODE_FACTORY(TypeList0_AST, TYPE_LIST);

