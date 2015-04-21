/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* exprs.cc: AST subclasses related to expressions. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/*****   Typed_Tree   *****/

Type_Ptr
Typed_Tree::getType ()
{
    if (_type == NULL)
        _type = computeType ();
    return _type;
}

bool
Typed_Tree::setType (Type_Ptr type, Unifier& subst)
{
    if (_type == NULL)
        _type = Type::makeVar ();
    return unify (_type, type, subst);
}

void
Typed_Tree::resolveTypes (Decl* context, Unifier& subst, Resolver& resolver)
{
    AST_Tree::resolveTypes (context, subst, resolver);
    getType ();
}

Type_Ptr
Typed_Tree::computeType ()
{
    return Type::makeVar ();
}

void
Typed_Tree::printOther (ostream& out, int indent, ASTSet& visited)
{
    if (getType () != NULL) {
        if (arity () == 0)
            out << " ";
        else
            out << endl << setw (indent + 4) << "";
        print (getType (), out, indent + 4, visited);
    }
}

/*****   NONE, TRUE, FALSE     *****/

class None_AST : public Typed_Tree {
protected:

    void printOther (ostream& out, int indent, ASTSet& visited) {
    }

    NODE_CONSTRUCTORS (None_AST, Typed_Tree);

};

NODE_FACTORY(None_AST, NONE);

class True_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (True_AST, Typed_Tree);

    void printOther (ostream& out, int indent, ASTSet& visited) {
    }

    Type_Ptr computeType () {
        return boolDecl->asType ();
    }

};

NODE_FACTORY(True_AST, TRUE);


class False_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (False_AST, Typed_Tree);

    void printOther (ostream& out, int indent, ASTSet& visited) {
    }

    Type_Ptr computeType () {
        return boolDecl->asType ();
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

    /** Set my type. */
    virtual void setExprType (Unifier& subst) {
        if (!setType (calledExpr ()->getType ()->binding ()->returnType (),
                      subst)) {
            error (this, "inappropriate function return type");
            return;
        }
    }

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        Typed_Tree::resolveTypes (context, subst, resolver);
        Type_Ptr funcType;
        funcType = calledExpr ()->getType ();

        if (!makeFuncType (numActuals (), funcType, subst)) {
            error (this,
                   "called object is not a %d-parameter function",
                   numActuals ());
            return;
        }

        funcType = funcType->binding ();
        setExprType (subst);

        if (funcType->numParams () != numActuals ()) {
            error (this, "wrong number of parameters to function");
            return;
        }
        for (int i = 0; i < numActuals (); i += 1) {
            if (!unify (actualParam (i)->getType (),
                        funcType->paramType (i), subst)) {
                error (this, "non-matching parameter type (parameter #%d)",
                       i);
                break;
            }
        }

    }
};

/** A function call. */
class Call_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Call_AST, Callable);

    AST_Ptr resolveAllocators (const Environ* env) {
        Callable::resolveAllocators (env);
        AST_Ptr callable = calledExpr ();
        if (callable->isType ()) {
            gcvector<AST_Ptr> initArgs;
            AST_Ptr init = consTree(ATTRIBUTEREF, callable, 
                                    make_id ("__init__", loc ()));
            initArgs.push_back (init);
            initArgs.push_back (consTree (NEW, callable));
            for (int i = 0; i < numActuals (); i += 1)
                initArgs.push_back (actualParam (i));
            return AST::make_tree (CALL1, &initArgs[0],
                                   &initArgs[initArgs.size ()]);
        }
        return this;
    }

};

NODE_FACTORY (Call_AST, CALL);

/***** CALL1 *****/

/** __init__(new T, ...)      */
class Call1_AST : public Call_AST {
protected:

    NODE_CONSTRUCTORS (Call1_AST, Call_AST);

    Type_Ptr computeType () {
        return actualParam (0)->getType ();
    }

};

NODE_FACTORY (Call1_AST, CALL1);

/***** NEW *****/

/**  new T     */
class New_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (New_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        if (!setType (child (0)->asType (), subst)) {
            error (this, "inconsistent types");
        }
    }

};

NODE_FACTORY (New_AST, NEW);


/** A binary operator. */
class Binop_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Binop_AST, Callable);

};    

NODE_FACTORY (Binop_AST, BINOP);

