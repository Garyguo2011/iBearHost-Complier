/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* ast.cc: Basic AST subclasses. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;


/* Definitions of methods in base class AST. */

AST::AST ()
    : _erroneous (false)
{
}

void
AST::copyChildren (int k, AST_Ptr node, int first, int len)
{
    for (int i = len - 1; i >= 0; i -= 1) {
        insert (k, node->child (first + i));
    }
}

AST_Ptr
AST::retypedNode (int syntax)
{
    AST_Ptr result = consTree(syntax);
    result->set_loc (loc ());
    result->copyChildren (0, this, 0, arity ());
    return result;
}

void
AST::print (ostream& out, int indent)
{
    ASTSet visited;
    print(this, out, indent, visited);
}

void
AST::print (AST_Ptr tree, std::ostream& out, int indent, ASTSet& visited)
{
    tree->_print (out, indent, visited);
}

Type_Ptr
AST::asType ()
{
    return NULL;
}

bool
AST::isType ()
{   
    int syntax = this->oper()->syntax();
    if (syntax == TYPE_VAR || syntax == FUNCTION_TYPE || syntax == TYPE){
        return true;
    }
    return false; 
}

AST_Ptr
AST::getId ()
{
    UNIMPLEMENTED (getId);
}

int
AST::numDecls ()
{
    return _decls.size();
}

Decl*
AST::getDecl (int k)
{
    //assert (k >= 0 && k < (int) _decls.size ());
    if ( _decls.size() > k) {
        return _decls[k];
    }
    else {
        return NULL;
    }
}

void
AST::addDecl (Decl* decl)
{
    _decls.push_back (decl);
}

void
AST::removeDecl (int k)
{ 
    assert (k >= 0 && k < (int) _decls.size ());
    _decls.erase (_decls.begin () + k);
}

Type_Ptr
AST::getType ()
{
    return _type;
}

bool
AST::setType (Type_Ptr type, Unifier& subst)
{
    if (_type == NULL) {
        _type = type;
        return true;
    }
    else {
        return unify(_type, type, subst);
    }
}

/** Default does nothing. */
AST_Ptr
AST::doOuterSemantics ()
{
    AST_Ptr dast;
    this->collectDecls(fileDecl);
    dast = this->resolveSimpleIds(fileDecl->getEnviron());
    dast->resolveSimpleTypeIds(fileDecl->getEnviron());
    dast = dast->resolveAllocators(fileDecl->getEnviron());
    dast = dast->resolveStaticSelections(fileDecl->getEnviron());
    dast->resolveTypesOuter(fileDecl);
    Unifier* subst = new Unifier();
    dast->resolveTypes(fileDecl, *subst);
    subst->setBindings();
    return dast;
}

