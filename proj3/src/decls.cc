/* Implementations of declaration and type-related classes */

/* Authors:  YOUR NAMES HERE */
/* From a skeleton by Paul N. Hilfinger */

#include <stdexcept>
#include <map>
#include "apyc.h"
#include "dast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/** These must be filled in with declarations from the standard
 *  prelude.  They are used to supply the types of built-in
 *  constructs.  All are initially NULL. */
Decl* intDecl;
Decl* listDecl;
Decl* tupleDecl[4];
Decl* strDecl;
Decl* dictDecl;
Decl* boolDecl;
Decl* rangeDecl;

typedef gcmap<gcstring, Decl**> BuiltinMap;
static BuiltinMap builtinMap;

static struct { const char* name; Decl** var; } builtinInit[] = {
    { "int", &intDecl },
    { "list", &listDecl },
    { "tuple0", &tupleDecl[0] },
    { "tuple1", &tupleDecl[1] },
    { "tuple2", &tupleDecl[2] },
    { "tuple3", &tupleDecl[3] },
    { "str", &strDecl },
    { "dict", &dictDecl },
    { "bool", &boolDecl },
    { "range", &rangeDecl },
    { NULL, NULL }
};

static gcvector<Decl*> allDecls;

/** Utility for printing types in Decls. */
static void
outType (Type_Ptr type, ostream& out) {
    out << " ";
    if (type != NULL) {
	type->binding ()->print (out, 0);
    } else
	out << "?";
}

/** Utility program: print members list of DECL. */
static void
outMembers (const Decl* decl, ostream& out) {
    out << " (index_list";
    for (int i = 0; i < decl->numMembers (); i += 1)
        out << " " << decl->getMember (i)->getIndex ();
    out << ")";
}

Decl::Decl (int index, const gcstring& name, Decl* container)
    : _index (index), _name (name), _container (container) {
    name.c_str ();
}
        
int
Decl::numMembers () const
{
    return _members.size ();
}

Decl*
Decl::getMember (int k) const
{
    return _members[k];
}

/* Print THIS on OUT. */ 
void 
Decl::print (ostream& out) const
{
    out << "(" << declTypeName () << " " << getIndex () 
	<< " " << getName () << " ";
    printContainer (out);
    printPosition (out);
    printType (out);
    printTypeParams (out);
    printMembersList (out);
    out << ")";
    out.flush ();
}

void
Decl::print () const
{
    print (cout);
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
}

void
Decl::printTypeParams (ostream& out) const {
}

Type_Ptr 
Decl::getType () const
{
    return NULL;
}