/***** COMPARE *****/

/** A comparison yielding bool */
class Compare_AST : public Binop_AST {
protected:

    NODE_CONSTRUCTORS (Compare_AST, Binop_AST);

    Type_Ptr computeType () {
        return boolDecl->asType ();
    }

};

NODE_FACTORY (Compare_AST, COMPARE);



/***** LEFT_COMPARE *****/

/** A comparison yielding its second operand's type. */
class LeftCompare_AST : public Binop_AST {
protected:

    NODE_CONSTRUCTORS (LeftCompare_AST, Binop_AST);

    void setExprType (Unifier& subst) {
        if (!setType (actualParam (1)->getType (), subst)) {
            error (this, "inappropriate type");
            return;
        }
    }

    Type_Ptr computeType () {
        return actualParam (1)->getType ();
    }

};

NODE_FACTORY (LeftCompare_AST, LEFT_COMPARE);


/** A unary operator. */
class Unop_AST : public Callable {

    NODE_CONSTRUCTORS (Unop_AST, Callable);

};    

NODE_FACTORY (Unop_AST, UNOP);


/***** SUBSCRIPTION *****/

/** E1[E2] */
class Subscription_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Subscription_AST, Callable);

    void addTargetDecls (Decl* enclosing) {
    }

};

NODE_FACTORY (Subscription_AST, SUBSCRIPT);

class Subscript_Assign_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Subscript_Assign_AST, Callable);

    void addTargetDecls (Decl* enclosing) {
    }

};

NODE_FACTORY (Subscript_Assign_AST, SUBSCRIPT_ASSIGN);
    
    
/***** SLICING *****/

/** E1[E2:E3] */
class Slicing_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Slicing_AST, Callable);

    void addTargetDecls (Decl* enclosing) {
    }

};

NODE_FACTORY (Slicing_AST, SLICE);

class Slicing_Assign_AST : public Callable {
protected:

    NODE_CONSTRUCTORS (Slicing_Assign_AST, Callable);

    void addTargetDecls (Decl* enclosing) {
    }

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

    Decl* getDecl (int k = 0) {
        return getId ()->getDecl (k);
    }

    int numDecls () {
        return getId ()->numDecls ();
    }

    void addTargetDecls (Decl* enclosing) {
    }

    AST_Ptr resolveStaticSelections (const Environ* env) {
        AST_Ptr left = child (0)->resolveStaticSelections (env);
        if (!left->isType ())
            return this;
        AST_Ptr id = getId ();
        if (id->getDecl () != NULL)
            return id;
        gcstring name = id->as_string ();
        const Environ* members = left->getDecl ()->getEnviron ();
        Decl_Vector defns;
        members->find_immediate (name, defns);
        if (defns.empty ()) {
            error (this, "no definition of %s in type", name.c_str ());
            id->addDecl (makeUnknownDecl (name, false));
        }
        for (size_t i = 0; i < defns.size (); i += 1)
            id->addDecl (defns[i]);
        return id;
    }

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        int errs0 = numErrors ();
        child (0)->resolveTypes (context, subst, resolver);
        AST_Ptr id = getId ();
        id->resolveSelectedType (subst, resolver);
        gcstring name = id->as_string ();
        Decl* expectedClassDecl = resolver[id]->getContainer ();
        if (expectedClassDecl != NULL && expectedClassDecl->isType ()) {
            gcvector<Type_Ptr> linkedTypes;
            linkedTypes.push_back (expectedClassDecl->asBaseType ());
            linkedTypes.push_back (id->getType ());
            freshen (linkedTypes);
            if (!unify (linkedTypes[0], child (0)->getType (), subst)
                || (errs0 == numErrors () 
                    && !setType (linkedTypes[1], subst))) {
                error (this,
                       "attribute %s has no definition that fits the context.",
                       name.c_str ());
            }
        }
    }

    AST_Ptr resolveSimpleIds (const Environ* env) {
        replace (0, child (0)->resolveSimpleIds (env));
        AST_Ptr id = getId ();
        gcstring name = id->as_string ();
        const Decl_Vector& decls = outerEnviron->get_members ();
        for_each_decl (classd, decls) {
            if (classd->isType ()) {
                Decl_Vector candidates;
                classd->getEnviron ()->find_immediate (name, candidates);
                for_each_decl (d, candidates) {
                    id->addDecl (d);
                } end_for;
            }
        } end_for;
        if (id->numDecls () == 0) {
            error (this, "no definitions of the %s attribute", name.c_str ());
            id->addDecl (makeUnknownDecl (name, false));
        }
        return this;
    }

};

