/* -*-C++-*- */
/* Generated from ast.hn at Sat Apr  4 16:24:16 2015 GMT. */

%code top {

#define YYPARAM Tree_Semantics< AST >
#define YYPRODUCING_TREES
#define YYERROR_FUNCTION_NAME parse_error

# define YY_PARSER_1
# include "horn-parse-lex.cc"
}

%{

    YYNAMESPACE_OPEN

%}

/* User prologue code */


#line 7 "ast.hn"


%{
    #include <string>
    #include <cstring>
    #include "apyc.h"
    #include "ast.h"

    using namespace std;

    static GCINIT _gcdummy;

    static AST_Ptr theTree;
   
    /** Return a location string (Unix format) formed from the name of
     *  the source file producing this AST and the number in NODE (an
     *  INT token). */
    static const char* make_ast_loc (AST* node);
    void parse_error (const char* loc, const char* message, ...);
%}

%debug
#line 29 "ast.hn"


%token AND "and"
%token ASSIGN "assign"
%token ATTRIBUTEREF "attributeref"
%token BINOP "binop"
%token BLOCK "block"
%token BREAK "break"
%token CALL "call"
%token CALL1 "call1"
%token CLASS "class"
%token COMPARE "compare"
%token CONTINUE "continue"
%token DEDENT
%token DEF "def"
%token DICT_DISPLAY "dict_display"
%token FALSE "False"
%token FOR "for"
%token FORMALS_LIST "formals_list"
%token FUNCTION_TYPE "function_type"
%token ID
%token IF "if"
%token IF_EXPR "if_expr"
%token INDENT 
%token INT_LITERAL "int_literal"
%token LEFT_COMPARE "left_compare"
%token LIST_DISPLAY "list_display"
%token METHOD "@method"
%token MODULE "module"
%token NATIVE "native"
%token NEXT_VALUE "next_value"
%token NONE "None"
%token NOT "not"
%token OR "or"
%token PAIR "pair"
%token PRINT "print"
%token PRINTLN "println"
%token RETURN "return"
%token SLICE "slice"
%token SLICE_ASSIGN "slice_assign"
%token STMT_LIST "stmt_list"
%token STRING_LITERAL
%token SUBSCRIPT "subscript"
%token SUBSCRIPT_ASSIGN "subscript_assign"
%token TARGET_LIST "target_list"
%token TRUE "True"
%token TUPLE "tuple"
%token TYPE "type"
%token TYPED_ID "typed_id"
%token TYPE_FORMALS_LIST "type_formals_list"
%token TYPE_LIST "type_list"
%token TYPE_VAR
%token UNOP "unop"
%token WHILE "while"

%token NEW

#line 105 "ast-parser.y"

/* Horn prologue */

%defines
%token-table

%{

#define YY_PARSER_2
#include "horn-parse-lex.cc"

%}

/* Token definitions */

%token '(' "("
%token ')' ")"
%token _TOK_0 "id"
%token _TOK_1 "string_literal"
%token _TOK_2 "type_var"
%token  TYPE_VAR_ID


/* Destroying discarded semantic values. */
%destructor { $$._destructor (); } <>

%{
static yyvar yyv_ID;
static yyvar yyv_INT_LITERAL;
static yyvar yyv_STRING_LITERAL;
static yyvar yyv_TYPE_VAR_ID;
static yyvar yyv_ast_node_type;
static yyvar yyv_expr;
static yyvar yyv_id;
static yyvar yyv_num;
static yyvar yyv_operands;
static yyvar yyv_val;

%}

%%



program : 
#line 111 "ast.hn"
 expr     { YYCTLPA($$,0,1,&$1);  yyv_expr = $1;theTree = yyv_expr.value (); } 
;




expr : 
#line 115 "ast.hn"
 "(" ast_node_type INT_LITERAL  operands ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  $1.ignore(); $5.ignore(); yyv_ast_node_type = $2; yyv_num = $3; yyv_INT_LITERAL = $3; yyv_operands = $4;yylhs = YYMAKE_TREE(yyv_ast_node_type.value (), 
                            yyv_operands.list_value ());
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); } 
 | 
#line 120 "ast.hn"
 "(" "id" INT_LITERAL id ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  yyv_INT_LITERAL = $3; yyv_id = $4;yylhs = yyv_id;
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); } 
 | 
#line 123 "ast.hn"
 "(" "int_literal" INT_LITERAL  INT_LITERAL  ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  yyv_num = $3; yyv_INT_LITERAL = $3; yyv_val = $4; yyv_INT_LITERAL = $4;yylhs = yyv_val;
                    yylhs.set_loc (make_ast_loc (yyv_num.value ())); } 
 | 
#line 126 "ast.hn"
 "(" "string_literal" INT_LITERAL STRING_LITERAL ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  yyv_INT_LITERAL = $3; yyv_STRING_LITERAL = $4;yylhs = yyv_STRING_LITERAL;
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); } 
 | 
