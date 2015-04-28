/* -*-C++-*- */
/* Generated from dast.hn at Tue Apr 28 02:11:16 2015 GMT. */

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


#line 7 "dast.hn"


%{
    #include <string>
    #include <cstring>
    #include "apyc.h"
    #include "dast.h"

    using namespace std;

    static GCINIT _gcdummy;

    static AST_Ptr theTree;
    static int pass;
    class yyvar;
   
    /** Return a location string (Unix format) formed from the name of
     *  the source file producing this AST and the number in NODE (an
     *  INT token). */
    static const char* make_ast_loc (AST* node);
    void parse_error (const char* loc, const char* message, ...);

    /** Set the decl decoration of NODE to the Decl with with index INDEX. */
    static void setDecl (AST_Ptr node, AST_Ptr index);
    /** Set the list of members of DECL to MEMBERS. The elements of MEMBERS
     *  are actually Decl*s, disguised as AST_Ptrs. */
    static void setMembers (Decl* decl, gcvector<AST_Ptr>* members);
    /** Set the list of type formals for DECL to FORMALS. The elements of FORMALS
     *  are actually Decl*s, disguised as AST_Ptrs. */
    static void setTypeFormals (Decl* decl, gcvector<AST_Ptr>* formals);
    /** Return the Decl with index INDEX, or NULL if there is no such Decl. */
    static Decl* getDecl (size_t index);
    /** Return the Decl with index given by the integer value of the
     *  token INDEX, or NULL if there is no such Decl. */
    static Decl* getDecl (AST_Ptr index);
    /** Return the Decl with index given by the integer value of the
     *  token in INDEX, or NULL if there is no such Decl. */
    static Decl* getDecl (yyvar& index);
    /** Return the integer value of the token K. */
    static int intValue (yyvar& index);

    /** Add DECL to the set of known Decls returnable by getDecl. */
    static void addDecl (Decl* decl);

%}

%debug
#line 54 "dast.hn"


%token AND "and"
%token ASSIGN "assign"
%token ATTRIBUTEREF "attributeref"
%token BINOP "binop"
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
%token METHOD "method"
%token MODULE "module"
%token NATIVE "native"
%token NEXT_VALUE "next_value"
%token NEW "new"
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

#line 128 "dast-parser.y"

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
%token _TOK_8 "classdecl"
%token _TOK_7 "funcdecl"
%token _TOK_0 "id"
%token _TOK_10 "index_list"
%token _TOK_6 "instancedecl"
%token _TOK_9 "moduledecl"
%token _TOK_5 "paramdecl"
%token _TOK_1 "string_literal"
%token _TOK_2 "type_var"
%token _TOK_4 "typevardecl"
%token _TOK_3 "vardecl"
%token  TYPE_VAR_ID


/* Destroying discarded semantic values. */
%destructor { $$._destructor (); } <>

%{
static yyvar yyv_ID;
static yyvar yyv_INT_LITERAL;
static yyvar yyv_STRING_LITERAL;
static yyvar yyv_TYPE_VAR_ID;
static yyvar yyv_ast_node_type;
static yyvar yyv_decl;
static yyvar yyv_decl_ref;
static yyvar yyv_decls;
static yyvar yyv_expr;
static yyvar yyv_id;
static yyvar yyv_index;
static yyvar yyv_index_list;
static yyvar yyv_members;
static yyvar yyv_num;
static yyvar yyv_operands;
static yyvar yyv_other_id;
static yyvar yyv_type;
static yyvar yyv_type_formals;
static yyvar yyv_val;

%}

%%



program : 
#line 132 "dast.hn"
 expr decls    { YYCTLPA($$,0,2,&$1,&$2);  yyv_expr = $1; yyv_decls = $2;theTree = yyv_expr.value (); } 
;




expr : 
#line 136 "dast.hn"
 "(" ast_node_type INT_LITERAL  operands ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  $1.ignore(); $5.ignore(); yyv_ast_node_type = $2; yyv_num = $3; yyv_INT_LITERAL = $3; yyv_operands = $4;yylhs = YYMAKE_TREE(yyv_ast_node_type.value (), 
                            yyv_operands.list_value ());
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); } 
 | 
#line 141 "dast.hn"
 "(" "id" INT_LITERAL id index ")"
                  { YYCTLPA($$,0,6,&$1,&$2,&$3,&$4,&$5,&$6);  yyv_INT_LITERAL = $3; yyv_id = $4; yyv_index = $5;yylhs = yyv_id;
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); 
                    if (pass == 2)
                        setDecl (yylhs.value (), yyv_index.value ()); } 
 | 
