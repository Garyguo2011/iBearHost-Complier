/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* exprs.cc: AST subclasses related to expressions. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/* The Horn framework has a provision (the NODE_FACTORY macro) that
 * allows AST subclasses to "register" themselves with the parser and
 * associate themselves with a particular syntactic category so that
 * the parser will create instances of the appropriate subclass when
 * asked to produce an AST node with a particular operator.  The
 * NODE_..._CONSTRUCTOR... macros set up the necessary constructors
 * and factory declarations in any given class.  To associate a
 * class with a given operator token, pass the (int) value of that
 * token's syntactic category to the NODE_FACTORY macro (for
 * one-character tokens, the character itself is usually the syntactic
 * category; for other tokens, use the name declared in the Horn
 * source file (those definitions appear in ast-parser.hh, included above).
 * There are examples in this and other files.
 */

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
Typed_Tree::resolveTypes (Decl* context, Unifier& subst)
{
    AST_Tree::resolveTypes (context, subst);
    getType ();
}

Type_Ptr
Typed_Tree::computeType ()
{
    return Type::makeVar ();
}

/* The following is an EXAMPLE of a potentially useful AST class
 * structure, showing the macros you can use to set up base classes
 * and their subtypes. */

/*****   NONE, TRUE, FALSE     *****/

class None_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (None_AST, Typed_Tree);

};

NODE_FACTORY(None_AST, NONE);

class True_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (True_AST, Typed_Tree);

    /** Return the type of boolDecl. */
    Type_Ptr computeType () {
        return boolDecl->asType ();
    }

    /** Set type basically. */
    void resolveTypes (Decl* context, Unifier& subst) {
        setType(computeType(), subst);
    }

};

NODE_FACTORY(True_AST, TRUE);


class False_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS (False_AST, Typed_Tree);

    /** Return the type of boolDecl. */
    Type_Ptr computeType () {
        return boolDecl->asType ();
    }

    /** Set type basically. */
    void resolveTypes (Decl* context, Unifier& subst) {
        setType(computeType(), subst);
    }
};

NODE_FACTORY(False_AST, FALSE);


/*****   CALLS    *****/

/** The supertype of "callable" things, including ordinary calls,
 *  binary operators, unary operators, subscriptions, and slices. */

class Callable : public Typed_Tree {
protected:

    NODE_BASE_CONSTRUCTORS (Callable, Typed_Tree);

    bool isCallable () {
        return true;
    }

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

    // PUT COMMON CODE DEALING WITH TYPE-CHECKING or SCOPE RULES HERE.

    void resolveTypes(Decl* context, Unifier& subst) {
        AST::resolveTypes(context, subst);
        Type_Ptr myType = makeFuncType(arity()-1);

        for (int count = 1; count < arity(); count++) {
            unify((Type_Ptr)myType->child(count), child(count)->getType(), subst);
        }

        int unified = 0;
        Type_Ptr returnType;

        if (child(0)->oper()->syntax() == ID) {
            // fprintf(stderr, "i am l ive got this many decls %d \n", child(0)->numDecls());
            Decl_Vector new_decls;
            for (int count = 0; count < child(0)->numDecls(); count++) {
                // cerr << "\n decl is \n";
                // child(0)->getDecl(count)->print(cerr);
                // cerr << "\n potential type \n";
                // child(0)->getDecl(count)->getType()->print(cerr,4);
                // cerr << "\n my type is \n";
                // myType->print(cerr, 4);
                // cerr << "\n";
                if(unifies(child(0)->getDecl(count)->getType(), myType)) {
                    unified++;
                    returnType = (Type_Ptr)child(0)->getDecl(count)->getType()->child(0);
                    new_decls.push_back(child(0)->getDecl(count));
                }
                else {
                    child(0)->removeDecl(count);
                    count--;
                }
            }
        }

        else if (child(0)->oper()->syntax() == ATTRIBUTEREF) {
            AST_Ptr id = child(0)->child(1);
            print(cerr, 4);
            cerr << "\n";
            id->print(cerr, 4);
            cerr << "\n";
            for (int count = 0; count < child(0)->numDecls(); count++) {
                if(unifies(id->getDecl(count)->getType(), myType)) {
                    unified++;
                    returnType = (Type_Ptr)id->getDecl(count)->getType()->child(0);
                }
                else {
                    child(0)->removeDecl(count);
                    count--;
                }
            }
        }

        else {
            if (unifies(myType, child(0)->getType())) {
                unified++;
                setType((Type_Ptr)myType->child(0), subst);
            }
        }

        if (unified==0) {
            error (loc(), "no functions match");
        }
        else if (unified==1) {
            setType(returnType, subst);
        }
        else {
            setType((Type_Ptr)myType->child(0), subst);
        }
    }
};

