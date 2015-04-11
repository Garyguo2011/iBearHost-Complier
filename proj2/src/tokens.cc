/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* tokens.cc: Definitions related to AST_Token and its subclasses. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include <cerrno>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

/** Default print for tokens. */
void
AST_Token::_print (ostream& out, int indent, ASTSet&)
{
    out << "(<Token>)";
}

/** Default implementation. */
gcstring
AST_Token::string_text () const
{
    throw logic_error ("unimplemented operation: string_text");
}

/** Default implementation. */
void
AST_Token::append_text(const gcstring& s)
{
    throw logic_error ("unimplemented operation: append_text");
}


/** The supertype of tokens with a type. */
class Typed_Token : public AST_Token {
public:

    Type_Ptr getType () {
        if (_type == NULL)
            _type = computeType ();
        return _type;
    }

    bool setType (Type_Ptr type, Unifier& subst) {
        if (_type == NULL)
            _type = Type::makeVar ();
        return unify (_type, type, subst);
    }

protected:

    /** Computes my type, which is then cached by getType(). */
    virtual Type_Ptr computeType () {
        return Type::makeVar ();
    }

    Type_Ptr _type;

    TOKEN_BASE_CONSTRUCTORS (Typed_Token, AST_Token);

};    

/** Represents an integer literal. */
class Int_Token : public Typed_Token {
protected:

    void _print (ostream& out, int indent, ASTSet& visited) {
	out << "(int_literal " << lineNumber () << " " << value
	    << ")";
    }

    TOKEN_CONSTRUCTORS(Int_Token, Typed_Token);

    Int_Token* post_make () {
        gcstring text = as_string ();
        errno = 0;
        value = strtol (text.c_str (), (char**) NULL, 0);
        if (errno != 0 || value > (1L<<30)) {
            error (loc (), "literal value out of range: %s",
                   text.c_str ());
            value = 0;
        }
        return this;
    }

    Type_Ptr computeType () {
        return intDecl->asType ();
    }

    long value;

};

TOKEN_FACTORY(Int_Token, INT_LITERAL);

/** Represents an identifier. */
class Id_Token : public Typed_Token {

protected:
    
    void addTargetDecls(Decl* enclosing) {
        Decl* decl = enclosing->addVarDecl(this);
        if (decl != NULL) {
            addDecl(decl);
        }
    }


    void _print (ostream& out, int indent, ASTSet& visited) {
	out << "(id " << lineNumber () << " " << as_string ();
        if (getDecl () != NULL)
            out << " " << getDecl ()->getIndex ();
        out << ")";
    }


    AST_Ptr resolveSimpleIds (const Environ* env)
    {
        Decl_Vector decls;
        gcstring name = as_string();
        Decl* decl = classes->find(name);
        if (decl != NULL && numDecls() == 0){
            addDecl(decl);
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
                addDecl(*i);
            }
        }
        return this;
    }

    TOKEN_CONSTRUCTORS (Id_Token, Typed_Token);

    int numDecls () {
        return _me.size ();
    }

    Decl* getDecl (int k = 0) {
        if (k >= (int) _me.size ())
            return NULL;
        else
            return _me[k];
    }

    void addDecl (Decl* decl) {
        _me.push_back (decl);
    }

    void removeDecl (int k) {
        assert (k >= 0 && k < (int) _me.size ());
        _me.erase (_me.begin () + k);
    }

    Type_Ptr getType()
    {
        if (_type == NULL){
            if (getDecl() == NULL)
                error(loc(), "id not declared in the scope");
            else
                _type = getDecl()->getType();
        }
            
        return _type;
    }

    void resolveTypes (Decl* context, Unifier& subst)
    {

    }

private:

    Decl_Vector _me;

};

TOKEN_FACTORY(Id_Token, ID);

/** Represents a string. */
class String_Token : public Typed_Token {
private:
    
    String_Token* post_make () {
        int v;
        const char* s = as_chars ();
        size_t i;
        i = 1;
        literal_text.clear ();
        while (i < text_size () - 1) {
            i += 1;
            if (s[i-1] == '\\') {
                v = 0;
                for (int j = 0; j < 3; j += 1) {
                    v = v*8 + (s[i] - '0');
                    i += 1;
                }
            } else {
                v = s[i-1];
            }
            literal_text += (char) v;
        }
        return this;
    }

    void _print (ostream& out, int indent, ASTSet& visited) {
        out << "(string_literal " << lineNumber () << " \"";
        for (size_t i = 0; i < literal_text.size (); i += 1) {
            char c = literal_text[i];
            if (c < 32 || c == '\\' || c == '"') {
                out << "\\" << oct << setw (3) << setfill('0') << (int) c
                    << setfill (' ') << dec;
            } else
                out << c;
        }
        out << "\")";
    }

    gcstring string_text () const {
        return literal_text;
    }

    void append_text(const gcstring& s) {
        literal_text += s;
    }

    Type_Ptr computeType () {
        return strDecl->asType ();
    }
        
    TOKEN_CONSTRUCTORS(String_Token, Typed_Token);
    static const String_Token raw_factory;

    gcstring literal_text;
};

TOKEN_FACTORY(String_Token, STRING_LITERAL);
