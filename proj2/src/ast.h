/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* ast.h: Top-level definitions for abstract syntax trees. */

/* Authors: */

#ifndef _AST_H_
#define _AST_H_

#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include "horn-common.h"

class AST;
class AST_Token;
class AST_Tree;
class Type;
class Decl;
class Environ;
class Unifier;

typedef AST* AST_Ptr;
typedef Type* Type_Ptr;
YYDEFINE_LIST_TYPE(List_Ptr, AST_Ptr);

/** A set of AST object pointers. */
typedef std::unordered_set<AST_Ptr> ASTSet;
/** A mapping from type object pointers to type object pointers. */
typedef std::unordered_map<Type_Ptr, Type_Ptr> TypeMap;


/* General Design Note:  We have only a few base types defined in .h
 * files.  Concrete types are typically defined in .cc files because
 * in general, their type names are not expected to be used directly
 * elsewhere in the program.  Instead, we rely on having these
 * concrete classes override virtual methods as appropriate, and use
 * factory methods to find and instantiate instances of these classes
 * where needed.  Thus AST and Type declare a common behavior for all
 * their subtypes, and it is that common behavior that the rest of the
 * program relies on exclusively, minimizing inquiries into the
 * specific types of child nodes.  */


/** The base type of all nodes in the abstract syntax tree. */
class AST : public CommonNode<AST, AST_Token, AST_Tree> {
public:
    typedef gcmap<std::string, AST_Ptr> AST_Map;

    /** The line number of the source location associated with me. */
    virtual const char* lineNumber ();

    /** Insert NODE->child(FIRST), ..., NODE->child(FIRST+NUM-1) before
     *  my child K. */
    virtual void copyChildren (int k, AST_Ptr node, int first, int num);

    /** A new node that is identical to me (same children and
     *  location), but with the operator associated with SYNTAX. This
     *  is a shallow copy; the children are shared, not cloned. */
    virtual AST_Ptr retypedNode (int syntax);

    /** Print my representation as an AST on OUT.  Use INDENT as the
     *  indentation for subsequent lines if my representation takes up
     *  multiple lines. */
    void print (std::ostream& out, int indent);

    /** For nodes derived from Type, return the node with static type Type.
     *  Returns NULL on other node types. */
    virtual Type_Ptr asType ();

    /** True if I am a Type or an id that denotes a type. */
    virtual bool isType ();

    /** For nodes representing formal parameters, ids, or attribute
     *  references, the id part.  For types, the class id.  */
    virtual AST_Ptr getId ();

    /** For nodes that represent named entities, the number of
     *  possible declarations of that entity.  (For overloaded names,
     *  therefore, may be >1). */
    virtual int numDecls ();

    /** The Kth declaration (0 <= K < numDecls()) of me.  Returns NULL
     *  if there is none. */
    virtual Decl* getDecl (int k = 0);

    /** Add DECL to the end of the list of declarations of this node,
     *  if allowed. */
    virtual void addDecl (Decl* decl);

    /** Remove Kth declaration (0 <= K < numDecls()) of me. */
    virtual void removeDecl (int k);

    /** Get my type, if I have one. */
    virtual Type_Ptr getType ();
    
    /** Set my type to TYPE, or unify with TYPE if already
     *  set. Returns true iff successful. */
    virtual bool setType (Type_Ptr type, Unifier& subst);

    /** Do outer-level semantic analysis on me---all scope and type
     *  analysis that applies to definitions and statements that are
     *  not nested inside classes or function definitions.  Modifies 
     *  the global environment with any definitions I represent.
     *  Returns the modified tree.  */
    virtual AST_Ptr doOuterSemantics ();

    /** Add any declarations that I represent to ENCLOSING, the
     *  environment in which I am nested.  This does not add
     *  declarations for declarative regions nested within me. */
    virtual void collectDecls (Decl* enclosing);

    /** Add declarations that result from occurrences of type
     *  variables in type attributions to ENCLOSING. */
    virtual void collectTypeVarDecls (Decl* enclosing);

