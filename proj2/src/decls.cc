/* Implementations of declaration and type-related classes */

/* Authors:  YOUR NAMES HERE */
/* From a skeleton by Paul N. Hilfinger */

#include <stdexcept>
#include "apyc.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/** These must be filled in with declarations from the standard
 *  prelude.  They are used to supply the types of built-in
 *  constructs.  All are initially NULL. */
Decl* intDecl;
Decl* listDecl;
Decl* tuple0Decl;
Decl* tuple1Decl;
Decl* tuple2Decl;
Decl* tuple3Decl;
Decl* strDecl;
Decl* dictDecl;
Decl* boolDecl;
Decl* fileDecl;
// TODO: FileDecl missing
Decl* rangeDecl;

/** List of declarations corresponding to the module and actual
 *  declarations in the program (as opposed to type variables
 *  introduced by freshen). */
static gcvector<Decl*> allDecls;

/** Utility for printing types in Decls. */
static void
outType (Type_Ptr type, ostream& out) {
    out << " ";
    if (type != NULL) {
	type->binding ()->print (cout, 0);
    } else
	out << "?";
}

Decl::Decl (const gcstring& name, Decl* container, Environ* members)
    : _frozen (true), _name (name), _container (container),
      _members (members) {
    _index = allDecls.size ();
    allDecls.push_back (this);
    /* Allow name.c_str() to be used in the future without reallocation. */
    name.c_str ();
}
        
/* Print THIS on OUT. */
void 
Decl::print (ostream& out) const
{
    out << "(" << declTypeName () << " " << getIndex () << " " << getName() << " ";
    printContainer (out);
    printPosition (out);
    printType (out);
    printTypeParams (out);
    printMembersList (out);
    out << ")";
    out.flush ();
}

void
Decl::printContainer (ostream& out) const
{
    if (getContainer () != NULL) 
        out << getContainer ()->getIndex () << " ";
    else
        out << "-1 ";
}

void
Decl:: printPosition (ostream& out) const {
}

void
Decl::printType (ostream& out) const {
}

void
Decl::printMembersList (ostream& out) const {
    if (_members != NULL) {
        out << " (index_list";
        const gcvector<Decl*>& members = getEnviron ()->get_members ();
        for (size_t i = 0; i < members.size (); i += 1)
            out << " " << members[i]->getIndex ();
        out << ")";
    }
}

void
Decl::printTypeParams (ostream& out) const {
}

Type_Ptr 
Decl::getType () const
{
    return NULL;
}

void
Decl::setType (Type_Ptr type)
{
}

int
Decl::getPosition () const
{
    return -1;
}

AST_Ptr
Decl::getAst () const
{
    return _ast;
}

void
Decl::setAst (AST_Ptr ast)
{
    _ast = ast;
}

bool
Decl::isType () const
{
    return false;
}

bool
Decl::isInternal () const
{
    return false;
}

bool
Decl::isMethod () const
{
    return false;
}

Type_Ptr
Decl::asType (int, Type_Ptr, Type_Ptr) const
{
    UNIMPLEMENTED (asType);
}

Type_Ptr
Decl::asType (int arity, Type_Ptr*) const
{
    UNIMPLEMENTED (asType);
}

Type_Ptr
Decl::asGenericType ()
{
    UNIMPLEMENTED (asType);
}

int
Decl::getTypeArity () const
{
    return 0;
}

const Environ*
Decl::getEnviron () const
{
    if (_members == NULL)
        UNIMPLEMENTED (getEnviron);
    return _members;
}

/* Determine whether this decl can add a variable
 * of given id to its members
 */
bool
Decl::canAddVar (AST_Ptr id)
{
    Decl_Vector exists;
    const gcstring name = id->as_string();
    _members->find_immediate(name, exists);
    bool found = false;
    for (Decl_Vector::const_iterator i = exists.begin ();
         i != exists.end ();
         i++) {
        if ((*i)->getName() == name) {
            if ((*i)->declTypeName() == "classdecl" ||
                (*i)->declTypeName() == "funcdecl") {
                id->recordError();
                return false;
            }
            else if ((*i)->declTypeName() == "vardecl" ||
                     (*i)->declTypeName() == "paramdecl") {
                found = true;
            }
        }
    }
    return !found;
}

/* Determine whether this decl can add a function
 * of given id to its members
 */
bool
Decl::canAddFunc (AST_Ptr id)
{
    Decl_Vector exists;
    const gcstring name = id->as_string();
    _members->find_immediate(name, exists);
    for (Decl_Vector::const_iterator i = exists.begin ();
         i != exists.end ();
         i++) {
        if ((*i)->getName() == name) {
            if ((*i)->declTypeName() == "vardecl" ||
                (*i)->declTypeName() == "classdecl") {
                id->recordError();
                return false;
            }
        }
    }
    return true;
}