#line 147 "dast.hn"
 "(" "int_literal" INT_LITERAL  INT_LITERAL  ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  yyv_num = $3; yyv_INT_LITERAL = $3; yyv_val = $4; yyv_INT_LITERAL = $4;yylhs = yyv_val;
                    yylhs.set_loc (make_ast_loc (yyv_num.value ())); } 
 | 
#line 150 "dast.hn"
 "(" "string_literal" INT_LITERAL STRING_LITERAL ")"
                  { YYCTLPA($$,0,5,&$1,&$2,&$3,&$4,&$5);  yyv_INT_LITERAL = $3; yyv_STRING_LITERAL = $4;yylhs = yyv_STRING_LITERAL;
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); } 
 | 
#line 153 "dast.hn"
 "(" "type_var" INT_LITERAL TYPE_VAR_ID index ")"
                  { YYCTLPA($$,0,6,&$1,&$2,&$3,&$4,&$5,&$6);  yyv_INT_LITERAL = $3; yyv_TYPE_VAR_ID = $4; yyv_index = $5;yylhs = YYMAKE_TREE (TYPE_VAR, yyv_TYPE_VAR_ID.value ());
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); 
                    if (pass == 2)
                        setDecl (yylhs.value (), yyv_index.value ()); } 
;



operands : 
#line 161 "dast.hn"
 __0 { YYCTLA($$,0,1,&$1);  }
;



ast_node_type : 
#line 165 "dast.hn"

      "and" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 167 "dast.hn"
 "assign" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 168 "dast.hn"
 "attributeref" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 169 "dast.hn"
 "binop" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 170 "dast.hn"
 "break" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 171 "dast.hn"
 "call" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 172 "dast.hn"
 "call1" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 173 "dast.hn"
 "class" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 174 "dast.hn"
 "compare" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 175 "dast.hn"
 "continue" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 176 "dast.hn"
 "def" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 177 "dast.hn"
 "dict_display" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 178 "dast.hn"
 "False" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 179 "dast.hn"
 "for" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 180 "dast.hn"
 "formals_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 181 "dast.hn"
 "function_type" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 182 "dast.hn"
 "if" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 183 "dast.hn"
 "if_expr" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 184 "dast.hn"
 "left_compare" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 185 "dast.hn"
 "list_display" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 186 "dast.hn"
 "method" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 187 "dast.hn"
 "module" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 188 "dast.hn"
 "native" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 189 "dast.hn"
 "next_value" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 190 "dast.hn"
 "new" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 191 "dast.hn"
 "None" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 192 "dast.hn"
 "or" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 193 "dast.hn"
 "pair" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 194 "dast.hn"
 "print" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 195 "dast.hn"
 "println" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 196 "dast.hn"
 "return" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 197 "dast.hn"
 "slice" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 198 "dast.hn"
 "slice_assign" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 199 "dast.hn"
 "stmt_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 200 "dast.hn"
 "subscript" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 201 "dast.hn"
 "subscript_assign" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 202 "dast.hn"
 "target_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 203 "dast.hn"
 "True" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 204 "dast.hn"
 "tuple" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 205 "dast.hn"
 "type" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 206 "dast.hn"
 "typed_id" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 207 "dast.hn"
 "type_formals_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 208 "dast.hn"
 "type_list" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 209 "dast.hn"
 "unop" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 210 "dast.hn"
 "while" { YYCTLPA($$,0,1,&$1);  }
;



id : 
#line 213 "dast.hn"
   ID { YYCTLPA($$,0,1,&$1);  yyv_ID = $1; }
 | 
#line 214 "dast.hn"
 other_id
           { YYCTLPA($$,0,1,&$1);  yyv_other_id = $1;yylhs = AST::make_token (ID, yyv_other_id.value()->text_size (),
                                   yyv_other_id.value()->as_chars ()); } 
;



other_id : 
#line 219 "dast.hn"

      ast_node_type { YYCTLPA($$,0,1,&$1);  yyv_ast_node_type = $1; }
 | 
#line 221 "dast.hn"
 "id" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 222 "dast.hn"
 "int_literal" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 223 "dast.hn"
 "string_literal" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 224 "dast.hn"
 "type_var" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 225 "dast.hn"
 "vardecl" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 226 "dast.hn"
 "typevardecl" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 227 "dast.hn"
 "paramdecl" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 228 "dast.hn"
 "instancedecl" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 229 "dast.hn"
 "funcdecl" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 230 "dast.hn"
 "classdecl" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 231 "dast.hn"
 "moduledecl" { YYCTLPA($$,0,1,&$1);  }
 | 