/** Call AST for function call, inherited from Callable. */
class Call_AST : public Callable {

protected:

    /** First check whether the node of AST is a TYPE(rescursively call otherwirse),
     *  then check whether there's a "__init__" method. If it is, create and return
     *  a new tree with the node of CALL1 that follows the relating rules and throw
     *  an error otherwise. */
    AST_Ptr resolveAllocators (const Environ* env){
        if (this->child(0)->oper()->syntax() == TYPE){
            AST_Ptr init_tree = make_id("__init__", "0");
            gcstring name = this->child(0)->child(0)->as_string();
            Decl* decl = classes->find(name);
            Decl* init_decl = decl->getEnviron()->find_immediate("__init__");
            if (init_decl != NULL){
                init_tree->addDecl(init_decl);
                // AST_Ptr new_tree = consTree(NEW, this->child(0));
                std::vector <AST_Ptr> temp;
                temp.push_back(init_tree);
                temp.push_back(consTree(NEW, this->child(0)));
                if (this->arity() >= 2){
                    // AST_Ptr expr_tree = this->child(1);
                    for (unsigned int i = 1; i < this->arity(); i++){
                    temp.push_back(this->child(i));
                    }
                }
                // AST_Ptr* new_args = &temp[0];
                // AST_Ptr new_expr_tree = AST::make_tree(EXPR_LIST, new_args, new_args + sizeof (new_args) / sizeof(new_args[0]));
                // return AST::make_tree(CALL1, new_args, new_args + sizeof (new_args) / sizeof(new_args[0]));
                return AST::make_tree(CALL1, &temp[0], &temp[temp.size()]);    
            } else {
                error(loc(), "No __init__ method found.");   
            }
            
        } else {
            for_each_child_var (c, this) {
                c = c->resolveAllocators (env);
            } end_for;
        }
        return this;
    }

    // void resolveTypes (Decl* context, Unifier& subst)
    // {
    //     context get environ find immediate id name 


    // }
    NODE_CONSTRUCTORS (Call_AST, Callable);

};

NODE_FACTORY (Call_AST, CALL);

/** Call1 AST for Call1 from the grammar rule, inherited from Callable. */
class Call1_AST : public Callable {
protected:
    NODE_CONSTRUCTORS (Call1_AST, Callable);

    /** Return the id of Call1 Tree according to the grammar rule.*/
    AST_Ptr getId () {
        return child(1)->child(0)->child(0);
    }

    /** If a class declaration has been found within the scope, then the type to
     *  the type of classDecl, otherwise throw an error. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes(context, subst);
        Decl* classDecl = classes->find(getId()->as_string());
        if (classDecl != NULL) {
            setType(classDecl->asGenericType(), subst);
        } else {
            error(loc(), "Class Declaration missing");
        }
    }
};

NODE_FACTORY (Call1_AST, CALL1);

/** A binary operator. */
class Binop_AST : public Callable {
protected:
    NODE_CONSTRUCTORS (Binop_AST, Callable);

};    

NODE_FACTORY (Binop_AST, BINOP);

/** A unary operator. */
class Unop_AST : public Callable {
protected:
    NODE_CONSTRUCTORS (Unop_AST, Callable);

};    

NODE_FACTORY (Unop_AST, UNOP);

// FIXME: There are others as well.

// /** ID */
// class ID_AST : public AST_Tree {
// protected:
//     NODE_CONSTRUCTORS(ID_AST, AST_Tree);

//     AST_Ptr getId()
//     {
//         return child(0);
//     }


// };

// NODE_FACTORY(ID_AST, ID);

/** Subscriptions AST for subscript from the grammar rule, inherited from Callable. */
class Subscript_AST : public Callable {
    NODE_CONSTRUCTORS(Subscript_AST, Callable);
};

NODE_FACTORY (Subscript_AST, SUBSCRIPT);

/** Slices AST for slice from the grammar rule, inherited from Callable. */
class Slice_AST : public Callable {
    NODE_CONSTRUCTORS(Slice_AST, Callable);
};

NODE_FACTORY (Slice_AST, SLICE);


class Subscript_Assign_AST : public Callable {
    NODE_CONSTRUCTORS(Subscript_Assign_AST, Callable);
};
NODE_FACTORY (Subscript_Assign_AST, SUBSCRIPT_ASSIGN);


class Slice_Assign_AST: public Callable {
    NODE_CONSTRUCTORS(Slice_Assign_AST, Callable);
};
NODE_FACTORY (Slice_Assign_AST, SLICE_ASSIGN);


/** Compare AST for compare from the grammar rule, inherited from Binop_AST. */
class Compare_AST : public Binop_AST {
protected:
    