Type_Ptr
Decl::getSelectedType () const {
    return getType ();
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
Decl::isOverloadable () const
{
    return false;
}

bool
Decl::isMethod () const
{
    return false;
}

Type_Ptr
Decl::asType ()
{
    AST_Ptr id = AST::make_token (ID, getName ());
    id->setDecl (this);
    return consTree (TYPE, id)->asType ();
}

int
Decl::getTypeArity () const
{
    return 0;
}

void
Decl::addTypeFormal (Decl* decl)
{
}

void
Decl::addMember (Decl* new_member)
{
    _members.push_back (new_member);
}

bool
Decl::assignable () const
{
    return false;
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
    TypedDecl (int index, const gcstring& name, Decl* container)
        :  Decl (index, name, container), _type (NULL) {
    }

public:

    Type_Ptr getType () const {
        return _type;
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

    VarDecl (int index, const gcstring& name, Decl* container)
        :  TypedDecl (index, name, container) {
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
makeVarDecl (int index, const gcstring& name, Decl* func)
{
    return new VarDecl (index, name, func);
}


class ParamDecl : public TypedDecl {
public:

    ParamDecl (int index, const gcstring& name, Decl* func, int k)
        :  TypedDecl (index, name, func), _posn (k) {
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
makeParamDecl (int index, const gcstring& name, Decl* func, int k)
{
    return new ParamDecl (index, name, func, k);
}


class InstanceDecl : public TypedDecl {
public:

    InstanceDecl (int index, const gcstring& name, Decl* cls)
        :  TypedDecl (index, name, cls) {
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
makeInstanceDecl (int index, const gcstring& name, Decl* cls)
{
    return new InstanceDecl (index, name, cls);
}

class TypeVarDecl : public Decl {
public:

    TypeVarDecl (int index, const gcstring& name)
        :  Decl (index, name, NULL) {
    }

protected:

    bool isInternal () const {
	return getAst () != NULL && getAst ()->arity () == 0;
    }

    void printContainer (ostream&) const {
    }

    const char* declTypeName () const {
        return "typevardecl";
    }

    void printType (ostream& out) const {
	outType (getAst ()->asType (), out);
    }

};

Decl*
makeTypeVarDecl (int index, const gcstring& name)
{
    return new TypeVarDecl (index, name);
}

class FuncDecl : public TypedDecl {
public:

    FuncDecl (int index, const gcstring& name, Decl* container)
        :  TypedDecl (index, name, container) {
    }

protected:

    bool isOverloadable () const {
        return true;
    }

    const char* declTypeName () const {
        return "funcdecl";
    }

    void printMembersList (ostream& out) const {
        outMembers (this, out);
    }
};

class MethodDecl : public FuncDecl {
public:

    MethodDecl (int index, const gcstring& name, Decl* container)
        :  FuncDecl (index, name, container) {
    }

protected:

    Type_Ptr getSelectedType () const {
        return getType ()->binding ()->boundFunctionType ();
    }

    bool isMethod () const {
	return true;
    }

};

Decl*
makeFuncDecl (int index, const gcstring& name, Decl* container)
{
    if (container->isType ())
	return new MethodDecl (index, name, container);
    else
	return new FuncDecl (index, name, container);
}

class ClassDecl : public Decl {
public:

    ClassDecl (int index, const gcstring& name)
        : Decl (index, name, NULL) {
    }

protected:

    bool isType () const {
	return true;
    }

    void printContainer (ostream&) const {
    }

    void printTypeParams (ostream& out) const {
        out << " (index_list";
        for (size_t k = 0; k < _params.size (); k += 1)
            out << " " << _params[k]->getIndex ();
	out << ")";
    }

    void addTypeFormal (Decl* decl) {
        _params.push_back (decl);
    }

    const char* declTypeName () const {
        return "classdecl";
    }

    int getTypeArity () const {
	return _params.size ();
    }

    void printMembersList (ostream& out) const {
        outMembers (this, out);
    }
private:
    gcvector<Decl*> _params;
};

Decl*
makeClassDecl (int index, const gcstring& name)
{
    return new ClassDecl (index, name);
}

class ModuleDecl : public Decl {
public:

    ModuleDecl (int index, const gcstring& name)
        :  Decl (index, name, NULL) {
    }

protected:

    const char* declTypeName () const {
        return "moduledecl";
    }

    void printContainer (ostream& os) const {
    }

    void printMembersList (ostream& out) const {
        outMembers (this, out);
    }
};

Decl*
makeModuleDecl (int index, const gcstring& name)
{
    return new ModuleDecl (index, name);
}

/** NoneDecl is used exclusively in this phase.  Its type name is not
 *  valid in the external form of a tree. There is only one NoneDecl. */
class NoneDecl : public Decl {
public:

    /** The index is irrelevant */
    NoneDecl ()
        : Decl (-1, "*None*", NULL) {
    }

protected:

    bool isType () const {
	return true;
    }

    void printContainer (ostream&) const {
    }

    const char* declTypeName () const {
        return "nonedecl";
    }

    int getTypeArity () const {
        return 0;
    }

};

static NoneDecl noneObj;
Decl* noneDecl = &noneObj;

Decl*
getDecl (size_t k)
{
    if (k >= allDecls.size ())
        return NULL;
    else
        return allDecls[k];
}

void
addDecl (Decl* decl)
{
    size_t k = decl->getIndex ();
    if (k >= allDecls.size ())
        allDecls.insert (allDecls.end (), k - allDecls.size () + 1, NULL);
    allDecls[k] = decl;
    setBuiltinDecl (decl);
}

void
setBuiltinDecl (Decl* decl)
{
    if (builtinMap.size () == 0) {
        for (int i = 0; builtinInit[i].name != NULL; i += 1) {
            builtinMap[builtinInit[i].name] = builtinInit[i].var;
        }
    }

    BuiltinMap::const_iterator entryPair = builtinMap.find (decl->getName ());
    if (entryPair != builtinMap.end ()) {
        if (*entryPair->second != NULL) {
            throw logic_error (string("multiple definition of builtin class ") 
                               + decl->getName ().c_str());
        }
        *entryPair->second = decl;
    }
}

