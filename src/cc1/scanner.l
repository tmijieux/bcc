%{
/* Jutta Degener, 1995  */
#include <stdio.h>


#include "function.h"
#include "type/type.h"
#include "symbol/symbol.h"
#include "expression/expression.h"
#include "statement/statement.h"
#include "constant/constant.h"

#include "util/error.h"
#include "util/string2.h"

#include "errorc.h"
#include "scanner.h"
#include "parser.tab.h"


#define BUFSIZE 1024

static void count(void);
static void comment(void);
static int check_type(void);
static void line_marker(void);

char *yyfilename = "<stdin>";

void newline();

%}
/*
%option reentrant
%option bison-bridge
%option bison-locations
*/
%option noyywrap
%option yylineno

D                       [0-9]
L                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
FS                      (f|F|l|L)
IS                      (u|U|l|L)*


%%
"/*"                    { comment(); }
"//".*                  { count(); }
^"#"    	        { line_marker(); }

"auto"                  { count(); return(TOKEN_AUTO); }
"break"                 { count(); return(TOKEN_BREAK); }
"case"                  { count(); return(TOKEN_CASE); }
"char"                  { count(); return(TOKEN_CHAR); }
"const"                 { count(); return(TOKEN_CONST); }
"continue"              { count(); return(TOKEN_CONTINUE); }
"default"               { count(); return(TOKEN_DEFAULT); }
"do"                    { count(); return(TOKEN_DO); }
"double"                { count(); return(TOKEN_DOUBLE); }
"else"                  { count(); return(TOKEN_ELSE); }
"enum"                  { count(); return(TOKEN_ENUM); }
"extern"                { count(); return(TOKEN_EXTERN); }
"float"                 { count(); return(TOKEN_FLOAT); }
"for"                   { count(); return(TOKEN_FOR); }
"goto"                  { count(); return(TOKEN_GOTO); }
"if"                    { count(); return(TOKEN_IF); }
"int"                   { count(); return(TOKEN_INT); }
"long"                  { count(); return(TOKEN_LONG); }
"register"              { count(); return(TOKEN_REGISTER); }
"return"                { count(); return(TOKEN_RETURN); }
"short"                 { count(); return(TOKEN_SHORT); }
"signed"                { count(); return(TOKEN_SIGNED); }
"sizeof"                { count(); return(TOKEN_SIZEOF); }
"static"                { count(); return(TOKEN_STATIC); }
"struct"                { count(); return(TOKEN_STRUCT); }
"switch"                { count(); return(TOKEN_SWITCH); }
"typedef"               { count(); return(TOKEN_TYPEDEF); }
"union"                 { count(); return(TOKEN_UNION); }
"unsigned"              { count(); return(TOKEN_UNSIGNED); }
"void"                  { count(); return(TOKEN_VOID); }
"volatile"              { count(); return(TOKEN_VOLATILE); }
"while"                 { count(); return(TOKEN_WHILE); }

{L}({L}|{D})*           { count(); return(check_type()); } //identifier of type

0[xX]{H}+{IS}?  {
    // hexadecimal integer
    count();
    yylval.constant = constant_hex_integer(yytext);
    return(TOKEN_CONSTANT);

}

0{D}+{IS}?  {
    // octal integer
    count();
    yylval.constant = constant_oct_integer(yytext);
    return(TOKEN_CONSTANT);
   }
{D}+{IS}?               {
    // decimal integer
    count();
    yylval.constant = constant_dec_integer(yytext);
    return(TOKEN_CONSTANT);
   }
L?'(\\.|[^\\'])+'     {
     /*char?*/
    count();
    yylval.constant = constant_hex_integer(yytext);
    return(TOKEN_CONSTANT);
}

{D}+{E}{FS}?            {
    // floating point with exponent, no dot
    count();
    yylval.constant = constant_floating_point(yytext);
    return(TOKEN_CONSTANT);

}
{D}*"."{D}+({E})?{FS}?  {
    // floating point with dot
    count();
    yylval.constant = constant_floating_point(yytext);
    return(TOKEN_CONSTANT);
}
{D}+"."{D}*({E})?{FS}?  {
    // floating point with dot and first part
    count();
    yylval.constant = constant_floating_point(yytext);
    return(TOKEN_CONSTANT);
}

L?\"(\\.|[^\\"])*\"   {
    // string literal
    count();
    yylval.constant = constant_string_literal(yytext);
    return(TOKEN_CONSTANT);
}