/* Determine whether this decl can add a classkjjkk
 * of given id to its members
 */
bool
Decl::canAddClass (AST_Ptr id)
{
    if (classes->find_immediate(id->as_string()) == NULL) {
        return true;
    }
    return false;
}

void
Decl::addMember (Decl* new_member)
{
    if (_members == NULL)
        UNIMPLEMENTED (addMember);
    _members->define (new_member);
}

Decl*
Decl::addVarDecl (AST_Ptr) {
    UNIMPLEMENTED (addVarDecl);
}

Decl*
Decl::addDefDecl (AST_Ptr) {
    UNIMPLEMENTED (addDefDecl);
}

Decl*
Decl::addClassDecl (AST_Ptr) {
    UNIMPLEMENTED (addDefDecl);
}

bool
Decl::assignable () const
{
    return false;
}

bool
Decl::isFrozen () const
{
    return _frozen;
}

void
Decl::setFrozen (bool freeze)
{
}

Decl::~Decl ()
{
}

const char*
Decl::declTypeName () const
{
    return "?";
}

/** The superclass of declarations that describe an entity with a type. */
class TypedDecl : public Decl {
protected:
    TypedDecl (const gcstring& name, Decl* container, AST_Ptr type,
           Environ* members = NULL)
        :  Decl (name, container, members),
           _type (type == NULL ? NULL : type->asType ()) {
    }

public:

    Type_Ptr getType () const {
        if (isFrozen () || _type == NULL)
            return _type;
        else
            return freshen (_type);
    }

    void setType (Type_Ptr type) {
        _type = type;
    }

protected:

    void printType (ostream& out) const {
	outType (_type, out);
    }

private:
    Type_Ptr _type;
};

class VarDecl : public TypedDecl {
public:

    VarDecl (const gcstring& name, Decl* container, AST_Ptr type)
        :  TypedDecl (name, container, type) {
    }

protected:

    const char* declTypeName () const {
        return "vardecl";
    }

    bool assignable () const {
        return true;
    }

};

Decl*
makeVarDecl (const gcstring& name, Decl* func, AST_Ptr type)
{
    return new VarDecl (name, func, type);
}


class ParamDecl : public TypedDecl {
public:

    ParamDecl (const gcstring& name, Decl* func, int k,
              AST_Ptr type)
        :  TypedDecl (name, func, type), _posn (k) {
    }

    int getPosition () const {
        return _posn;
    }

protected:

    const char* declTypeName () const {
        return "paramdecl";
    }

    void printPosition (ostream& out) const {
        out << " " << getPosition ();
    }

    bool assignable () const {
        return true;
    }

private:

    int _posn;

};

Decl*
makeParamDecl (const gcstring& name, Decl* func, int k, AST_Ptr type)
{
    return new ParamDecl (name, func, k, type);
}


class InstanceDecl : public TypedDecl {
public:

    InstanceDecl (const gcstring& name, Decl* cls, AST_Ptr type)
        :  TypedDecl (name, cls, type) {
    }

protected:

    const char* declTypeName () const {
        return "instancedecl";
    }

    bool assignable () const {
        return true;
    }

};

Decl*
makeInstanceDecl (const gcstring& name, Decl* cls, AST_Ptr type)
{
    return new InstanceDecl (name, cls, type);
}

class TypeVarDecl : public Decl {
public:
    AST_Ptr _canonical;
    TypeVarDecl (const gcstring& name, AST_Ptr canonical)
        :  Decl (name, NULL) {
        setAst (canonical);
        _canonical = canonical;
    }

protected:

    const char* declTypeName () const {
        return "typevardecl";
    }

    bool isInternal () const {
        return getAst () != NULL && getAst ()->arity () == 0;
    }

    void printContainer (ostream& out) const {
        _canonical->print(out, 0);
    };

    void printType (ostream& out) const {
	outType (getAst ()->asType (), out);
    }

};

Decl*
makeTypeVarDecl (const gcstring& name, AST_Ptr typeVar)
{
    return new TypeVarDecl (name, typeVar);
}

class FuncDecl : public TypedDecl {
public:

    FuncDecl (const gcstring& name, Decl* container, AST_Ptr type,
        Environ* env)
        :  TypedDecl (name, container, type, env) {
    }

protected:

    const char* declTypeName () const {
        return "funcdecl";
    }

    void setFrozen (bool freeze) {
        _frozen = freeze;
    }

    Decl* addVarDecl (AST_Ptr id) {
        if (canAddVar(id)) {
            Decl* decl = makeVarDecl (id->as_string (), this, Type::makeVar ());
            addMember (decl);
            return decl;
        }
        return NULL;
    }

    Decl* addDefDecl (AST_Ptr id) {
        if (canAddFunc(id)) {
            Decl* decl = makeFuncDecl (id->as_string (), this, Type::makeVar ());
            addMember (decl);
            return decl;
        }
        return NULL;
    }
};