    /** Assuming I am a target of an assignment, add any local
     *  declarations that would result from assignments to me to
     *  ENCLOSING, my enclosing construct.  (Used by overridings of
     *  collectDecls.) */
    virtual void addTargetDecls (Decl* enclosing);

    /** Resolve all simple (non-qualified) identifiers in me, assuming
     *  that ENV defines declarations visible at my outer level.
     *  Returns the resolved node.  This will differ from THIS when it
     *  denotes a type.  */
    virtual AST_Ptr resolveSimpleIds (const Environ* env);
    
    /** Resolve all simple (non-qualified) type identifiers in a typed
     *  identifier.  Does nothing for other nodes. Assumes that
     *  that ENV defines declarations visible at my outer level. */
    virtual void resolveSimpleTypeIds (const Environ* env);
    
    /** Replace any allocators in me with appropriate NEW nodes,
     *  returning the modified node. */
    virtual AST_Ptr resolveAllocators (const Environ* env);

    /** Resolve all selections of the form CLASS.ID by replacing them
     *  with ID, appropriately decorated, assuming that ENV defines
     *  all visible classes.   Returns the modified tree. */
    virtual AST_Ptr resolveStaticSelections (const Environ* env);

    /** Set the "freeze" state of everything defined by "def" in me to
     *  FROZEN. */
    virtual void freezeDecls (bool frozen);

    /** Resolve the types of me and my subcomponents, and resolve
     *  the meanings of unresolved attribute references (OBJ.ID, where
     *  OBJ is not a class, so that the possible meanings of ID depends 
     *  on the type of OBJ).  During resolution, all def's in me are
     *  frozen---i.e., references to them do not create fresh type
     *  variables. */
    virtual void resolveTypesOuter(Decl* context);

    /** Attempt to determine the types of me and my subcomponents.
     *  Each expression's type is initially an unbound type variable,
     *  which this routine then binds to a type in SUBST.  The
     *  operations does not chahge this tree, but records everything
     *  in SUBST.  To permanently set types, simply use the
     *  setBindings() method of SUBST.  If typing fails, throws a
     *  semantic_error exception. CONTEXT provides the module, class,
     *  or function containing me. */
    virtual void resolveTypes (Decl* context, Unifier& subst);

    /** True if an error has been reported on me. */
    bool errorReported ();

    /** Indicate that an error has been reported on this node (to
     *  avoid multiple error messages. */
    void recordError ();

protected:

    AST ();

    /** Print me as an AST on OUT.  Use INDENT as the indentation for 
     *  subsequent lines if my representation takes up multiple lines.
     *  This method is intended to be called by other print methods
     *  during a traversal (using the print method below), whereas
     *  the public print method begins a traversal.  Assumes that
     *  VISITED indicates ancestor nodes that have already been
     *  printed, restoring it to its previous value when done. */
    virtual void _print (std::ostream& out, int indent, ASTSet& visited) = 0;

    /** Print TREE on OUT at given INDENT level, recording nodes
     *  visited in VISITED (to avoid infinite traversals of
     *  circular type structures.  This is the intended way that
     *  overridings of _print should recursively print their children.
     */
    static void print (AST_Ptr tree, std::ostream& out, int indent,
                       ASTSet& visited);

    /** Set to true to indicate that an error has been reported on this
     *  node.  Used to avoid multiple error messages on a node. */
    bool _erroneous;

};

class AST_Token : public CommonToken<AST, AST_Token, AST_Tree> {
public:
    AST_Token (int syntax, const char* text, size_t len)
	: CommonToken<AST, AST_Token, AST_Tree> (syntax, text, len) { }

    AST_Token (int syntax, const gcstring& text)
        : CommonToken<AST, AST_Token, AST_Tree> (syntax, text) { }

    /** The text denoted by THIS, if a string literal.  Undefined
     *  otherwise.  This is distinct from the actual text of a
     *  literal; all escape sequences have been replaced with their
     *  denotations. */
    virtual gcstring string_text () const;

    /** Append S to the value of string_text(), if allowed.  Otherwise
     *  undefined. */
    virtual void append_text(const gcstring& s);

protected:

    /** Used to produce factory objects. */
    AST_Token (int syntax) 
        : CommonToken<AST, AST_Token, AST_Tree>(syntax) {
    }

    void _print (std::ostream& out, int indent, ASTSet& visited);
};
    
class AST_Tree : public CommonTree<AST, AST_Token, AST_Tree> {
    typedef CommonTree<AST, AST_Token, AST_Tree> Parent;

public:

    NODE_BASE_CONSTRUCTORS (AST_Tree, Parent);

protected:

    /** Implements AST::print.  Default definition of printing on
     *  trees: prints (<OP> <LINE> <CHILD0> ...), where <OP> is the 
     *  external operator name and line is the source line number.
     *  Assumes the VISITED indicates ancestor nodes that have been
     *  printed, and restored its value when done. */
    void _print (std::ostream& out, int indent, ASTSet& visited);

    /** External name of this type of node, for printing purposes.
     *  This is NOT intended as a way of determine the type of a
     *  node, and is valid only until the next call on externalName. */
    virtual const char* externalName ();

};

/** The supertype of all tree nodes that represent types.  We could
 *  instead define type-specific operations in AST, but that clutters
 *  ASTs with operations that apply only to certain subtypes.  This
 *  class is intended to factor out the operations specific to types. */
class Type : public AST_Tree {

    friend class TypeVar_AST;
    friend class Unifier;

public:

    /** Overrides AST::asType. Effectively reveals the Type-specific
     *  operations on this node.  */
    Type_Ptr asType () {
        return this;
    }

    bool isType () {
        return true;
    }

    bool isFunctionType () {
        return false;
    }

    /** Reports an erroneous type reference, since types do not have types. */
    Type_Ptr getType ();

    /** The id_node representing my class.  NULL for function types
     *  and unbound type variables. */
    AST_Ptr getId ();

    /** My arity, if I am a function type.  Otherwise -1. */
    virtual int numParams ();

    /** The type of my Kth parameter, 0 <= K < numParams(). */
    virtual Type_Ptr paramType (int k);

    /** My return type, if I am a function type.  Otherwise NULL. */
    virtual Type_Ptr returnType ();

    /** My number of type parameters. */
    virtual int numTypeParams ();

    /** My Kth type parameter, 0 <= K < numTypeParams(),  For a
     *  function type, numTypeParams() == numParams() + 1; the 0th
     *  type parameter is the return type, and the K+1st is 
     *  paramType(K). */
    virtual Type_Ptr typeParam (int k);

    /** For function types, the type of the clousre on the first
     *  argument. If THIS is (t1, t2, ..., tn)->t0, then the result is
     *  (t2,...,tn)->t0.  Returns NULL if applied to other kinds of type
     *  or to parameterless function types. If f is a method, then
     *  this is the type of x.f.  */
    virtual Type_Ptr boundFunctionType ();

    /** an environment defining all my attributes. */
    virtual const Environ* getEnviron ();

    /** The type that THIS denotes, or THIS itself if it is not bound
     *  to another type.  It is the identity on everything but bound
     *  type variables. */
    virtual Type_Ptr binding ();

    /** Set binding () to be the same as that of TYPE.  Affects only
     *  type variables. */
    virtual void setTypeBinding (Type_Ptr type);

    /** A new, unbound type variable. */
    static Type_Ptr makeVar ();

    /** True iff I am a type variable. */
    virtual bool isTypeVariable ();

    /** True if I contain any unbound type variables. */
    static bool hasFreeVariables(Type_Ptr type);

    NODE_BASE_CONSTRUCTORS_INIT (Type, AST_Tree, _binding (this));

protected:

    /** Bind me to TYPE, assuming I am unbound. */
    void bind (Type_Ptr type);

    /** Unbind me. */
    void unbind ();

    /** Used internally by hasFreeVariables to do most of the work,
     *  avoiding circular traversals. */
    virtual bool hasFreeVariables (ASTSet& visited);

private:

    /** Type to which I am bound, or myself if unbound. */
    Type_Ptr _binding;

};

/** Unify a most-general function type having N formals with TYPE,
 *  returning true iff successful. */