void
AST::collectDecls (Decl* enclosing)
{
    switch(this->oper()->syntax()) {
        case ASSIGN:
        {
            this->child(0)->addTargetDecls(enclosing);
            this->child(1)->collectDecls(enclosing);
            break;
        }
        case DEF:
        case METHOD:
        {
            AST_Ptr id = this->child(0);
            Decl* decl = enclosing->addDefDecl(id);
            if (decl != NULL) {
                id->addDecl(decl);
                for_each_child (c, this) {
                    c->collectDecls (decl);
                } end_for;
            }
            break;
        }
        case CLASS:
        {
            AST_Ptr id = this->child(0);
            const gcstring name = id->as_string();
            AST_Ptr params = this->child(1);
            if (name == "str") {
                Decl* decl = makeClassDecl(name, consTree(TYPE_FORMALS_LIST));
                strDecl = decl;
                id->addDecl(decl);
            }
            else if (name == "int") {
                Decl* decl = makeClassDecl(name, consTree(TYPE_FORMALS_LIST));
                intDecl = decl;
                id->addDecl(decl);
            }
            /** TODO
            
            Make class declarations for all other classes in prelude.
            Make sure to initialize the proper variable in decls.cc, eg inDecl, strDecl

            Please follow examples.

            */

            else if (name == "bool") {
                Decl* decl = makeClassDecl(name, params);
                boolDecl = decl;
                id->addDecl(decl);
            }
            else if (name == "range") {
                Decl* decl = makeClassDecl(name, params);
                rangeDecl = decl;
                id->addDecl(decl);
            }
            // need inline substitution
            else if (name == "list") {
                Decl* decl = makeClassDecl(name, params);
                this->collectTypeVarDecls(decl);
                listDecl = decl;
                id->addDecl(decl);
            }
            else if (name == "dict") {
                Decl* decl = makeClassDecl(name, params);
                this->collectTypeVarDecls(decl);
                dictDecl = decl;
                id->addDecl(decl);
            }
            else if (name == "tuple0") {
                Decl* decl = makeClassDecl(name, params);
                tuple0Decl = decl;
                id->addDecl(decl);
            }
            else if (name == "tuple1") {
                Decl* decl = makeClassDecl(name, params);
                this->collectTypeVarDecls(decl);
                tuple1Decl = decl;
                id->addDecl(decl);
            }
            else if (name == "tuple2"){
                Decl* decl = makeClassDecl(name, params);
                this->collectTypeVarDecls(decl);
                tuple2Decl = decl;
                id->addDecl(decl);
            }
            else if (name == "tuple3"){
                Decl* decl = makeClassDecl(name, params);
                this->collectTypeVarDecls(decl);
                tuple3Decl = decl;
                id->addDecl(decl);
            }
            /* END */
            
            else {
                Decl* decl = enclosing->addClassDecl(this);
                this->collectTypeVarDecls(decl);
                if (decl != NULL) {
                    id->addDecl(decl);
                    for_each_child (c, this) {
                        c->collectDecls (decl);
                    } end_for;
                }
            }
            break;
        }
        case FORMALS_LIST:
        {
            for (unsigned int count = 0; count < this -> arity(); count++) {
                AST_Ptr param = this->child(count);
                Decl* decl;
                if (param->oper()->syntax() == TYPED_ID) {
                    decl = makeParamDecl(param->child(0)->as_string(),
                                        enclosing,
                                        count,
                                        param->child(1));
                    param->child(0)->addDecl(decl);
                }
                else {
                    decl = makeParamDecl(param->as_string(),
                                        enclosing,
                                        count,
                                        Type::makeVar());
                    param->addDecl(decl);
                }
                enclosing->addMember(decl);
            }
            break;
        }
        default:
        {
            for_each_child (c, this) {
                c->collectDecls (enclosing);
            } end_for;
            break;
        }
    }
}

void
AST::collectTypeVarDecls (Decl* enclosing)
{

    AST_Ptr params = this->child(1);
    for (unsigned int count = 0; count < params->arity(); count++) {
        AST_Ptr param = params->child(count);
        AST_Ptr paramId = param->child(0);
        Decl* paramType = makeTypeVarDecl(paramId->as_string(), param);
        param->addDecl(paramType);
    }

}

void
AST::addTargetDecls (Decl* enclosing)
{
    switch(this->oper()->syntax()) {
        case TARGET_LIST:
        {
            for_each_child(target, this) {
                switch(target->oper()->syntax()) {
                    case ID:
                    {
                        Decl* decl = enclosing->addVarDecl(target);
                        if (decl != NULL) {
                            target->addDecl(decl);
                        }
                        break;
                    }
                    case TYPED_ID:
                    {
                        // TODO
                        AST_Ptr id = target->child(0);
                        Type_Ptr type = (Type_Ptr) target->child(1);
                        Decl* decl = enclosing->addVarDecl(id);
                        if (decl != NULL) {
                            decl->setType(type);
                            id->addDecl(decl);
                        }
                        break;
                    }
                }
            } end_for;
            break;
        }
        case ID:
        {
            Decl* decl = enclosing->addVarDecl(this);
            if (decl != NULL) {
                this->addDecl(decl);
            }
            break;
        }
        case TYPED_ID:
        {
            // TODO
            AST_Ptr id = this->child(0);
            Type_Ptr type = (Type_Ptr) this->child(1);
            Decl* decl = enclosing->addVarDecl(id);
            if (decl != NULL) {
                decl->setType(type);
                id->addDecl(decl);
            }
            break;
        }
    }
}