Decl*
makeFuncDecl (const gcstring& name, Decl* container, AST_Ptr type)
{
    return new FuncDecl (name, container, type,
             new Environ (container->getEnviron ()));
}

class MethodDecl : public FuncDecl {
public:

    MethodDecl (const gcstring& name, Decl* container, AST_Ptr type)
        :  FuncDecl (name, container, type,
             new Environ (container->getEnviron ()->get_enclosure ())) {
    }

protected:

    bool isMethod () const {
        return true;
    }

private:

    mutable Type_Ptr _selectedType;

};

Decl*
makeMethodDecl (const gcstring& name, Decl* cls, AST_Ptr type)
{
    return new MethodDecl (name, cls, type);
}

class ClassDecl : public Decl {
public:

    ClassDecl (const gcstring& name, AST_Ptr params)
        : Decl (name, NULL, new Environ (outer_environ)), _params (params) {
    }

protected:

    const char* declTypeName () const {
        return "classdecl";
    }

    bool isType () const {
    return true;
    }

    void printContainer (ostream&) const {
    }

    void printTypeParams (ostream& out) const {
        out << " (index_list";
        for_each_child (c, _params) {
            Decl* decl = c->getDecl ();
            if (decl == NULL)
            out << " ?";
            else
            out << " " << decl->getIndex ();
        } end_for;
        out << ")";
    }

    Type_Ptr asType (int arity, Type_Ptr* params0) const {
        AST_Ptr* params = (AST_Ptr*) params0;
        if (getTypeArity () != -1 && getTypeArity () != arity) {
            throw range_error ("wrong number of type parameters");
        }
        for (int i = 0; i < arity; i += 1)
            if (params[i] == NULL)
                throw domain_error ("attempt to pass null type parameter");

        AST_Ptr id = make_id (getName ().c_str (), NULL);
        id->addDecl (const_cast<ClassDecl*> (this));

        AST_Ptr result = consTree (TYPE, id);
        result->append (params, params+arity);
        return result->asType ();
    }

    Type_Ptr asType (int arity, Type_Ptr t0, Type_Ptr t1) const {
        Type_Ptr params[] = { t0, t1 };
        return asType (arity, params);
    }

    Type_Ptr asGenericType () {
        gcvector<Type_Ptr> params;
        for (int i = 0; i < getTypeArity (); i += 1) {
            params.push_back (Type::makeVar ());
        }
        return asType (getTypeArity (), &params[0]);
    }

    Decl* addVarDecl (AST_Ptr id) {
        if (canAddVar(id)) {
            Decl* decl = makeInstanceDecl (id->as_string (), this, Type::makeVar ());
            addMember (decl);
            return decl;
        }
        return NULL;
    }

    Decl* addDefDecl (AST_Ptr id) {
        if (canAddFunc(id)) {
            Decl* decl = makeMethodDecl (id->as_string (), this, Type::makeVar ());
            addMember (decl);
            return decl;
        }
        return NULL;
    }

    int getTypeArity () const {
        return _params->arity ();
    }

    AST_Ptr _params;
};

Decl*
makeClassDecl (const gcstring& name, AST_Ptr params)
{
    Decl* decl = new ClassDecl (name, params);
    classes->define(decl);
    return decl;
}

class ModuleDecl : public Decl {
public:

    ModuleDecl (const gcstring& name)
        :  Decl (name, NULL, new Environ (NULL)) {
    }

protected:

    const char* declTypeName () const {
        return "moduledecl";
    }

    void printContainer (ostream& os) const {
    }

    Decl* addVarDecl (AST_Ptr id) {
        if (canAddVar(id)) {
            Decl* decl = makeVarDecl (id->as_string (), this, Type::makeVar ());
            addMember (decl);
            return decl;
        }
        return NULL;
    }

    Decl* addDefDecl (AST_Ptr id) {
        if (canAddFunc(id)) {
            Decl* decl = makeFuncDecl (id->as_string (), this, Type::makeVar ());
            addMember (decl);
            return decl;
        }
        return NULL;
    }

    Decl* addClassDecl (AST_Ptr clazz) {
        AST_Ptr id = clazz->child(0);
        if (canAddClass(id)) {
            AST_Ptr params = clazz->child(1);
            Decl* decl = makeClassDecl (id->as_string (), params);
            addMember(decl);
            return decl;
        }
        return NULL;
    }

};

Decl*
makeModuleDecl (const gcstring& name)
{
    fileDecl = new ModuleDecl (name);
    return fileDecl;
}

void
outputDecls (ostream& out)
{
    out << endl;
    for (size_t i = 0; i < allDecls.size (); i += 1) {
        if (!allDecls[i]->isInternal ()) {
            allDecls[i]->print (out);
            out << endl;
        }
    }
}
