/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Interfaces for apyc. */

#ifndef _APYC_H_
#define _APYC_H_

#include <cstdio>
#include <string>
#include <stdexcept>
#include "dast.h"

class Decl;

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

/** The cumulative error count. */
extern int numErrors ();

/** Returns a decorated AST read from the file named DAST_FILE_NAME, recording
 *  PYTHON_FILE_NAME as the source file in line-number information. */
extern AST_Ptr readDast (const gcstring& dast_file_name, 
                         const gcstring& python_file_name);

/** A debugging routine that prints all the Decls collected by the
 *  last run of readDest on OUT. */
extern void printDecls (std::ostream& out);

/* Decls */

// You will probably want to use Decls to contain 

/** A declaration node, containing semantic information about a 
 *  program entity.  Subtypes of Decl refer to local variables,
 *  parameters, global variables, defined functions, methods, constants,
 *  modules, and classes. */
class Decl : public gc {
public:

    Decl (int index, const gcstring& name, Decl* container);
        
    /** My index value (if I appear explicitly), and otherwise -1 to
     *  indicate that I am unindexed. */
    int getIndex () const { return _index; }

    const gcstring& getName () const { return _name; }

    /** Print THIS on OUT. */
    virtual void print(std::ostream& out) const;

    /** Print THIS on the standard output. */
    virtual void print () const;

    /** Get my container (null if none). */
    virtual Decl* getContainer () const { return _container; }

    /** Get the type of the entity I represent. */
    virtual Type_Ptr getType () const;

    /** Get my type if selected from an object, as in x.f, where x is
     *  not a class. */
    virtual Type_Ptr getSelectedType () const;

    /** Set my type to TYPE in SUBST. */
    virtual void setType (Type_Ptr type);

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

    /** If I am a type, returns a Type that represents me with no parameters. */
    virtual Type_Ptr asType ();

    /** If I am type, returns the number of type arguments. */
    virtual int getTypeArity () const;

    /** Get my position (in a parameter list, indexed from 0). */
    virtual int getPosition () const;

    /** Add DECL to the end of my list of formal types. */
    virtual void addTypeFormal (Decl* decl);

    /** Add DECL to the end of my list of member Decls. */
    virtual void addMember (Decl* new_member);

    /** The number of members I have. */
    virtual int numMembers () const;

    /** Get the Kth member (numbering from 0) added to me, 
     *  0 <= K < numMembers(). */
    virtual Decl* getMember (int k) const;

    /** True iff the entity I represent can be assigned to or defined
     *  by assignment. */
    virtual bool assignable () const;

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
    virtual void printMembersList (std::ostream& out) const;

private:
    int _index;
    const gcstring _name;
    Decl* _container;
    gcvector<Decl*> _members;
    AST_Ptr _ast;
};

/** Declaration of local or module-level variable NAME with index
 *  number INDEX, defined immediately inside function or module
 *  CONTAINER. */
extern Decl* makeVarDecl (int index, const gcstring& name, Decl* container);

/** Declaration with index INDEX of parameter #K (numbered from 0)
 *  named NAME in function FUNC. */
extern Decl* makeParamDecl (int index, const gcstring& name,
                            Decl* func, int k);

/** Declaration with index INDEX of an instance variable named NAME 
 *  in class CLAZZ. */
extern Decl* makeInstanceDecl (int index, const gcstring& name, Decl* clazz);

/** Declaration with index INDEX of type variable NAME. */
extern Decl* makeTypeVarDecl (int index, const gcstring& name);

/** Declaration with index INDEX of function NAME, nested inside the
 *  function or module CONTAINER. */

extern Decl* makeFuncDecl (int index, const gcstring& name, Decl* container);

/** Declaration with index INDEX of a class NAME. */
extern Decl* makeClassDecl (int index, const gcstring& name);

/** Declaraton for the module main.  This always has index number 0. */
extern Decl* makeModuleDecl (int index, const gcstring& name);

/** Declaration for the type of None (runtime entity only). */
extern Decl* makeNoneDecl (int index);

/** If DECL represents a declaration of a builtin class, set the
 *  appropriate global variable to point to it. */
extern void setBuiltinDecl (Decl* decl);

/** Decls for built-in types. */
extern Decl* intDecl;
extern Decl* listDecl;
extern Decl* tupleDecl[];
extern Decl* strDecl;
extern Decl* dictDecl;
extern Decl* boolDecl;
extern Decl* rangeDecl;
/** A special type used only in the runtime phase. */
extern Decl* noneDecl;

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
        

/** The declaration of the main module. */
extern Decl* mainModule;

#endif