#line 232 "dast.hn"
 "index_list" { YYCTLPA($$,0,1,&$1);  }
;




decls : /* empty */  { YYCTLPA($$,0,0);  }
 | 
#line 238 "dast.hn"
 decls decl     { YYCTLPA($$,0,2,&$1,&$2);  yyv_decls = $1; yyv_decl = $2; } 
;



decl : 
#line 241 "dast.hn"
 
      "(" "vardecl" index ID decl_ref type ")"
            { YYCTLPA($$,0,7,&$1,&$2,&$3,&$4,&$5,&$6,&$7);  yyv_index = $3; yyv_ID = $4; yyv_decl_ref = $5; yyv_type = $6;if (pass == 1) 
                  addDecl(makeVarDecl (intValue(yyv_index),
                                       yyv_ID.value ()->as_string (),
                                       getDecl (yyv_decl_ref)));
              else {
                  Decl* decl = getDecl (yyv_index);
                  decl->setType (yyv_type.value ()->asType ());
              } } 
 | 
#line 252 "dast.hn"
 "(" "typevardecl" index TYPE_VAR_ID type ")"
            { YYCTLPA($$,0,6,&$1,&$2,&$3,&$4,&$5,&$6);  yyv_index = $3; yyv_TYPE_VAR_ID = $4; yyv_type = $5;if (pass == 1) 
                  addDecl (makeTypeVarDecl (intValue(yyv_index),
                                            yyv_TYPE_VAR_ID.value ()->as_string ()));
              else {
                  Decl* decl = getDecl (yyv_index);
                  decl->setAst (yyv_type.value ());
              } } 
 | 
#line 261 "dast.hn"
 "(" "paramdecl" index ID decl_ref INT_LITERAL type ")"
            { YYCTLPA($$,0,8,&$1,&$2,&$3,&$4,&$5,&$6,&$7,&$8);  yyv_index = $3; yyv_ID = $4; yyv_decl_ref = $5; yyv_INT_LITERAL = $6; yyv_type = $7;if (pass == 1) 
                  addDecl (makeParamDecl (intValue(yyv_index),
                                          yyv_ID.value ()->as_string (),
                                          getDecl (yyv_decl_ref),
                                          yyv_INT_LITERAL.value ()->intValue ()));
              else {
                  Decl* decl = getDecl (yyv_index);
                  decl->setType (yyv_type.value ()->asType ());
              } } 
 | 
#line 272 "dast.hn"
 "(" "instancedecl" index ID decl_ref type ")"
            { YYCTLPA($$,0,7,&$1,&$2,&$3,&$4,&$5,&$6,&$7);  yyv_index = $3; yyv_ID = $4; yyv_decl_ref = $5; yyv_type = $6;if (pass == 1) 
                  addDecl (makeVarDecl (intValue(yyv_index),
                                        yyv_ID.value ()->as_string (),
                                        getDecl (yyv_decl_ref)));
              else {
                  Decl* decl = getDecl (yyv_index);
                  decl->setType (yyv_type.value ()->asType ());
              } } 
 | 
#line 282 "dast.hn"
 "(" "funcdecl" index ID decl_ref type index_list ")"
            { YYCTLPA($$,0,8,&$1,&$2,&$3,&$4,&$5,&$6,&$7,&$8);  yyv_index = $3; yyv_ID = $4; yyv_decl_ref = $5; yyv_type = $6; yyv_index_list = $7;if (pass == 1) 
                  addDecl (makeFuncDecl (intValue(yyv_index),
                                         yyv_ID.value ()->as_string (),
                                         getDecl (yyv_decl_ref)));
              else {
                  Decl* decl = getDecl (yyv_index);
                  decl->setType (yyv_type.value ()->asType ());
                  setMembers (decl, yyv_index_list.list_value ());
              } } 
 | 
#line 293 "dast.hn"
 "(" "classdecl" index ID index_list  index_list  ")"
            { YYCTLPA($$,0,7,&$1,&$2,&$3,&$4,&$5,&$6,&$7);  yyv_index = $3; yyv_ID = $4; yyv_type_formals = $5; yyv_index_list = $5; yyv_members = $6; yyv_index_list = $6;if (pass == 1) 
                  addDecl (makeClassDecl (intValue(yyv_index),
                                          yyv_ID.value ()->as_string ()));
              else {
                  Decl* decl = getDecl (yyv_index);
                  setTypeFormals (decl, yyv_type_formals.list_value ());
                  setMembers (decl, yyv_members.list_value ());
              } } 
 | 
