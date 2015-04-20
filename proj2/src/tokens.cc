/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* tokens.cc: Definitions related to AST_Token and its subclasses. */

/* Authors:  YOUR NAMES HERE */

#include <cctype>
#include <iostream>
#include <cerrno>
#include "apyc.h"
#include "ast.h"
#include "ast-parser.hh"

using namespace std;

static GCINIT _gcdummy;

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

    TOKEN_BASE_CONSTRUCTORS_INIT (Typed_Token, AST_Token, _type (NULL));

};    

/** Represents an integer literal. */
class Int_Token : public Typed_Token {
protected:

    void printOther (ostream& out, int indent, ASTSet& visited) {
	out << " " << value;
    }

    TOKEN_CONSTRUCTORS(Int_Token, Typed_Token);

    Int_Token* post_make () {
        gcstring text = as_string ();
        errno = 0;
        value = strtol (text.c_str (), (char**) NULL, 0);
        return this;
    }

    Type_Ptr computeType () {
        return intDecl->asType ();
    }

    int intValue () {
        return value;
    }

    long value;

};

TOKEN_FACTORY(Int_Token, INT_LITERAL);

/** Represents an identifier. */
class Id_Token : public Typed_Token {
protected:

    void printOther (ostream& out, int indent, ASTSet& visited) {
        out << " " << as_string ();
        if (getDecl () != NULL) 
            out << " " << getDecl ()->getIndex ();
    }

    TOKEN_CONSTRUCTORS (Id_Token, Typed_Token);

    AST_Ptr getId () {
        return this;
    }

    int numDecls () {
        return _me.size ();
    }

    Decl* getDecl (int k = 0) {
        if (k >= (int) _me.size ())
            return NULL;
        else
            return _me[k];
    }

    bool isType () {
        Decl* me = getDecl ();
        return (me != NULL && me->isType ());
    }

    void addDecl (Decl* decl) {
        _me.push_back (decl);
    }

    void removeDecl (int k) {
        assert (k >= 0 && k < (int) _me.size ());
        _me.erase (_me.begin () + k);
    }

    void addTargetDecls (Decl* enclosing) {
        gcstring name = as_string ();
        Decl* old = enclosing->getEnviron ()->find_immediate (name);
        if (old == NULL) {
            addDecl (enclosing->addVarDecl(this));
        } else if (! old->assignable ()) {
            error (this, "attempt to assign to non-assignable object: %s",
                   name.c_str ());
            addDecl (old);
        } else {
            addDecl (old);
        }
    }   

    AST_Ptr resolveSimpleIds (const Environ* env) {
        gcstring name = as_string ();
        if (getDecl () != NULL)
            return this;
        Decl_Vector defns;
        env->find (name, defns);
        if (defns.empty ()) {
            error (this, "undefined identifier: %s", name.c_str ());
            addDecl (makeUnknownDecl (name, false));
            return this;
        }
        if (defns.size () == 1 && defns[0]->isType ()) {
            addDecl (defns[0]);
            return consTree (TYPE, this);
        }
        for (size_t i = 0; i < defns.size (); i += 1)
            addDecl (defns[i]);
        return this;
    }

    void getOverloadings (Resolver& resolver) {
        resolver.addId (this);
    }            

    void resolveTypes (Decl* context, Unifier& subst, Resolver& resolver) {
        if (_type == NULL) {
            if (numDecls () == 1)
                _type = getDecl (0)->getType ();
            else
                _type = Type::makeVar ();
        }
        if (numDecls () > 0) {
            Type_Ptr type = resolver[this]->getType ();
            if (type != NULL && ! unify(type, _type, subst))
                error (this, "Inconsistent type for %s", as_string ().c_str ());
        }
    }

    void resolveSelectedType (Unifier& subst, Resolver& resolver) {
        if (_type == NULL) {
            if (numDecls () == 1)
                _type = getDecl (0)->getSelectedType ();
            else
                _type = Type::makeVar ();
        }
        if (numDecls () > 0) {
            Decl* me = resolver[this];
            if (! unify(me->getSelectedType (), _type, subst))
                error (this, "Inconsistent type for %s", as_string ().c_str ());
        }
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

    void printOther (ostream& out, int indent, ASTSet& visited) {
        out << " " << " \"";
        for (size_t i = 0; i < literal_text.size (); i += 1) {
            char c = literal_text[i];
            if (c < 32 || c == '\\' || c == '"') {
                out << "\\" << oct << setw (3) << setfill('0') << (int) c
                    << setfill (' ') << dec;
            } else
                out << c;
        }
        out << "\"";
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

