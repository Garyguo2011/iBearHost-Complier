/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* tokens.cc: Definitions related to AST_Token and its subclasses. */

/* Authors:  YOUR NAMES HERE */

#include <cctype>
#include <iostream>
#include <cerrno>
#include "apyc.h"
#include "dast.h"
#include "dast-parser.hh"


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

/** The supertype of tokens with a type. */
class Typed_Token : public AST_Token {
public:

    Type_Ptr getType () {
        return _type;
    }

    void setType (Type_Ptr type) {
        _type = type;
    }

protected:

    Type_Ptr _type;

    TOKEN_BASE_CONSTRUCTORS_INIT (Typed_Token, AST_Token, _type (NULL));

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
        return this;
    }

    Type_Ptr getType () {
        if (Typed_Token::getType () == NULL)
            setType(intDecl->asType ());
        return Typed_Token::getType ();
    }

    long intValue () {
        return value;
    }

    long value;

    void codeGen ()
    {
        const int temp = this->intValue();
        cout << "__cons_int__ ("
             << temp
             << ")";
    }

};

TOKEN_FACTORY(Int_Token, INT_LITERAL);

/** Represents an identifier. */
class Id_Token : public Typed_Token {
protected:

    void _print (ostream& out, int indent, ASTSet& visited) {
	out << "(id " << lineNumber () << " " << as_string ();
        if (getDecl () != NULL)
            out << " " << getDecl ()->getIndex ();
        out << ")";
    }

    TOKEN_CONSTRUCTORS (Id_Token, Typed_Token);

    AST_Ptr getId () {
        return this;
    }

    Decl* getDecl () {
        return _me;
    }

    void setDecl (Decl* decl) {
        _me = decl;
    }

    bool isType () {
        Decl* me = getDecl ();
        return (me != NULL && me->isType ());
    }

    void codeGen() {
        const char* temp = as_string().c_str();
        // if (((std::string) temp).compare("int") != 0 && ((std::string) temp).compare("bool") != 0) {
        //     if (((std::string) temp).compare("str") == 0) {
        //         temp = "char*";
        //     } else {
        //         temp = "void";
        //     }
        // }
        // if (((std::string) temp).compare("str") == 0) {
        //     temp = "PyStr*";
        // }
        // else if (((std::string) temp).compare("int") == 0) {
        //     temp = "PyInt*";
        // }
        // else if (((std::string) temp).compare("bool") == 0) {
        //     temp = "PyBool*";
        // }
        // else if (((std::string) temp).compare("str") == 0) {
        //     temp = "PyStr*";
        // }
        // else if (((std::string) temp).compare("range") == 0) {
        //     temp = "PyRange*";
        // }
        // else if (((std::string) temp).compare("list") == 0) {
        //     temp = "PyList*";
        // }
        // else if (((std::string) temp).compare("dict") == 0) {
        //     temp = "PyDict*";
        // }
        // else if (((std::string) temp).compare("tuple0") == 0) {
        //     temp = "PyTuple0*";
        // }
        // else if (((std::string) temp).compare("tuple1") == 0) {
        //     temp = "PyTuple1*";
        // }
        // else if (((std::string) temp).compare("tuple2") == 0) {
        //     temp = "PyTuple2*";
        // }
        // else if (((std::string) temp).compare("tuple3") == 0) {
        //     temp = "PyTuple3*";
        // }
        // fprintf(stderr, "ID: %s\n", temp);
        cout << temp << " ";
    }

private:

    Decl* _me;

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

    Type_Ptr getType () {
        if (Typed_Token::getType () == NULL)
            setType (strDecl->asType ());
        return Typed_Token::getType ();
    }
        
    TOKEN_CONSTRUCTORS(String_Token, Typed_Token);
    static const String_Token raw_factory;

    gcstring literal_text;

    void codeGen ()
    {
        cout << "__cons_str__ (\""
             << string_text() << "\")";
    }
};

TOKEN_FACTORY(String_Token, STRING_LITERAL);

