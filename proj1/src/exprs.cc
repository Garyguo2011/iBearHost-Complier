/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* exprs.cc: AST subclasses related to expressions. */

/* Authors:  YOUR NAMES HERE */

// The default AST printing method defined in ast.cc suffices for
// almost all ASTs.  There are a few exceptions, shown here.
// Strictly speaking, it is not necessary to define AST subclasses for
// the different kinds of AST, but you may want to anyway just to get
// a leg up on projects 2 and 3, where you will want to override
// methods to define node-specific behaviors.  The Println_AST class
// in stmts.cc is an example of a minimal AST subclass definition that
// simply inherits print and other methods unchnaged.


#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "apyc-parser.hh"

using namespace std;

/** Make sure garbage collection is initialized. */
static GCINIT _gcdummy;

                           /*** TOKENS ***/

/** Default print for tokens. */
void
AST_Token::print (ostream& out, int indent)
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


/** Represents an integer literal. */
class Int_Token : public AST_Token {
private:

    void print (ostream& out, int indent) {
        out << "(int_literal " << lineNumber () << " " << value << ")";
    }

    /** Initialize value from the text of the lexeme, checking that
     *  the literal is in range.  [The post_make method may be
     *  overridden to provide additional processing during the
     *  construction of a node or token.] */
    Int_Token* post_make () {
        value = strtol (as_string ().c_str (), (char**) NULL, 0);
        // FIXME: Incomplete.  Does not catch certain errors.
        return this;
    }

    long value;

    TOKEN_CONSTRUCTORS(Int_Token, AST_Token);

};

TOKEN_FACTORY(Int_Token, INT_LITERAL);

/** Represents an id. */
class Id_Token : public AST_Token {
private:

    void print (ostream& out, int indent) {
        out << "(id " << lineNumber () << " " << as_string ().c_str () << ")";
    }

    void print_value (ostream& out, int indent) {
        out << as_string ().c_str ();
    }

    TOKEN_CONSTRUCTORS(Id_Token, AST_Token);

};

TOKEN_FACTORY(Id_Token, ID);

/** Represents a special id. */
class SpecialId_Token : public AST_Token {
private:

    void print (ostream& out, int indent) {
        out << "(" << as_string ().c_str () << " " << lineNumber () << ")";
    }

    TOKEN_CONSTRUCTORS(SpecialId_Token, AST_Token);

};

TOKEN_FACTORY(SpecialId_Token, SPECIALID);
  
/** Represents a string. */
class String_Token : public AST_Token {
private:
    
    /** Set literal_text from the text of this lexeme, converting
     *  escape sequences as necessary. */
    String_Token* post_make () {
        if (syntax () == RAWSTRING) {
            const char* s = as_chars ();
            int stringSize;
            literal_text.clear ();
            if ( (s[1] == '\'' && s[2] == '\'' && s[3] == '\'') || (s[1] == '\"' && s[2] == '\"' && s[3] == '\"') ) {
                stringSize = text_size() - 7;
                literal_text = gcstring (s+4, stringSize);
            } 
            else {
                stringSize = text_size() - 3;
                literal_text = gcstring (s+2, stringSize);
            }
        } else {
            int v;
            const char* s = as_chars ();
            int endOfString;
            int i;
            literal_text.clear ();
            if ( (s[0] == '\'' && s[1] == '\'' && s[2] == '\'') || (s[0] == '\"' && s[1] == '\"' && s[2] == '\"') ) {
                i = 3;
                endOfString = text_size() - 3;
            } 
            else {
                endOfString = text_size() - 1;
                i = 1;
            }
            while (i < endOfString) {
                i += 1;
                if (s[i-1] == '\\') {
                    i += 1;
                    switch (s[i-1]) {
                    default: literal_text += '\\'; v = s[i-1]; break;
                    case '\n': continue;
                    case 'a': v = '\007'; break;
                    case 'b': v = '\b'; break;
                    case 'f': v = '\f'; break;
                    case 'n': v = '\n'; break;
                    case 'r': v = '\r'; break;
                    case 't': v = '\t'; break;
                    case 'v': v = '\v'; break;
                    case '\'': v = '\''; break;
                    case '"': case '\\': v = s[i-1]; break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': 
                    { 
                        v = s[i-1] - '0';
                        for (int j = 0; j < 2; j += 1) {
                            if ('0' > s[i] || s[i] > '7')
                                break;
                            v = v*8 + (s[i] - '0');
                            i += 1;
                        }
                        break;
                    }
                    case 'x': {
                        if (i+2 > endOfString || 
                            !isxdigit (s[i]) || !isxdigit (s[i+1])) {
                            error (s, "bad hexadecimal escape sequence");
                            break;
                        }
                        sscanf (s+i, "%2x", &v);
                        i += 2;
                        break;
                    }
                    }
                } else
                    v = s[i-1];
                literal_text += (char) v;        
            }
        }
        return this;
    }

    void print (ostream& out, int indent) {
        for (size_t i = 0; i < literal_text.size (); i += 1) {
            char c = literal_text[i];
            if (c < 32 || c == '\\' || c == '"') {
                out << "\\" << oct << setw (3) << setfill('0') << (int) c
                    << setfill (' ') << dec;
            } else
                out << c;
        }
    }

    gcstring string_text () const {
        return literal_text;
    }

    void append_text(const gcstring& s) {
        literal_text += s;
    }

    TOKEN_CONSTRUCTORS(String_Token, AST_Token);
    static const String_Token raw_factory;

    gcstring literal_text;
};

TOKEN_FACTORY(String_Token, STRING);

/** A dummy token whose creation registers String_Token as the class
 *  to use for RAWSTRING tokens produced by the lexer.  (The
 *  TOKEN_FACTORY macro above registers String_Token as the class for
 *  non-raw STRING tokens as well.)
 *  */ 
const String_Token String_Token::raw_factory (RAWSTRING);


                     /*** PRIMARY EXPRESSIONS ***/

/** A string literal. In Python, a string may be denoted by a number of
 *  string and raw string tokens concatentated together.  For example:
 *       message = 'He said, "Don"' "'t do that!" 
 *  A String_Literal_AST contains a sequence of string tokens and,
 *  when printing an AST, concatenates them together. **/
class String_Literal_AST : public AST_Tree {
public:

    NODE_CONSTRUCTORS (String_Literal_AST, AST_Tree);

protected:

    void print (ostream& out, int indent) {
        out << "(string_literal " << lineNumber () << " \"";
        for_each_child (c, this) {
            c->print (out, indent);
        } end_for;
        out << "\")";
    }
};

NODE_FACTORY (String_Literal_AST, STRING_LITERAL);
