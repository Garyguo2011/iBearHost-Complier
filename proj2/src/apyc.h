/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Interfaces for apyc. */

#ifndef _APYC_H_
#define _APYC_H_

#include <cstdio>
#include <string>
#include <stdexcept>
#include "ast.h"

class Decl;
class Environ;
typedef std::unordered_set<Decl*> DeclSet;

/** A dummy class whose sole purpose is to provide a constructor that
 *  initializes the garbage collector (required for Darwin).  Put a
 *  definition of a dummy GCINIT at the beginning of each source
 *  file. */
class GCINIT {
public:
    GCINIT() {
        if (!initialized) 
            GC_init();
        initialized = true;
    }
private:
    static bool initialized;
};

#define UNIMPLEMENTED(name) \
    throw logic_error ("unimplemented method: " #name)

/** Print an error message indicating a fatal error, with MESSAGE as
 *  the detail, and exit with code 2 immediately. */
extern void fatal (const gcstring& message) __attribute__ ((noreturn));

/** Print an error message in standard Unix format:
 *      <filename>:<linenum>: <message>
 *  where <filename> and <linenum> denote the file and line number
 *  containing source location LOC, and <message> is composed from
 *  FORMAT and the trailing arguments as
 *  for the printf family. */
extern void error (const char* loc, const char* format, ...);

/** Print an error message as for error(loc, format, ...), using
 *  NODE->loc() as the location.  Reports only one error per node. */
extern void error (AST_Ptr node, const char* format, ...);

/** Print an error message (without file or line number indications)
 *  composed from FORMAT and the trailing arguments as for the printf
 *  family. */
extern void errorNoFile (const char* format, ...);

/** Set printing of error reports to true iff ON is true.  When off, 
 *  numErrors() increments, but nothing is printed.  Use this to tell
 *  if a certain choice of overloaded declarations works without
 *  giving the usual message when it doesn't.  Returns previous
 *  setting. */
extern bool setErrorReporting (bool on);

/** The cumulative error count. */
extern int numErrors ();

/** Reset the cumulative error count to NUM. By saving numErrors before
 *  processing a subtree, turning off printing of error messages, and 
 *  then resetting it numErrors to its initial value, you can tell if a
 *  certain set of overloading choices (for example) worked without
 *  complaining if it doesn't.  Returns the previous value of
 *  numErrors(). */
extern int setNumErrors (int num);

/** Returns an AST read from the file named AST_FILE_NAME, recording
 *  PYTHON_FILE_NAME as the source file in line-number information. */
extern AST_Ptr readAst (const gcstring& ast_file_name, 
                        const gcstring& python_file_name);

/** Perform certain initial transformations of the tree that could
 *  have been done during parsing.  See full comment in post1.cc. */
extern AST_Ptr post1 (AST_Ptr prog, AST_Ptr prelude);

/* Decls */

/** A declaration node, containing semantic information about a 
 *  program entity.  Subtypes of Decl refer to local variables,
 *  parameters, global variables, defined functions, methods, constants,
 *  modules, and classes. */
class Decl : public gc {
public:

    Decl (const gcstring& name, Decl* container, Environ* members = NULL);
        
    /** My index value (if I appear explicitly), and otherwise -1 to
     *  indicate that I am unindexed. */
    int getIndex () const { return _index; }

    const gcstring& getName () const { return _name; }

    /** Print THIS on OUT. */
    virtual void print(std::ostream& out, const DeclSet& used) const;

    /** Print THIS on the standard output. */
    virtual void print (const DeclSet& used) const;

    /** Get my container (null if none). */
    virtual Decl* getContainer () const { return _container; }

    /** Get the type of the entity I represent. */
    virtual Type_Ptr getType () const;

    /** Get my type if selected from an object, as in x.f, where x is
     *  not a class. */
    virtual Type_Ptr getSelectedType () const;

    /** Set my type to TYPE in SUBST. */
    virtual void setType (Type_Ptr type, Unifier& subst);

    /** My associated AST, if any.  A Decl may be associated with a
     *  particular AST that corresponds to the declaration of the
     *  entity it declares.  */
    virtual AST_Ptr getAst () const;

    /** Set getAst() to AST. */
    virtual void setAst (AST_Ptr ast);

    /** True iff I am an overloadable kind of entity (defined by def). */
    virtual bool isOverloadable () const;

    /** True iff I represent a method. */
    virtual bool isMethod () const;

    /** True iff I represent a type. */
    virtual bool isType () const;

    /** True iff I represent an internally generated type variable
     *  (which should not be included in the output list). */
    virtual bool isInternal () const;

    /** A Type representing me with ARITY (0 <= ARITY <=2) type parameters
     *  taken from T0 and T1.  Requires isType(). */
    virtual Type_Ptr asType (int arity = 0,
                             Type_Ptr t0 = NULL, Type_Ptr t1 = NULL) const;

    /** A Type representing me with parameters PARAMS[0 .. ARITY-1]. */
    virtual Type_Ptr asType (int arity, Type_Ptr* params) const;

    /** A Type representing me with the type parameters supplied at my
     *  definition. */
    virtual Type_Ptr asBaseType () const;

    /** A Type representing me with generic type parameters. */
    virtual Type_Ptr asGenericType ();

    /** If I am type, returns the number of type arguments. */
    virtual int getTypeArity () const;

    /** Get my position (in a parameter list, indexed from 0). */
    virtual int getPosition () const;

    /** A view of all member Decls I contain (modules, classes). */
    virtual const Environ* getEnviron () const;

    /** Add DECL to the end of my list of member Decls. */
    virtual void addMember (Decl* new_member);

    /** Return a declaration of ID appropriate for a variable declaration to
     *  my members. */
    virtual Decl* newVarDecl (AST_Ptr id);

    /** Create and add a declaration of ID appropriate for a variable
     *  declaration to my members.  There must not already be one. Returns the
     *  resulting declaration */
    virtual Decl* addVarDecl (AST_Ptr id);

    /** Return a declaration of ID appropriate for a 'def' with K
     *  parameters to my members. */
    virtual Decl* newDefDecl (AST_Ptr id, int k);

    /** Create and add a declaration of ID appropriate for a 'def'
     *  with K parameters to my members.  Returns the resulting declaration. */
    virtual Decl* addDefDecl (AST_Ptr id, int k);

    /** Add a new parameter declaration for ID, returning the declaration.
     *  K is the index of this parameter in its formal parameter list.
     *  If the parameter declaration already exists, indicate an error
     *  and return the previous declaration. */
    virtual Decl* addParamDecl (AST_Ptr id, int k);

    /** Add a type variable declaration for ID, if it does not already
     *  exist.  Return either the previously existing declaration or
     *  the new one, as appropriate. */
    virtual Decl* addTypeVarDecl (AST_Ptr id);

    /** True iff the entity I represent can be assigned to or defined
     *  by assignment. */
    virtual bool assignable () const;

    /** True iff my type is currently "frozen", meaning that getType is
     *  not to freshen type variables in it.  Everything in a class is
     *  frozen until processing of the class definition is finished.
     *  Likewise for outer-level functions. */
    virtual bool isFrozen () const;

    /** If my freezing status is mutable, set it to FROZEN.
     *  Otherwise, does nothing. */
    virtual void setFrozen (bool frozen);

    /** Replace all type-variable bindings reachable from me with
     *  their referents, except for those needed to break cycles. 
     *  Returns the modified tree. */
    virtual void replaceBindings ();

    virtual ~Decl ();

protected:

    /** The name of this type of Decl for external printing purposes. */
    virtual const char* declTypeName () const;

    /** Print my container's index on OUT, if
     *  applicable, and otherwise do nothing. */
    virtual void printContainer (std::ostream& out) const;

    /** Print my position in my container, if applicable, on OUT,
     *  and otherwise do nothing. */
    virtual void printPosition (std::ostream& out) const;

    /** Print my type on OUT, if applicable, and  otherwise do nothing. */
    virtual void printType (std::ostream& out) const;

    /** Print my list of type parameters on OUT,
     *  if applicable, and otherwise do nothing. */
    virtual void printTypeParams (std::ostream& out) const;

    /** Print my index list of members or local definitions on OUT,
     *  if applicable, and otherwise do nothing. */
    virtual void printMembersList (std::ostream& out, const DeclSet& used) const;

protected:
    bool _frozen;

private:
    int _index;
    const gcstring _name;
    Decl* _container;
    Environ* _members;
    AST_Ptr _ast;
};

/** Declaration of local or module-level variable NAME, defined
 *  immediately inside function or module CONTAINER and having type
 *  TYPE. */
extern Decl* makeVarDecl (const gcstring& name,
                          Decl* container, AST_Ptr type);
/** Declaration of parameter #K (numbered from 0) named NAME in function FUNC
 *  and of type TYPE. */
extern Decl* makeParamDecl (const gcstring& name,
                            Decl* func, int k, AST_Ptr type);
/** Declaration of an instance variable named NAME of type TYPE 
 *  in class CLAZZ. */
extern Decl* makeInstanceDecl (const gcstring& name, Decl* clazz,
                               AST_Ptr type);
/** Declaration of type variable NAME, associated with type variable
 *  CANONICAL. */
extern Decl* makeTypeVarDecl (const gcstring& name, AST_Ptr canonical);
/** Declaration of function NAME of type TYPE, nested inside the
 *  function or module CONTAINER. */
extern Decl* makeFuncDecl (const gcstring& name,
                           Decl* container, AST_Ptr type);
/** Declaration for a class NAME with ARITY type parameters. */
extern Decl* makeClassDecl (const gcstring& name, AST_Ptr params);
/** Declaraton for the module MAIN.  This always has sequence number 0. */
extern Decl* makeModuleDecl (const gcstring& name);

/** Declaration for an unknown entity: intended to provide a non-null
 *  dummy declaration to use for erroneous references. If ISTYPE, the
 *  Decl is marked as a type. */
extern Decl* makeUnknownDecl (const gcstring& name, bool isType);

/** If DECL represents a declaration of a builtin class, set the
 *  appropriate global variable to point to it. */
extern void setBuiltinDecl (Decl* decl);

/** Replace the getAst () values of all types in Decls. */
extern void replaceDeclBindings ();

/** Output all Decl nodes in USED to standard output. */
extern void outputDecls (std::ostream& out, const DeclSet& usedTypeVars);

/** Decls for built-in types. */
extern Decl* intDecl;
extern Decl* listDecl;
extern Decl* tupleDecl[];
extern Decl* strDecl;
extern Decl* dictDecl;
extern Decl* boolDecl;
extern Decl* fileDecl;
extern Decl* rangeDecl;

typedef gcvector<Decl*> Decl_Vector;

/** Usage:
 *   for_each_decl (x, decls) {
 *        stmts involving x (a Decl*).
 *   } end_for;   */
#define for_each_decl(I, DECLS)                                              \
    do {                                                                     \
        const Decl_Vector& _v_ = DECLS;                                      \
        for (Decl_Vector::const_iterator _i_ = _v_.begin ();                 \
             _i_ != _v_.end (); _i_++) {                                     \
             Decl* I = *_i_;
        

class Environ : public gc {
public:

    /** An initialiy empty environment enclosed in ENCLOSING. */
    Environ (const Environ* enclosing);

    /** An environment initialized to the (immediate) contents of 
     *  ENVIRON0, enclosed in enclosing. */
    Environ (const Environ* environ0, const Environ* enclosing);

    /** An entry for NAME, or NULL if none.  Does not search enclosing
     *  Environs. */
    Decl* find_immediate (const gcstring& name) const;

    /** Set DEFNS to a list of all my entries for NAME.  Does not search
     *  enclosing Environs. */
    void find_immediate (const gcstring& name, Decl_Vector& defns) const;

    /** An entry for NAME in me or enclosing Environs, or NULL if
     *  none. */
    Decl* find (const gcstring& name) const;

    /** Set DEFNS to all definitions of NAME in the innermost Environ
     *  in me or my enclosing Environs that has any.  DEFNS is set
     *  empty if it is nowhere defined. */
    void find(const gcstring& name, Decl_Vector& defns) const;

    /** Define DECL in me by its name.  */
    void define (Decl* decl);

    /** The environment enclosing me (passed to my constructor), if
     *  any. */
    const Environ* get_enclosure () const;

    /** A view of my members (not including enclosing Environs). */
    const Decl_Vector& get_members () const;

private:

    Decl_Vector members;
    const Environ* enclosure;
};

/** The current outer (__main__) environment */
extern const Environ* outerEnviron;

/** The declaration of the main module. */
extern Decl* mainModule;

/** A constant empty environment. */
extern const Environ* theEmptyEnviron;

#endif

