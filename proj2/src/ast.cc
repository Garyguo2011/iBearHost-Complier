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
    return _decls[k];
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
    throw logic_error ("node does not represent something with a type");
}

bool
AST::setType (Type_Ptr type, Unifier& subst)
{
    throw logic_error ("node does not represent something with a type");
}

/** Default does nothing. */
AST_Ptr
AST::doOuterSemantics ()
{
    AST_Ptr dast;
    this->collectDecls(fileDecl);
    dast = this->resolveSimpleIds(fileDecl->getEnviron());
    return dast;
    //return this;
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
        case ID:
        {
            // find ID in envhyththrth

            gcstring name = this->as_string();
            if (classes->find(name) != NULL){
                return consTree(TYPE, this);
            } 
            Decl* decl = env->find(name);
            if (decl == NULL){
                fprintf(stderr, "decl not found \n");
            } else{
                this->addDecl(decl);
            } break;
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
        case CALL:
        {
            // call different function

            if (this->child(0)->oper()->syntax() == TYPE){
                return this->resolveAllocators(classes);
            } else{
                // for_each_child_var (c, this) {
                //     c = c->resolveSimpleIds (env);
                // } end_for;
                gcstring name = this->as_string();
                Decl* decl = env->find(name);
                if (decl == NULL){
                    fprintf(stderr, "function decl not found \n" );
                } else{
                    this->child(0)->addDecl(decl);
                }

            }
            break;
        }
        case ATTRIBUTEREF:
        {
            // call different function
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
    for_each_child (c, this) {
        c->resolveSimpleTypeIds (env);
    } end_for;
}
    
AST_Ptr
AST::resolveAllocators (const Environ* env)
{
    // for_each_child_var (c, this) {
    //     c = c->resolveAllocators (env);
    // } end_for;
    gcstring name = this->as_string();
    Decl* decl = env->find(name);
    if (decl == NULL){
        return this;    
    } else {

    }
    
}

AST_Ptr
AST::resolveStaticSelections (const Environ* env)
{
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

void
AST::resolveTypes (Decl* context, Unifier& subst)
{
    for_each_child_var (c, this) {
        c->resolveTypes (context, subst);
    } end_for;
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