AST_Ptr
AST::resolveSimpleIds (const Environ* env)
{
    switch(this->oper()->syntax()) {
        case TYPE:
        {
            Decl_Vector decls;
            AST_Ptr id = this->child(0);
            gcstring name = id->as_string();
            Decl* decl = classes->find(name);
            if (decl != NULL && id->numDecls() == 0){
                id->addDecl(decl);
            } 
        }
        case ID:
        {
            Decl_Vector decls;
            gcstring name = this->as_string();
            Decl* decl = classes->find(name);
            if (decl != NULL && this->numDecls() == 0){;
                this->addDecl(decl);
                return consTree(TYPE, this, consTree(TYPE_LIST));
            } 
            env->find(name, decls);
            if (decls.size() == 0){
                //fprintf(stderr, "decl not found with \n");
            } 
            else {
                for (Decl_Vector::const_iterator i = decls.begin (); 
                     i != decls.end (); 
                     i++)
                {
                    this->addDecl(*i);
                }
            } 
            break;
        }
        case CLASS:
        {           
            AST_Ptr id = this->child(0);
            const Environ* class_env = id->getDecl()->getEnviron();
            for_each_child_var (c, this) {
                c = c->resolveSimpleIds (class_env);
            } end_for;
            break;
        }
        case DEF:
        {
            AST_Ptr id = this->child(0);
            const Environ* func_env = id->getDecl()->getEnviron();
            for_each_child_var (c, this) {
                c = c->resolveSimpleIds (func_env);
            } end_for;
            break;
        }
        case ATTRIBUTEREF:
        {
            int count = 0;
            for_each_child_var (c, this) {
                if (count == 0) {
                    c = c->resolveSimpleIds (env);
                }
                count++;
            } end_for;
            break;
        }
        default:
        {          
            for_each_child_var (c, this) {
                c = c->resolveSimpleIds (env);
            } end_for;
            break;
        }   
    }
    return this;
}

void
AST::resolveSimpleTypeIds (const Environ* env)
{
    if (this->oper()->syntax() == TYPE) {
        AST_Ptr id = this->child(0);
        Decl* decl = classes->find(id->as_string());
        if (decl != NULL) {
            this->addDecl(decl);
        }
    }
    for_each_child (c, this) {
        c->resolveSimpleTypeIds (env);
    } end_for;
}
    
AST_Ptr
AST::resolveAllocators (const Environ* env)
{
    if (this->oper()->syntax() == CALL) {
    }
    if (this->oper()->syntax() == CALL && 
        this->child(0)->oper()->syntax() == TYPE) {
        AST_Ptr init_tree = make_id("__init__", "0");
        gcstring name = this->child(0)->child(0)->as_string();
        Decl* decl = classes->find(name);
        Decl* init_decl = decl->getEnviron()->find_immediate("__init__");
        init_tree->addDecl(init_decl);
        AST_Ptr new_tree = consTree(NEW, this->child(0));
        std::vector <AST_Ptr> temp;
        temp.push_back(new_tree);
        if (this->arity() == 2){
            AST_Ptr expr_tree = this->child(1);
            for (int i = 0; i < expr_tree->arity(); i++){
                temp.push_back(expr_tree->child(i));
            }
        }
        AST_Ptr* new_args = &temp[0];
        AST_Ptr new_expr_tree = AST::make_tree(EXPR_LIST, new_args, new_args + sizeof (new_args) / sizeof(new_args[0]));
        return consTree(CALL1, init_tree, new_expr_tree);            
    }
    for_each_child_var (c, this) {
        c = c->resolveAllocators (env);
    } end_for;
    return this;
}

AST_Ptr
AST::resolveStaticSelections (const Environ* env)
{
    if (this->oper()->syntax() == ATTRIBUTEREF) {
        AST_Ptr id0 = this->child(0);
        Decl* decl = id0->getDecl();
        if (decl != NULL) {
            AST_Ptr id1 = this->child(1);
            Decl_Vector decls;
            decl->getEnviron()->find(id1->as_string(), decls);

            for (Decl_Vector::const_iterator i = decls.begin (); 
                     i != decls.end (); 
                     i++)
            {
                if ((*i)->isMethod()) {
                    id1->addDecl((*i));
                    return id1;
                }
            }
        } else {
            fprintf(stderr, "Class not found.\n");
        }
    }
    for_each_child_var (c, this) {
        c = c->resolveStaticSelections (env);
    } end_for;
    return this;
}

void
AST::freezeDecls (bool frozen)
{
    for_each_child (c, this) {
        c->freezeDecls (frozen);
    } end_for;
}

/*
(5,6, "Gary")
int    int    str 
(type (id tuple3) (typelist (type (id int)) (type (id int)) (type (id str)) )
*/