#line 303 "dast.hn"
 "(" "moduledecl" index ID index_list ")"
            { YYCTLPA($$,0,6,&$1,&$2,&$3,&$4,&$5,&$6);  yyv_index = $3; yyv_ID = $4; yyv_index_list = $5;if (pass == 1) 
                  addDecl (makeModuleDecl (intValue(yyv_index),
                                           yyv_ID.value ()->as_string ()));
              else {
                  Decl* decl = getDecl (yyv_index);
                  setMembers (decl, yyv_index_list.list_value ());
              } } 
;



type : 
#line 314 "dast.hn"
 expr { YYCTLPA($$,0,1,&$1);  yyv_expr = $1; }
;



index : 
#line 317 "dast.hn"
 INT_LITERAL { YYCTLPA($$,0,1,&$1);  yyv_INT_LITERAL = $1; }
;



decl_ref : 
#line 320 "dast.hn"
 INT_LITERAL { YYCTLPA($$,0,1,&$1);  yyv_INT_LITERAL = $1; }
;



index_list : 
#line 323 "dast.hn"

      "(" "index_list" __1 ")" { YYCTLA($$,0,4,&$1,&$2,&$3,&$4);  $1.ignore(); $2.ignore(); $4.ignore(); }
;

 __0 : /* empty */  { YYCTLPC($$,0,0);  }
 | 
#line 161 "dast.hn"
 __0
      expr { YYCTLC($$,0,2,&$1,&$2);  yyv_expr = $2; }
;

 __1 : /* empty */  { YYCTLPC($$,2,2,&$-1,&$0);  }
 | 
#line 324 "dast.hn"
 __1 decl_ref { YYCTLC($$,2,4,&$-1,&$0,&$1,&$2);  yyv_decl_ref = $2; }
;




#line 569 "dast-parser.y"

%%


#line 328 "dast.hn"


static gcstring current_python_file;
static gcstring current_ast_file;
static gcvector<Decl*> allDecls;


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

static void
setDecl (AST_Ptr node, AST_Ptr index)
{
    node->setDecl (getDecl (index->intValue ()));
}  


static void
setMembers (Decl* decl, gcvector<AST_Ptr>* members)
{
    for (size_t i = 0; i < members->size (); i += 1) {
        decl->addMember (getDecl ((*members)[i]));
    }
}

static void
setTypeFormals (Decl* decl, gcvector<AST_Ptr>* formals)
{
    for (size_t i = 0; i < formals->size (); i += 1) {
        decl->addTypeFormal (getDecl ((*formals)[i]));
    }
}

static int
intValue (yyvar& k)
{
    return k.value ()->intValue ();
}

static Decl*
getDecl (size_t k)
{
    if (k >= allDecls.size ())
        return NULL;
    else
        return allDecls[k];
}

static Decl*
getDecl (AST_Ptr index)
{
    return getDecl (index->intValue ());
}

static Decl*
getDecl (yyvar& index)
{
    return getDecl (intValue (index));
}

static void
addDecl (Decl* decl)
{
    size_t k = decl->getIndex ();
    if (k >= allDecls.size ())
        allDecls.insert (allDecls.end (), k - allDecls.size () + 1, NULL);
    allDecls[k] = decl;
    setBuiltinDecl (decl);
}

AST_Ptr
readDast (const gcstring& dast_file_name,
         const gcstring& python_file_name)
{
    current_ast_file = dast_file_name;

    for (pass = 1; pass <= 2; pass += 1) {
        FILE* f = fopen (dast_file_name.c_str (), "r");

        if (f == NULL) {
            errorNoFile ("Could not open %s", dast_file_name.c_str ());
            return NULL;
        }
        yypush_lexer (f, dast_file_name);
        current_python_file = python_file_name;
        theTree = NULL;
        yyparse ();
        fclose (f);
        yypop_lexer ();
    }
            
    return theTree;
}

void
printDecls (ostream& out)
{
    for (size_t i = 0; i < allDecls.size (); i += 1) {
        if (allDecls[i] != NULL) {
            allDecls[i]->print (out);
            out << endl;
        }
    }
}


#line 709 "dast-parser.y"

const char* 
yyexternal_token_name (int syntax)
{
    int internal_num = YYTRANSLATE (syntax);
    return yytname[internal_num];
}

#undef YY_NULL
#include "dast-lexer.cc"

YYNAMESPACE_CLOSE

template <class Type>
Type Simple_Value_Semantics<Type>::default_make_token (int syn,
						       size_t len,
						       const char* text)
{
    return YY_DEFAULT_MAKE_TOKEN(syn, len, text);
}