extern bool makeFuncType (int n, Type_Ptr type, Unifier& subst);

/** Return a most-general function type having N formals. */
extern Type_Ptr makeFuncType (int n);

/** Return a most-general method type for a method of class CLAS
 *  having N>=1 formals. */
extern Type_Ptr makeMethodType (int n, Decl* clas);

/** Return a copy of TYPE with all unbound type variables replaced
 *  by fresh unbound variables. */
extern Type_Ptr freshen (Type_Ptr type);

/** Simultaneously freshen all unbound type variables in the trees in
 *  TYPES, replacing each TYPES[i] with a freshened version. */
extern void freshen (gcvector<Type_Ptr>& types);

/** A mapping from Types to Types used to present the results of
 *  unification.  Initially all arguments map to themselves. */
class Unifier {
public:
    /** A Unifier in which all values bind to themselves. */
    Unifier () : _numBound (0) {}
 
    /** True iff X is currently bound to a value other than itself. */
    bool isBound (Type_Ptr x) const;

    /** The current binding of X.  Always the same as X->binding(). */
    Type_Ptr binding (Type_Ptr x) const;

    /** The number of type variables bound in me. */
    int numBound () const {
        return _numBound;
    }

    /** Bind X to Y.  If x' is the current binding of X, and y' is the
     *  current binding of Y, then after this call, X and x' and Y will be
     *  bound to y'. */
    void bind(Type_Ptr x, Type_Ptr y);

    /** Make all current bindings recorded in me permanent by deleting
     *  all of them so that they are not unbound when I am finalized. */
    void setBindings ();

    /** Transfer all bindings recorded in OTHER to me, removing them
     *  from OTHER. */
    void transfer (Unifier& other);

    /** Unbind all bindings recorded in me. */
    ~Unifier ();

private:
    /** Copy constructor not allowed. */
    Unifier (const Unifier& source) { }

    int _numBound;
    std::vector<Type_Ptr> _bindings;

};

/** Extend SUBST so that T0 unifies with T1, returning true iff successful.
 *  Otherwise, returns false and leaves bindings and SUBST unchanged. */
extern bool unify (Type_Ptr t0, Type_Ptr t1, Unifier& subst);

/** Returns true iff T0 unifies with T1.  Does not modify any current
 *  bindings. */
extern bool unifies (Type_Ptr t0, Type_Ptr t1);

/** The supertype of AST_Trees that represent expressions that have a
 *  type. */
class Typed_Tree : public AST_Tree {
public:

    Type_Ptr getType ();

    bool setType (Type_Ptr type, Unifier& subst);

protected:

    void resolveTypes (Decl* context, Unifier& subst);
    
    /** Computes my type, which is then cached by getType(). */
    virtual Type_Ptr computeType ();

    Type_Ptr _type;

    NODE_BASE_CONSTRUCTORS_INIT (Typed_Tree, AST_Tree, _type(NULL));

};


/** Control structure: 
 *      For each child, VAR, of AST_Node* NODE, ...
 *  Usage:
 *      for_each_child (C, aTree) {
 *           <operations involving C (an AST_Node*)>
 *      } end_for;
 *  Inside the body, C_i_ is the index of C within aTree.
 */