void
AST::resolveTypes (Decl* context, Unifier& subst)
{
    for_each_child_var (c, this) {
        c->resolveTypes (context, subst);
    } end_for;
    switch(this->oper()->syntax()) {
        case LIST_DISPLAY:
        {
            break;
        }
        // case INT_LITERAL:
        // {
        //     this->setType(intDecl->asType(), subst);
        //     break;
        // }
        case TUPLE:
        {
            switch(this->arity()) {
                case 0:
                {
                    this->setType(tuple0Decl->asType(), subst);
                    break;
                }
                case 1:
                {
                    Type_Ptr* types = (Type_Ptr*)malloc(sizeof(Type_Ptr));
                    types[0] = this->child(0)->getType();
                    // this->child(0);
                    this->setType(tuple1Decl->asType(1, types), subst);
                    free(types);
                    break; 
                }
                case 2:
                {
                    Type_Ptr* types = (Type_Ptr*) malloc (2 * sizeof(Type_Ptr));
                    types[0] = this->child(0)->getType();
                    types[1] = this->child(1)->getType();
                    this->setType(tuple1Decl->asType(1, types), subst);
                    free(types);
                    break;
                    // fprintf(stderr, "tuple of size 2\n");                    
                    // fprintf(stderr, "setting type \n");             
                    //fprintf(stderr, "%d \n", this->setType(tuple2Decl->asType(2, types), subst));
                    //fprintf(stderr, "type is set \n");
                    // break; 
                }
                case 3:
                {
                    Type_Ptr* types = (Type_Ptr*) malloc (3 * sizeof(Type_Ptr));
                    types[0] = this->child(0)->getType();
                    types[1] = this->child(1)->getType();
                    types[2] = this->child(2)->getType();
                    this->setType(tuple3Decl->asType(3, types), subst);
                    free(types);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case STRING_LITERAL:
        {
            break;
        }
        case NONE:
        {
            break;
        }
        case TRUE:
        {
            break;
        }
        case FALSE:
        {
            break;
        }
        case ID:
        {
            break;
        }
        case AND:
        {
            break;
        }
        case OR:
        {
            break;
        }
        case CALL:
        {
            break;
        }
        case CALL1:
        {
            break;
        }

        case ASSIGN:
        {
            break;
        }
        case FOR:
        {
            break;
        }
        case WHILE:
        {
            break;
        }
        case IF:
        {
            break;
        }
        case RETURN:
        {
            break;
        }
        case PRINT:
        {
            break;
        }
        case TYPED_ID:
        {
            break;
        }
        case ATTRIBUTEREF:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

bool
AST::errorReported ()
{
    return _erroneous;
}

void
AST::recordError ()
{
    _erroneous = true;
}

/* Definitions of methods in base class AST_Tree. */

void
AST_Tree::_print (ostream& out, int indent, ASTSet& visited)
{
    visited.insert (this);
    out << "(" << externalName () << " " << lineNumber ();
    for_each_child (c, this) {
        out << endl << setw (indent + 4) << "";
        print (c, out, indent + 4, visited);
    } end_for;
    out << ")";
    visited.erase (this);
}

const char*
AST_Tree::externalName ()
{
    static string result;

    int syntax = oper ()->syntax ();
    const char* name;
    name = yyexternal_token_name (syntax);
    if (name == NULL)
        return "?";
    if (name[0] != '"')
        return name;
    name += 1;
    while (*name == '@')
        name += 1;
    
    if (name[0] == '\0')
        return "?";

    result = string (name, strlen (name)-1);
    return result.c_str();
}

AST_Ptr
make_id (const char* text, const char* loc) 
{
    AST_Ptr result = AST::make_token (ID, strlen (text), text);
    result->set_loc (loc);
    return result;
}

AST_Ptr
consTree (int syntax)
{
    AST_Ptr args[1];
    return AST::make_tree (syntax, args, args);
}

AST_Ptr
consTree (int syntax, const AST_Ptr c0)
{
    AST_Ptr args[] = { c0 };
    return AST::make_tree (syntax,
                           args, args + sizeof (args) / sizeof(args[0]));
}

AST_Ptr
consTree (int syntax, const AST_Ptr c0, const AST_Ptr c1)
{
    AST_Ptr args[] = { c0, c1 };
    return AST::make_tree (syntax,
                           args, args + sizeof (args) / sizeof(args[0]));
}

AST_Ptr
consTree (int syntax, const AST_Ptr c0, const AST_Ptr c1,
          const AST_Ptr c2)
{
    AST_Ptr args[] = { c0, c1, c2 };
    return AST::make_tree (syntax,
                           args, args + sizeof (args) / sizeof(args[0]));
}

AST_Ptr
consTree (int syntax, const AST_Ptr c0, const AST_Ptr c1,
          const AST_Ptr c2, const AST_Ptr c3)
{
    AST_Ptr args[] = { c0, c1, c2, c3 };
    return AST::make_tree (syntax,
                           args, args + sizeof (args) / sizeof(args[0]));
}