#line 129 "ast.hn"
 "(" "type_var" INT_LITERAL TYPE_VAR_ID ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  yyv_INT_LITERAL = $3; yyv_TYPE_VAR_ID = $4;yylhs = YYMAKE_TREE (TYPE_VAR, yyv_TYPE_VAR_ID.value ());
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); } 
;



operands : 
#line 134 "ast.hn"
 __0 { YYCTLA($$,0,1,&$1);  }
;



ast_node_type : 
#line 138 "ast.hn"

      "and" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 140 "ast.hn"
 "assign" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 141 "ast.hn"
 "attributeref" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 142 "ast.hn"
 "binop" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 143 "ast.hn"
 "block" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 144 "ast.hn"
 "break" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 145 "ast.hn"
 "call" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 146 "ast.hn"
 "class" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 147 "ast.hn"
 "compare" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 148 "ast.hn"
 "continue" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 149 "ast.hn"
 "def" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 150 "ast.hn"
 "dict_display" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 151 "ast.hn"
 "False" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 152 "ast.hn"
 "for" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 153 "ast.hn"
 "formals_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 154 "ast.hn"
 "function_type" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 155 "ast.hn"
 "if" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 156 "ast.hn"
 "if_expr" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 157 "ast.hn"
 "left_compare" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 158 "ast.hn"
 "list_display" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 159 "ast.hn"
 "module" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 160 "ast.hn"
 "native" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 161 "ast.hn"
 "next_value" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 162 "ast.hn"
 "None" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 163 "ast.hn"
 "or" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 164 "ast.hn"
 "pair" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 165 "ast.hn"
 "print" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 166 "ast.hn"
 "println" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 167 "ast.hn"
 "return" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 168 "ast.hn"
 "slice" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 169 "ast.hn"
 "slice_assign" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 170 "ast.hn"
 "stmt_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 171 "ast.hn"
 "subscript" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 172 "ast.hn"
 "subscript_assign" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 173 "ast.hn"
 "target_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 174 "ast.hn"
 "True" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 175 "ast.hn"
 "tuple" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 176 "ast.hn"
 "type" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 177 "ast.hn"
 "typed_id" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 178 "ast.hn"
 "type_formals_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 179 "ast.hn"
 "type_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 180 "ast.hn"
 "unop" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 181 "ast.hn"
 "while" { YYCTLPA($$,0,1,&$1);  }
;



id : 
#line 184 "ast.hn"
   ID { YYCTLPA($$,0,1,&$1);  yyv_ID = $1; }
 | 
#line 185 "ast.hn"
 ast_node_type { YYCTLPA($$,0,1,&$1);  yyv_ast_node_type = $1; }
 | 
#line 186 "ast.hn"
 "id" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 187 "ast.hn"
 "int_literal" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 188 "ast.hn"
 "string_literal" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 189 "ast.hn"
 "type_var" { YYCTLPA($$,0,1,&$1);  }
;

 __0 : /* empty */  { YYCTLPC($$,0,0);  }
 | 
#line 134 "ast.hn"
 __0
      expr { YYCTLC($$,0,2,&$1,&$2);  yyv_expr = $2; }
;




#line 359 "ast-parser.y"

%%


#line 193 "ast.hn"


static gcstring current_python_file;
static gcstring current_ast_file;

const char*
AST::lineNumber ()
{
    if (loc () == NULL)
        return "0";
    const char* suffix = strrchr (loc (), ':');
    if (suffix == NULL)
        return "0";
    return suffix + 1;
}

void
parse_error (const char* loc, const char* message, ...)
{
    if (loc == NULL)
        error ((current_ast_file + ":?").c_str (), message);
    else {
        char *place = new char[current_ast_file.size() + 12];
        sprintf(place, "%s:%d", current_ast_file.c_str (),
                yylocation_line (loc));
        error (place, message);
    }
    fatal ("bad AST");
}

static const char*
make_ast_loc (AST* node)
{
    return GC_strdup ((current_python_file + ":" + node->as_string ()).c_str ());
}

AST_Ptr
readAst (const gcstring& ast_file_name,
         const gcstring& python_file_name)
{
    current_ast_file = ast_file_name;
    FILE* f = fopen (ast_file_name.c_str (), "r");

    if (f == NULL) {
        errorNoFile ("Could not open %s", ast_file_name.c_str ());
        return NULL;
    }
    yypush_lexer (f, ast_file_name);
    current_python_file = python_file_name;

    theTree = NULL;
    yyparse ();
    fclose (f);
    yypop_lexer ();
            
    return theTree;
}


#line 424 "ast-parser.y"

const char* 
yyexternal_token_name (int syntax)
{
    int internal_num = YYTRANSLATE (syntax);
    return yytname[internal_num];
}

#undef YY_NULL
#include "ast-lexer.cc"

YYNAMESPACE_CLOSE

template <class Type>
Type Simple_Value_Semantics<Type>::default_make_token (int syn,
						       size_t len,
						       const char* text)
{
    return YY_DEFAULT_MAKE_TOKEN(syn, len, text);
}