#define for_each_child(Var, Node)                                            \
    do {                                                                     \
       AST_Ptr Var ## _n_ = Node;                                            \
       for (int Var ## _i_ = 0, Var ## _e_ = Var ## _n_->arity ();           \
            Var ## _i_ < Var ## _e_; Var ## _i_ += 1) {                      \
           const AST_Ptr Var  = Var ## _n_->child (Var ## _i_);

/** Control structure: 
 *      For each child, VAR, of AST_Node* NODE in reverse order, ...
 *  Usage:
 *      for_each_child (C, aTree) {
 *           <operations involving C (an AST_Node*)>
 *      } end_for;
 *  Inside the body, C_i_ is the index of C within aTree.
 */
#define for_each_child_reverse(Var, Node)                                    \
    do {                                                                     \
       AST_Ptr Var ## _n_ = Node;                                            \
       for (int Var ## _i_ = Var ## _n_->arity () - 1;                       \
            Var ## _i_ >= 0; Var ## _i_ -= 1) {                              \
           const AST_Ptr Var  = Var ## _n_->child (Var ## _i_);

/** Control structure: 
 *      For each child, VAR, of AST_Node* NODE, ...
 *  replacing the child with the value of VAR at the end of each iteration.
 *    
 *  Usage:
 *      for_each_child_var (C, aTree) {
 *           <operations involving C (an AST_Node*)>
 *      } end_for;
 */
#define for_each_child_var(Var, Node)                                        \
    do {                                                                     \
       AST_Ptr Var ## _n_ = Node;                                            \
       AST_Ptr Var = NULL;                                                   \
       for (int Var ## _i_ = 0;                                              \
            Var ## _i_ < (int) Var ## _n_->arity ();                         \
            _replace_and_incr (Var ## _n_, Var ## _i_, Var)) {               \
           Var = Var ## _n_->child (Var ## _i_);

#define end_for } } while (0)

/** Auxiliary function used by the for_each_child_var */
static inline int
_replace_and_incr (AST_Ptr& node, int& k, AST_Ptr& new_child)
{
    int n = new_child == NULL ? 0 
        : new_child->is_list () ? new_child->arity () 
        : 1;
    node->replace (k, new_child);
    return k += n;
}

/** A default definition of a method, METHOD, in class CLASS, taking
 *  formal parameter spec FORMALS (in parentheses) and returning void.
 *  ACTUALS is the list of formals parameter identifiers.  The
 *  resulting method recursively calls METHOD with ACTUALS on each
 *  child.
 *
 *  Example:
 *     PASSDOWN_METHOD(AST, mogrify, (int x), (x))
 *  produces
 *     void
 *     AST::mogrify (int x) 
 *     {
 *        for_each_child (_c_, this) {
 *             _c_->mogrify(x);
 *        } end_for;
 *     }
 */
#define PASSDOWN_METHOD(Class, Method, Formals, Actuals)                     \
void                                                                         \
Class::Method Formals {                                                      \
    for_each_child (_c_, this) {                                             \
        _c_->Method Actuals;                                                 \
    } end_for;                                                               \
}

/** As for PASSDOWN_METHOD, but returns THIS, and sets each child to
 *  the result of the recursive application.
 *
 *  Example:
 *     AST* PASSDOWN_VALUE_METHOD(AST, flatten, (), ())
 *  produces
 *     AST*
 *     AST::flatten () 
 *     {
 *        for_each_child (_c_, this) {
 *             _c_ = _c_->flatten (x);
 *        } end_for;
 *        return this;
 *     }
 */
#define PASSDOWN_VALUE_METHOD(Class, Method, Formals, Actuals)               \
Class::Method Formals {                                                      \
    for_each_child_var (_c_, this) {                                         \
        _c_ = _c_->Method Actuals;                                           \
    } end_for;                                                               \
    return this;                                                             \
}


/** Create an "id" node for the identifier TEXT, giving LOC as its
 *  location. TEXT must be a permanent string (that is, it must not
 *  get deallocated while the resulting node is in use.) */
extern AST_Ptr make_id (const char* text, const char* loc);

/** Convenience methods to create trees with given SYNTAX and various
 *  numbers of children. */
extern AST_Ptr consTree (int syntax);
extern AST_Ptr consTree (int syntax, AST_Ptr c0);
extern AST_Ptr consTree (int syntax, AST_Ptr c0, AST_Ptr c1);
extern AST_Ptr consTree (int syntax, AST_Ptr c0, AST_Ptr c1,
                         AST_Ptr c2);
extern AST_Ptr consTree (int syntax, AST_Ptr c0, AST_Ptr c1,
                         AST_Ptr c2, AST_Ptr c3);
/** Arbitrary number of children: FIRST and LIMIT are pointers into an
 *  array of AST_Ptrs indicating the first child and the position
 *  beyond the last child. */
extern AST_Ptr consTree (int syntax, AST_Ptr* first, AST_Ptr* limit);

#endif