    NODE_CONSTRUCTORS(Compare_AST, Binop_AST);

};

NODE_FACTORY(Compare_AST, COMPARE);

/** Left Compare AST for left_compare from the grammar rule, inherited from Binop_AST. */
class LeftCompare_AST : public Binop_AST {
protected:

    NODE_CONSTRUCTORS(LeftCompare_AST, Binop_AST);
};

NODE_FACTORY(LeftCompare_AST, LEFT_COMPARE);

/** Attributeref AST for attributeref from the grammar rule, inherited from Typed_Tree. */
class Attributeref_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(Attributeref_AST, Typed_Tree);

    void addTargetDecls (Decl* enclosing) {}

    /** Simply recursively call it. */
    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        int count = 0;
        for_each_child_var (c, this){
            if (count == 0){
                c = c->resolveSimpleIds(env);
            }
            count++;
        } end_for;
        if (!child(0)->isType()) {
            AST_Ptr attr = child(1);
            Decl_Vector all_classes = classes->get_members();
            for (Decl_Vector::const_iterator i = all_classes.begin (); 
             i != all_classes.end (); 
             i++) {
                Decl_Vector class_members = (*i)->getEnviron()->get_members();
                for (Decl_Vector::const_iterator member = class_members.begin (); 
                 member != class_members.end (); 
                 member++) {
                    if ((*member)->getName() == attr->as_string()) {
                        attr->addDecl(*member);
                    }
                }
            }
        }
        return this;
    }

    AST_Ptr getId() {
        return child(1);
    }

    void addDecl(Decl* decl) {
        getId()->addDecl(decl);
    }

    /** Resolve all selections of the form CLASS.ID by replacing them
     *  with ID, appropriately decorated, assuming that ENV defines
     *  all visible classes.   Returns the modified tree. */
    AST_Ptr resolveStaticSelections (const Environ* env) {
        if (child(0)->oper()->syntax() == TYPE) {
            AST_Ptr id0 = child(0)->child(0);
            Decl* decl = env->find_immediate(id0->as_string());
            AST_Ptr id1 = this->child(1);
            if (decl != NULL) {
                Decl_Vector decls;
                decl->getEnviron()->find_immediate(id1->as_string(), decls);
                for (Decl_Vector::const_iterator i = decls.begin ();
                         i != decls.end ();
                         i++)
                {
                    if ((*i)->isMethod()) {
                        id1->addDecl((*i));
                    }
                }
            } 
            else {
                error(loc(), "Instance method not found.");
            }
            return id1;
        }
        else {
            return this;
        }
    }

    /** For E.x, first resolve type of E, then go through every decl of x 
     *  and check whether E is a class and the decl of x is an attribute of E
     */
    void resolveTypes(Decl* context, Unifier& subst) {
        AST_Ptr obj = child(0);
        AST_Ptr attr = child(1);
        obj->resolveTypes(context, subst);
        for (int count = 0; count < attr->numDecls(); count++) {
            if (!unify(obj->getType(),attr->getDecl(count)->getContainer()->asGenericType() ,subst)) {
                attr->removeDecl(count);
            }

        }
        if (attr->numDecls() == 1) {
            setType(attr->getDecl()->getType(), subst);
        } else {
            error(loc(), "attr not found");
        }
    }
};

NODE_FACTORY(Attributeref_AST, ATTRIBUTEREF);

/** Tuple AST Tree for tuple from the grammar rule, inherited from Typed_Tree. */
class Tuple_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS(Tuple_AST, Typed_Tree);

    /** Resolve types seperately based on its arity. Set type accordingly
     *  iff 0 <= arity() <= 3. Otherwise throw an error. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes (context, subst);

        switch (arity())
        {
            case 0:
            {
                setType(tuple0Decl->asType(), subst);
                break;
            }
            case 1:
            {
                Type_Ptr type_list[1];
                type_list[0] = child(0)->getType();
                setType(tuple1Decl->asType(arity(), type_list), subst);
                break;
            }
            case 2:
            {
                Type_Ptr type_list[2];
                type_list[0] = child(0)->getType();
                type_list[1] = child(1)->getType();
                setType(tuple2Decl->asType(arity(), type_list), subst);
                break;
            }
            case 3:
            {
                Type_Ptr type_list[3];
                type_list[0] = child(0)->getType();
                type_list[1] = child(1)->getType();
                type_list[2] = child(2)->getType();
                setType(tuple3Decl->asType(arity(), type_list), subst);
                break;
            }
            default:
            {
                error(loc(), "Tuple has more than 3 children");
            }
        }
    }

};

NODE_FACTORY(Tuple_AST, TUPLE);

/** TargetList AST Tree for targetlist from the grammar rule, inherited from Typed_Tree. */
class TargetList_AST : public Typed_Tree {
protected:

    NODE_CONSTRUCTORS(TargetList_AST, Typed_Tree);
};

NODE_FACTORY(TargetList_AST, TARGET_LIST);

/** List Display AST Tree for list_display from the grammar rule, inherited from Typed_Tree. */
class ListDisplay_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(ListDisplay_AST, Typed_Tree);

    /** Typechecking for every child and throw an error if elements in the list have
     *  multiple types. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST::resolveTypes (context, subst);
        if (arity() == 0) {
            setType(listDecl->asType(1, Type::makeVar()), subst);
        } else {
            Type_Ptr elements[1];
            elements[0] = child(0)->getType();
            Type_Ptr first_type = elements[0];
            for (unsigned int i = 1; i < arity() ; i++) {
                if (!unify(first_type, child(i)->getType(), subst)) {
                    error (loc (), "Elements in list are not same types");
                }
            }
            setType(listDecl->asType(1, elements), subst);
        }
    }
};

NODE_FACTORY(ListDisplay_AST, LIST_DISPLAY);

/** Dictionary Display AST Tree for dict_display from the grammar rule, inherited from Typed_Tree. */
class DictDisplay_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(DictDisplay_AST, Typed_Tree);
    void resolveTypes (Decl* context, Unifier& subst) 
    {
        AST::resolveTypes (context, subst);
        if (arity() == 0) {
            Type_Ptr type_list[2];
            type_list[0] = Type::makeVar();
            type_list[1] = Type::makeVar();
            setType(dictDecl->asType (2, type_list), subst);
        } else {
            Type_Ptr keyType = child(0)->child(0)->getType();

            if (unify(keyType, boolDecl->asType(), subst) || 
                unify(keyType, intDecl->asType(), subst) || 
                unify(keyType, strDecl->asType(), subst)) {
                Type_Ptr elements[2];
                elements[0] = child(0)->child(0)->getType();
                elements[1] = child(0)->child(1)->getType();
                Type_Ptr first_type = dictDecl->asType(2, elements);
                for (unsigned int i = 1; i < arity() ; i++) {
                    Type_Ptr rest[2];
                    rest[0] = child(i)->child(0)->getType();
                    rest[1] = child(i)->child(1)->getType();
                    Type_Ptr rest_type = dictDecl->asType(2, rest);
                    if (!unify(first_type, rest_type, subst)) {
                        error (loc (), "Elements in dict are not same types");
                    }
                }
                setType(first_type, subst);
            } else {
                error(loc(), "invalid key type");
            }
            
        }
    }
};

NODE_FACTORY(DictDisplay_AST, DICT_DISPLAY);

/** If expression AST for if, inherited from Typed_Tree. */
class IfExpr_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(IfExpr_AST, Typed_Tree);

    /** E1 if C else E2. Throw out an error if C doesn't have a type of bool,
     *  otherwise check whether E1 and E2 can be unified. */
    void resolveTypes (Decl* context, Unifier& subst) 
    {
        AST::resolveTypes (context, subst);

        if (!unify(child(0)->getType(), boolDecl->asType(), subst)) {
            error(loc(), "IF_EXPR expression is not bool");
        }

        if (unify(child(1)->getType(), child(2)->getType(), subst)) {
            setType(child(1)->getType(), subst);
        } else {
            error(loc(), "IF_EXPR Inconsistent Types");
        }
    }
};

NODE_FACTORY(IfExpr_AST, IF_EXPR);

/** And AST Tree for and, inherited from Typed_Tree. */
class And_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(And_AST, Typed_Tree);

    /** Check whether the type of first child and the type of second child
     *  can be unified. Throw an error if they can't. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST_Tree::resolveTypes (context, subst);

        if (!unify(child(0)->getType(), child(1)->getType(), subst)) {
            error (loc (), "And Statement Expressions doesn't match");
        } else {
            setType(child(0)->getType(), subst);    
        }
    }
};

NODE_FACTORY(And_AST, AND);

/** OR AST for or, inherited from Typed_Tree. */
class Or_AST : public Typed_Tree {
protected:
    NODE_CONSTRUCTORS(Or_AST, Typed_Tree);

    /** Check whether the type of first child and the type of second child
     *  can be unified. Throw an error if they can't. */
    void resolveTypes (Decl* context, Unifier& subst) {
        AST_Tree::resolveTypes (context, subst);

        if (!unify(child(0)->getType(), child(1)->getType(), subst)) {
            error (loc (), "Or Statement Expressions doesn't match");
        } else {
            setType(child(0)->getType(), subst);    
        }
    }
};

NODE_FACTORY(Or_AST, OR);