NODE_FACTORY (AttributeRef_AST, ATTRIBUTEREF);

/***** TUPLE *****/

/** (E1, ...)  */
class Tuple_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (Tuple_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        Typed_Tree::resolveTypes (context, subst, resolver);
        if (arity () > 3)
            error (this, "tuple has too many elements (max 3)");
        Type_Ptr componentTypes[3];
        for (size_t i = 0; i < arity (); i += 1)
            componentTypes[i] = child (i)->getType ();
        Type_Ptr tupleType =
            tupleDecl[arity ()]->asType (arity (), componentTypes);
        if (!setType (tupleType, subst))
            error (this, "type mismatch on tuple");
    }        

};

NODE_FACTORY (Tuple_AST, TUPLE);

/***** TARGET_LIST *****/

/** (TARGET, ...) on left-hand side of assignment, for. */
class TargetList_AST : public Tuple_AST {
protected:

    NODE_CONSTRUCTORS (TargetList_AST, Tuple_AST);

    void addTargetDecls (Decl* enclosing) {
        for_each_child (c, this) {
            c->addTargetDecls (enclosing);
        } end_for;
    }

};

NODE_FACTORY (TargetList_AST, TARGET_LIST);


/***** LIST_DISPLAY *****/

/** [E1, ...]  */
class ListDisplay_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (ListDisplay_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        Typed_Tree::resolveTypes (context, subst, resolver);
        Type_Ptr componentType;
        if (arity () == 0)
            componentType = Type::makeVar ();
        else
            componentType = child (0)->getType ();
        for (size_t i = 1; i < arity (); i += 1)
            if (!unify (componentType, child (i)->getType (), subst)) {
                error (child (i), "type mismatch in list display");
                break;
            }
        Type_Ptr listType =
            listDecl->asType (1, componentType);
        if (!setType (listType, subst))
            error (this, "type mismatch on list display");
    }    

};

NODE_FACTORY (ListDisplay_AST, LIST_DISPLAY);


/***** DICT_DISPLAY *****/

/** { a: b, ... }  */
class DictDisplay_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (DictDisplay_AST, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        Typed_Tree::resolveTypes (context, subst, resolver);
        Type_Ptr keyType, valType;
        if (arity () == 0) {
            keyType = Type::makeVar ();
            valType = Type::makeVar ();
        } else  {
            keyType = child (0)->child (0)->getType ();
            valType = child (0)->child (1)->getType ();
        }
        for (size_t i = 1; i < arity (); i += 1) {
            if (!unify (keyType, child (i)->child (0)->getType (), subst)) {
                error (child (i), "key type mismatch in dict display");
                break;
            }
            if (!unify (valType, child (i)->child (1)->getType (), subst)) {
                error (child (i), "value type mismatch in dict display");
                break;
            }
        }
        Type_Ptr dictType =
            dictDecl->asType (2, keyType, valType);
        if (!setType (dictType, subst))
            error (this, "type mismatch on dict display");
    }

};

NODE_FACTORY (DictDisplay_AST, DICT_DISPLAY);



/** A class of expression in which its subexpressions must agree as to
 *  type and its value's type is that of its subexpressios. */
class BalancedExpr : public Typed_Tree {
protected:

    NODE_BASE_CONSTRUCTORS (BalancedExpr, Typed_Tree);

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        int k = arity ();
        Typed_Tree::resolveTypes (context, subst, resolver);
        if (!unify (child (k - 2)->getType (), child (k - 1)->getType (), subst))
            error (this, "types of alternatives do not match");
        if (!setType (child (k - 1)->getType (), subst))
            error (loc (), "inconsistent types");
    }

};

/***** IF_EXPR *****/

/**  E1 if Cond else E2  */
class IfExpr_AST : public BalancedExpr {
protected:

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        Typed_Tree::resolveTypes (context, subst, resolver);
        if (!unify (child (0)->getType (), boolDecl->asType (), subst)) {
            error (child (0), "condition must be boolean");
        }
    }


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


