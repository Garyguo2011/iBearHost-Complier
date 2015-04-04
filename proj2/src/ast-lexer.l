/* Generated from ast.hn at Sat Apr  4 16:24:16 2015 GMT. */

%option 8bit nodefault noinput nounput noyywrap

%{ 
#define YY_LEXER_1
#include "horn-parse-lex.cc"
%}

%option outfile="ast-lexer.cc"

%x YYPREFERRED

_EOF  "\377"
_OCT	[0-7]


%%

@method	{ { YY_LEXLHS(METHOD); YYLEXRET; } } 
False	{ { YY_LEXLHS(FALSE); YYLEXRET; } } 
None	{ { YY_LEXLHS(NONE); YYLEXRET; } } 
True	{ { YY_LEXLHS(TRUE); YYLEXRET; } } 
and	{ { YY_LEXLHS(AND); YYLEXRET; } } 
assign	{ { YY_LEXLHS(ASSIGN); YYLEXRET; } } 
attributeref	{ { YY_LEXLHS(ATTRIBUTEREF); YYLEXRET; } } 
binop	{ { YY_LEXLHS(BINOP); YYLEXRET; } } 
block	{ { YY_LEXLHS(BLOCK); YYLEXRET; } } 
break	{ { YY_LEXLHS(BREAK); YYLEXRET; } } 
call	{ { YY_LEXLHS(CALL); YYLEXRET; } } 
call1	{ { YY_LEXLHS(CALL1); YYLEXRET; } } 
class	{ { YY_LEXLHS(CLASS); YYLEXRET; } } 
compare	{ { YY_LEXLHS(COMPARE); YYLEXRET; } } 
continue	{ { YY_LEXLHS(CONTINUE); YYLEXRET; } } 
def	{ { YY_LEXLHS(DEF); YYLEXRET; } } 
dict_display	{ { YY_LEXLHS(DICT_DISPLAY); YYLEXRET; } } 
for	{ { YY_LEXLHS(FOR); YYLEXRET; } } 
formals_list	{ { YY_LEXLHS(FORMALS_LIST); YYLEXRET; } } 
function_type	{ { YY_LEXLHS(FUNCTION_TYPE); YYLEXRET; } } 
id	{ { YY_LEXLHS(_TOK_0); YYLEXRET; } } 
if	{ { YY_LEXLHS(IF); YYLEXRET; } } 
if_expr	{ { YY_LEXLHS(IF_EXPR); YYLEXRET; } } 
int_literal	{ { YY_LEXLHS(INT_LITERAL); YYLEXRET; } } 
left_compare	{ { YY_LEXLHS(LEFT_COMPARE); YYLEXRET; } } 
list_display	{ { YY_LEXLHS(LIST_DISPLAY); YYLEXRET; } } 
module	{ { YY_LEXLHS(MODULE); YYLEXRET; } } 
native	{ { YY_LEXLHS(NATIVE); YYLEXRET; } } 
next_value	{ { YY_LEXLHS(NEXT_VALUE); YYLEXRET; } } 
not	{ { YY_LEXLHS(NOT); YYLEXRET; } } 
or	{ { YY_LEXLHS(OR); YYLEXRET; } } 
pair	{ { YY_LEXLHS(PAIR); YYLEXRET; } } 
print	{ { YY_LEXLHS(PRINT); YYLEXRET; } } 
println	{ { YY_LEXLHS(PRINTLN); YYLEXRET; } } 
return	{ { YY_LEXLHS(RETURN); YYLEXRET; } } 
slice	{ { YY_LEXLHS(SLICE); YYLEXRET; } } 
slice_assign	{ { YY_LEXLHS(SLICE_ASSIGN); YYLEXRET; } } 
stmt_list	{ { YY_LEXLHS(STMT_LIST); YYLEXRET; } } 
string_literal	{ { YY_LEXLHS(_TOK_1); YYLEXRET; } } 
subscript	{ { YY_LEXLHS(SUBSCRIPT); YYLEXRET; } } 
subscript_assign	{ { YY_LEXLHS(SUBSCRIPT_ASSIGN); YYLEXRET; } } 
target_list	{ { YY_LEXLHS(TARGET_LIST); YYLEXRET; } } 
tuple	{ { YY_LEXLHS(TUPLE); YYLEXRET; } } 
type	{ { YY_LEXLHS(TYPE); YYLEXRET; } } 
type_formals_list	{ { YY_LEXLHS(TYPE_FORMALS_LIST); YYLEXRET; } } 
type_list	{ { YY_LEXLHS(TYPE_LIST); YYLEXRET; } } 
type_var	{ { YY_LEXLHS(_TOK_2); YYLEXRET; } } 
typed_id	{ { YY_LEXLHS(TYPED_ID); YYLEXRET; } } 
unop	{ { YY_LEXLHS(UNOP); YYLEXRET; } } 
while	{ { YY_LEXLHS(WHILE); YYLEXRET; } } 
[(-)]	{ { YYSIMPLELEXRET; } } 
([A-Za-z]|_)([0-9A-Za-z]|_)*	{ { YY_LEXLHS(ID); YYLEXRET; } } 
\$#?([0-9A-Za-z]|_)*	{ { YY_LEXLHS(TYPE_VAR_ID); YYLEXRET; } } 
[0-9]+	{ { YY_LEXLHS(INT_LITERAL); YYLEXRET; } } 
["]([\001-!#-[\]-\376]|[\\]{_OCT}{_OCT}{_OCT})*["]	{ { YY_LEXLHS(STRING_LITERAL); YYLEXRET; } } 
[\011-\012\015 ]	{ { YY_LEXLHS;  YYLEXRET; } } 


<YYPREFERRED>.|\n  { yyless(0); return -1; }
.|\n               { if (yytext[0] == YYEOF_CHAR) {
                         yyless (0);     
                         return YYEOF;
                     }
                     return yytext[0]; }

%%

#define YY_LEXER_2
#include "horn-parse-lex.cc"
