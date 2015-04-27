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
    string_pair("__in__", "membership test"),
    string_pair("__notin__", "membership test"),
};

static gcmap<gcstring, gcstring> 
OP_MAPPING(&OPNAMES[0], OPNAMES + sizeof(OPNAMES)/sizeof(string_pair));

static void
reportAmbiguities (gcvector<Resolver>& resolved)
{
    if (resolved.size () <= 1)
        return;
    int numOverloadings = resolved[0].numOverloadings ();
    for (int i = 0; i < numOverloadings; i += 1) {
        AST_Ptr id = resolved[0].overloading (i);
        Decl* decl0 = resolved[0][id];
        for (size_t j = 1; j < resolved.size (); j += 1) {
            if (decl0 != resolved[j][id]) {
                gcstring name = id->as_string ();
                if (OP_MAPPING.count (name) == 0) 
                    error (id, "ambiguous reference to %s", name.c_str ());
                else
                    error (id, "ambiguous %s",
                           OP_MAPPING[name].c_str ());
                break;
            }
        }
    }
}

void
AST::resolveTypesOuter (Decl* context) 
{
    freezeDecls (true);
    bool errorReporting0 = setErrorReporting (false);
    int errors0 = numErrors ();
    Resolver resolver;
    gcvector<Resolver> resolved;

    getOverloadings (resolver);

    while (resolver.nextResolution ()) {
        Unifier subst1;
        resolveTypes (context, subst1, resolver);
        if (numErrors () == errors0)
            resolved.push_back (resolver);
        setNumErrors (errors0);
    }

    setErrorReporting (errorReporting0);
    reportAmbiguities (resolved);
    if (resolved.size () != 0)
        resolver = resolved[0];
    Unifier subst;
    resolveTypes (context, subst, resolver);
    resolver.setOverloadings ();
    subst.setBindings ();
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
    if (unify1 (t0, t1, s)) {
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


/*****  RESOLVER  *****/

void
Resolver::addId (AST_Ptr id)
{
    if (_indexOf.count (id) == 0 && id->numDecls () > 1) {
        _indexOf[id] = _overloadings.size ();
        _overloadings.push_back (id);
        if (_selection.size () == 0) 
            _selection.push_back (-1);
        else
            _selection.push_back (0);
    }
}

int
Resolver::numOverloadings () const
{
    return _overloadings.size ();
}

bool
Resolver::nextResolution ()
{
    for (unsigned int k = 0; k < _selection.size (); k += 1) {
        if (_selection[k] + 1 < _overloadings[k]->numDecls ()) {
            _selection[k] += 1;
            return true;
        } else {
            _selection[k] = 0;
        }
    }
    return false;
}

Decl*
Resolver::operator[] (AST_Ptr id)
{
    if (_indexOf.count (id) == 0)
        return id->getDecl ();
    else
        return id->getDecl (_selection[_indexOf[id]]);
}

AST_Ptr
Resolver::overloading (int i)
{
    return _overloadings[i];
}

void
Resolver::setOverloadings ()
{
    for (size_t i = 0; i < _overloadings.size (); i += 1) {
        AST_Ptr id = _overloadings[i];
        Decl* d = id->getDecl (_selection[i]);
        while (id->numDecls () > 0)
            id->removeDecl (0);
        id->addDecl (d);
    }
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
    ASTSet visiting;
    return type->hasFreeVariables (visiting);
}

bool
Type::hasFreeVariables (ASTSet& visiting)
{
    if (visiting.count (this) == 0) {
        visiting.insert (this);
        for_each_child (c, this) {
            if (c->asType () != NULL && c->asType ()->hasFreeVariables (visiting))
                return true;
        } end_for;
    }
    return false;
}

Type_Ptr
freshen (Type_Ptr type)
{
    if (type->hasFreeVariables (type)) {
        TypeMap freshMap;
        return type->freshen (freshMap);
    } else
        return type;
}
void
freshen (gcvector<Type_Ptr>& types)
{
    TypeMap freshMap;

    for (size_t i = 0; i < types.size (); i += 1) {
        if (Type::hasFreeVariables (types[i])) {
            for (size_t j = 0; j < types.size (); j += 1)
                types[j] = types[j]->freshen (freshMap);
            break;
        }
    }
}

/* See also TypeVar_AST::freshen */
Type_Ptr
Type::freshen (TypeMap& freshMap)
{
    Type_Ptr result;
    if (freshMap.count (this) != 0)
        return freshMap[this];

    result = consTree (oper ()->syntax ())->asType ();
    freshMap[this] = result;
    for_each_child (c, this) {
        AST_Ptr c1;
        if (c->asType () == NULL)
            c1 = c;
        else
            c1 = c->asType ()->freshen (freshMap);
        result->append (c1);
    } end_for;
    return result;
}


Type_Ptr
makeFuncType (int n)
{
    gcvector<AST_Ptr> params;
    for (int i = 0; i <= n; i += 1)
        params.push_back(Type::makeVar ());
    return AST::make_tree (FUNCTION_TYPE, &params[0], &params[params.size()])
        ->asType();
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
makeFuncType (Type_Ptr returnType, int n, ...)
{
    Type_Ptr func = consTree (FUNCTION_TYPE)->asType ();
    va_list ap;
    va_start (ap, n);
    func->append (returnType);
    for (int i = 0; i < n; i += 1) {
        func->append (va_arg (ap, AST_Ptr));
    }
    va_end (ap);
    return func;
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

    bool hasFreeVariables (ASTSet& visiting) {
        Type_Ptr b = binding ();
        if (b->isTypeVariable ())
            return true;
        else
            return b->hasFreeVariables (visiting);
    }

    Type_Ptr binding () {
        Decl* me = getDecl ();
        assert (me != NULL && me->getAst () != NULL);
        Type_Ptr b = me->getAst ()->asType ();
        if (b->_binding == this)
            return b;
        return b->_binding->binding ();
    }

    void _print (ostream& out, int indent, ASTSet& visiting) {
        Type_Ptr me = binding ();
        if (me == this || visiting.count (me) > 0) {
            if (arity () == 1) {
                out << "(type_var " << lineNumber () << " " 
                    << child(0)->as_string ();
            } else
                out << "(type_var 0 $#" << uid;
            if (getDecl () != NULL)
                out << " " << getDecl ()->getIndex ();
            out << ")";
        } else
            print (me, out, indent, visiting);
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

    int numDecls () {
        return _me == NULL ? 0 : 1;
    }

    void addDecl (Decl* decl) {
        assert (_me == NULL);
        _me = decl;
    }

    void collectTypeVarDecls (Decl* enclosing) {
        if (_me == NULL) {
            addDecl (enclosing->addTypeVarDecl (this));
        }
    }

    AST_Ptr resolveSimpleIds (const Environ* env) {
        if (_me == NULL) {
            gcstring name = as_string ();
            _me = env->find_immediate (name);
            if (_me == NULL) {
                error (this, "the type variable %s is undefined",
                       name.c_str ());
                _me = makeTypeVarDecl (name, this);
            }
        }
        return this;
    }

    AST_Ptr replaceBindings (ASTSet& visiting) {
        Type_Ptr p;
        p = this;
        Decl* me = getDecl ();
        if (me == NULL) 
            return this;
        p = me->getAst ()->asType ();
        Type_Ptr b = p->binding ();
        if (b->isTypeVariable ())
            return b;
        else if (visiting.count (b) > 0) {
            p->unbind ();
            p->bind (b);
            return p;
        } else {
            return b->replaceBindings (visiting);
        }
    }

    void findUsedDecls (DeclSet& used) {
        Type::findUsedDecls (used);
        if (numDecls () > 0) {
            used.insert (getDecl ());
        }
    }    

    Type_Ptr freshen (TypeMap& freshMap) {
        if (freshMap.count (this) > 0) 
            return freshMap[this];
        Type_Ptr p = binding ();
        Type_Ptr result;
        if (p->isTypeVariable ()) {
            if (freshMap.count (p) > 0) {
                result = freshMap[p];
                freshMap[this] = result;
            } else {
                result = Type::makeVar ();
                freshMap[result] = freshMap[this] = freshMap[p] = result;
            }
        } else {
            result = Type::makeVar ();
            freshMap[this] = result;
            p = p->freshen(freshMap);
            result->bind (p);
        }
        return result;
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

    Decl* getDecl (int k = 0) {
        return getId ()->getDecl (k);
    }

    int numDecls () {
        return getId ()->numDecls ();
    }

    void addDecl (Decl* decl) {
        child (0)->addDecl (decl);
    }

    void collectTypeVarDecls (Decl* enclosing) {
        PASSDOWN (this, collectTypeVarDecls (enclosing), 1);
    }

    int numTypeParams () {
        return arity () - 1;
    }

    Type_Ptr typeParam (int k) {
        return child (k + 1)->asType ();
    }

    const Environ* getEnviron () {
        if (numDecls () == 1)
            return getDecl ()->getEnviron ();
        else
            return theEmptyEnviron;
    }

    void resolveSimpleTypeIds (const Environ* env) {
        Type::resolveSimpleTypeIds (env);
        if (getDecl () != NULL)
            return;
        gcstring name = getId ()->as_string ();
        Decl* decl = env->find (name);
        if (decl == NULL) {
            error (this, "undefined type: %s", name.c_str ());
            addDecl (makeUnknownDecl (name, true));
        } else if (!decl->isType ()) {
            error (this, "%s is not a type", name.c_str ());
            addDecl (makeUnknownDecl (name, true));
        } else {
            addDecl (decl);
        }
    }        

};

NODE_FACTORY (ClassType_AST, TYPE);