"..."                   { count(); return(TOKEN_ELLIPSIS); }
">>="                   { count(); return(TOKEN_RIGHT_ASSIGN); }
"<<="                   { count(); return(TOKEN_LEFT_ASSIGN); }
"+="                    { count(); return(TOKEN_ADD_ASSIGN); }
"-="                    { count(); return(TOKEN_SUB_ASSIGN); }
"*="                    { count(); return(TOKEN_MUL_ASSIGN); }
"/="                    { count(); return(TOKEN_DIV_ASSIGN); }
"%="                    { count(); return(TOKEN_MOD_ASSIGN); }
"&="                    { count(); return(TOKEN_AND_ASSIGN); }
"^="                    { count(); return(TOKEN_XOR_ASSIGN); }
"|="                    { count(); return(TOKEN_OR_ASSIGN); }
">>"                    { count(); return(TOKEN_RIGHT_OP); }
"<<"                    { count(); return(TOKEN_LEFT_OP); }
"++"                    { count(); return(TOKEN_INC_OP); }
"--"                    { count(); return(TOKEN_DEC_OP); }
"->"                    { count(); return(TOKEN_PTR_OP); }
"&&"                    { count(); return(TOKEN_AND_OP); }
"||"                    { count(); return(TOKEN_OR_OP); }
"<="                    { count(); return(TOKEN_LE_OP); }
">="                    { count(); return(TOKEN_GE_OP); }
"=="                    { count(); return(TOKEN_EQ_OP); }
"!="                    { count(); return(TOKEN_NE_OP); }
";"                     { count(); return(';'); }
("{"|"<%")              { count(); return('{'); }
("}"|"%>")              { count(); return('}'); }
","                     { count(); return(','); }
":"                     { count(); return(':'); }
"="                     { count(); return('='); }
"("                     { count(); return('('); }
")"                     { count(); return(')'); }
("["|"<:")              { count(); return('['); }
("]"|":>")              { count(); return(']'); }
"."                     { count(); return('.'); }
"&"                     { count(); return('&'); }
"!"                     { count(); return('!'); }
"~"                     { count(); return('~'); }
"-"                     { count(); return('-'); }
"+"                     { count(); return('+'); }
"*"                     { count(); return('*'); }
"/"                     { count(); return('/'); }
"%"                     { count(); return('%'); }
"<"                     { count(); return('<'); }
">"                     { count(); return('>'); }
"^"                     { count(); return('^'); }
"|"                     { count(); return('|'); }
"?"                     { count(); return('?'); }

[ \t\v\f]             { count(); }
[\n]                  { count(); newline(); }
.                       { /* ignore bad characters */ }

%%

static void comment(void)
{
    char c, c1;
  loop:
    while ((c = input()) != '*' && c != 0)
        /*putchar(c)*/;

    if ((c1 = input()) != '/' && c != 0) {
        unput(c1);
        goto loop;
    }

    if (c != 0)
    {
        /*putchar(c1)*/;
    }
}


int yycolno = 0;

unsigned int old_yytext_index = 0;
const char *old_yytext[YYOLDTEXT_SIZE] = {
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
};

static void count(void)
{
    int i;

    for (i = 0; yytext[i] != '\0'; i++)
        if (yytext[i] == '\n')
            yycolno = 0;
        else if (yytext[i] == '\t')
            yycolno += 8 - (yycolno % 8);
        else
            yycolno++;

    old_yytext_index = (old_yytext_index+1)%YYOLDTEXT_SIZE;
    old_yytext[old_yytext_index] = strstrip(yytext);
//    ECHO;
}

static int check_type(void)
{
    struct symbol *may_be_typedef = NULL;

    if (st_search(yytext, &may_be_typedef) == 1) {
        /* debug("found symbol %s : may be typename", yytext); */
        if (symbol_is_typename(may_be_typedef)) {
            /* debug("success!! symbol %s is typename", yytext); */
            yylval.type = symbol_get_type(may_be_typedef);
            return TOKEN_TYPE_NAME;
        }
    }
    yylval.string = strdup(yytext);
    return(TOKEN_IDENTIFIER);
}

static void line_marker(void)
{
    char line[BUFSIZE];
    char c;
    char *filename = NULL;

    int i = 0;
    while ((c = input()) != '\n' && c != 0 && i < BUFSIZE) {
        line[i++] = c;
    }
    line[i] = 0;

    sscanf(line, "%d \"%ms", &yylineno, &filename);
    if (NULL != filename) {
        yyfilename = strstrip2(filename);
        free(filename);
    } else {
        fatal_error("cannot compile file with unprocessed "
                    "preprocessor directives\n");
    }
    //debug("line_marker %d, %s\n", lineno, yyfilename);
}

void newline()
{
//    old_yytext_index = 0;
}
