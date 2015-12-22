%{
/* grammar by Jutta Degener, 1995 */

#include <stdio.h>
#include <stdlib.h>
#include <list.h>

#include "util/alloc.h"

#include "symbol_table.h"
#include "error.h"

#include "symbol.h"
#include "type.h"
#include "constant.h"
#include "expression.h"
#include "statement.h"

#include "function.h"
#include "module.h"
#include "program.h"
#include "codegen.h"
#include "scanner.h"

%}
%token <string> TOKEN_IDENTIFIER
%token <constant> TOKEN_CONSTANT
%token <string> TOKEN_STRING_LITERAL
                        
%token TOKEN_PTR_OP TOKEN_INC_OP TOKEN_DEC_OP TOKEN_LEFT_OP TOKEN_RIGHT_OP
%token TOKEN_LE_OP TOKEN_GE_OP TOKEN_EQ_OP TOKEN_NE_OP
                        
%token TOKEN_AND_OP TOKEN_OR_OP TOKEN_MUL_ASSIGN TOKEN_DIV_ASSIGN
%token TOKEN_MOD_ASSIGN TOKEN_ADD_ASSIGN TOKEN_SUB_ASSIGN TOKEN_LEFT_ASSIGN
%token TOKEN_RIGHT_ASSIGN TOKEN_AND_ASSIGN TOKEN_XOR_ASSIGN TOKEN_OR_ASSIGN
%token TOKEN_TYPE_NAME

%token TOKEN_ELLIPSIS
                        
 // keywords
%token TOKEN_TYPEDEF TOKEN_EXTERN TOKEN_STATIC TOKEN_AUTO TOKEN_REGISTER
%token TOKEN_CHAR TOKEN_SHORT TOKEN_INT TOKEN_LONG TOKEN_SIGNED TOKEN_UNSIGNED
%token TOKEN_FLOAT TOKEN_DOUBLE TOKEN_CONST TOKEN_VOLATILE TOKEN_VOID
%token TOKEN_STRUCT TOKEN_UNION TOKEN_ENUM TOKEN_CASE TOKEN_DEFAULT TOKEN_IF
%token TOKEN_ELSE TOKEN_SWITCH TOKEN_WHILE TOKEN_DO TOKEN_FOR TOKEN_GOTO
%token TOKEN_CONTINUE TOKEN_BREAK TOKEN_RETURN TOKEN_SIZEOF

%type <expression> primary_expression
%type <expression> postfix_expression
%type <expression> unary_expression
%type <expression> cast_expression
%type <expression> multiplicative_expression
%type <expression> additive_expression
%type <expression> shift_expression
%type <expression> relational_expression
%type <expression> equality_expression
%type <expression> and_expression
%type <expression> exclusive_or_expression
%type <expression> inclusive_or_expression
%type <expression> logical_and_expression
%type <expression> logical_or_expression
%type <expression> conditional_expression
%type <expression> assignment_expression
%type <expression> expression
%type <expression> constant_expression
                        
%type <list> argument_expression_list
%type <list> init_declarator_list
%type <list> struct_declaration_list
%type <list> struct_declarator_list
%type <list> enumerator_list
%type <list> parameter_type_list
%type <list> parameter_list
%type <list> identifier_list
%type <list> initializer_list
%type <list> declaration_list
%type <list> statement_list
%type <list> specifier_qualifier_list

%type <list> declaration_specifiers

%type <statement> labeled_statement
%type <statement> compound_statement
%type <statement> expression_statement
%type <statement> selection_statement
%type <statement> iteration_statement
%type <statement> jump_statement
%type <statement> statement

%type <specifier> storage_class_specifier
%type <specifier> type_specifier
%type <specifier> type_qualifier

%type <initializer> initializer

%type <type> type_name
%type <symbol> declaration
%type <symbol> declarator
%type <symbol> direct_declarator
%type <symbol> struct_declarator

%type <character> unary_operator
%type <character> assignment_operator

%start translation_unit
%union {
    char *string;
    char character;
    int integer;
    float fp;
    double doublefp;
    enum type_type type_type;
    struct constant *constant;
    struct symbol *symbol;
    struct function *function;
    struct statement *statement;
    const struct type *type;
    const struct expression *expression;
    struct specifier *specifier;
    struct initializer *initializer;
    struct list *list;
};
%%

primary_expression
: TOKEN_IDENTIFIER { $$ = expr_symbol(stable_get($1)); }
| TOKEN_CONSTANT { $$ = expr_constant($1); }
//| TOKEN_STRING_LITERAL { $$ = expr_constant(string_to_constant($1)); }
| '(' expression ')' { $$ = $2; }
;

postfix_expression
: primary_expression { $$ = $1; }
| postfix_expression '[' expression ']' { $$ = expr_array($1, $3); }
| postfix_expression '(' ')' { $$ = expr_funcall($1, list_new(0)); }
| postfix_expression '(' argument_expression_list ')'
{ $$ = expr_funcall($1, $3); }

| postfix_expression '.' TOKEN_IDENTIFIER
{ $$ = expr_struct_access($1, $3); }

| postfix_expression TOKEN_PTR_OP TOKEN_IDENTIFIER
 { $$ = expr_struct_deref($1, $3); }

| postfix_expression TOKEN_INC_OP  { $$ = expr_post_inc($1); }
| postfix_expression TOKEN_DEC_OP  { $$ = expr_post_dec($1); }
;

argument_expression_list
: assignment_expression { $$ = list_new(LI_ELEM, $1, NULL); }
| argument_expression_list ',' assignment_expression { list_append($$ = $1, $3); }
;

unary_expression
: postfix_expression { $$ = $1; }
| TOKEN_INC_OP unary_expression { $$ = expr_pre_inc($2); }
| TOKEN_DEC_OP unary_expression { $$ = expr_pre_dec($2); }
| unary_operator cast_expression { $$ = expr_unary($1, $2); }
| TOKEN_SIZEOF unary_expression { $$ = expr_sizeof_expr($2); }
| TOKEN_SIZEOF '(' type_name ')'  { $$ = expr_sizeof_typename($3); }
;

unary_operator
: '&' { $$ = '&' }
| '*' { $$ = '*' }
| '+' { $$ = '+' }
| '-' { $$ = '-' }
| '~' { $$ = '~' }
| '!' { $$ = '!' }
;

cast_expression
: unary_expression { $$ = $1; }
| '(' type_name ')' cast_expression { $$ = expr_cast($4, $2); }
;

multiplicative_expression
: cast_expression { $$ = $1; }
| multiplicative_expression '*' cast_expression
| multiplicative_expression '/' cast_expression
| multiplicative_expression '%' cast_expression
;

additive_expression
: multiplicative_expression { $$ = $1; }
| additive_expression '+' multiplicative_expression
| additive_expression '-' multiplicative_expression
;

shift_expression
: additive_expression { $$ = $1; }
| shift_expression TOKEN_LEFT_OP additive_expression
| shift_expression TOKEN_RIGHT_OP additive_expression
;

relational_expression
: shift_expression { $$ = $1; }
| relational_expression '<' shift_expression
| relational_expression '>' shift_expression
| relational_expression TOKEN_LE_OP shift_expression
| relational_expression TOKEN_GE_OP shift_expression
;

equality_expression
: relational_expression { $$ = $1; }
| equality_expression TOKEN_EQ_OP relational_expression
| equality_expression TOKEN_NE_OP relational_expression
;

and_expression
: equality_expression { $$ = $1; }
| and_expression '&' equality_expression
;

exclusive_or_expression
: and_expression { $$ = $1; }
| exclusive_or_expression '^' and_expression
;

inclusive_or_expression
: exclusive_or_expression { $$ = $1; }
| inclusive_or_expression '|' exclusive_or_expression
;

logical_and_expression
: inclusive_or_expression { $$ = $1; }
| logical_and_expression TOKEN_AND_OP inclusive_or_expression
;

logical_or_expression
: logical_and_expression { $$ = $1; }
| logical_or_expression TOKEN_OR_OP logical_and_expression
;

conditional_expression
: logical_or_expression { $$ = $1; }
| logical_or_expression '?' expression ':' conditional_expression
;

assignment_expression
: conditional_expression { $$ = $1; }
| unary_expression assignment_operator assignment_expression
;

assignment_operator
: '='                 { $$ = '='; }
| TOKEN_MUL_ASSIGN    { $$ = '*'; }
| TOKEN_DIV_ASSIGN    { $$ = '/'; }
| TOKEN_MOD_ASSIGN    { $$ = '%'; }
| TOKEN_ADD_ASSIGN    { $$ = '+'; }
| TOKEN_SUB_ASSIGN    { $$ = '-'; }
| TOKEN_LEFT_ASSIGN   { $$ = '>'; }
| TOKEN_RIGHT_ASSIGN  { $$ = '<'; }
| TOKEN_AND_ASSIGN    { $$ = '&'; }
| TOKEN_XOR_ASSIGN    { $$ = '^'; }
| TOKEN_OR_ASSIGN     { $$ = '|'; }
;

expression
: assignment_expression { $$ = $1; }
| expression ',' assignment_expression { $$ = expr_list($1, $3); }
;

constant_expression
: conditional_expression { /*expr_check_constant($1)*/ $$ = $1; }
;

declaration
: declaration_specifiers ';'
| declaration_specifiers init_declarator_list ';'
;

declaration_specifiers
: storage_class_specifier
| storage_class_specifier declaration_specifiers
| type_specifier
| type_specifier declaration_specifiers
| type_qualifier
| type_qualifier declaration_specifiers
;

init_declarator_list
: init_declarator
| init_declarator_list ',' init_declarator
;

init_declarator
: declarator
| declarator '=' initializer
;

storage_class_specifier
: TOKEN_TYPEDEF
| TOKEN_EXTERN
| TOKEN_STATIC
| TOKEN_AUTO
| TOKEN_REGISTER
;

type_specifier
: TOKEN_VOID
| TOKEN_CHAR
| TOKEN_SHORT
| TOKEN_INT
| TOKEN_LONG
| TOKEN_FLOAT
| TOKEN_DOUBLE
| TOKEN_SIGNED
| TOKEN_UNSIGNED
| struct_or_union_specifier
| enum_specifier
| TOKEN_TYPE_NAME
;

struct_or_union_specifier
: struct_or_union TOKEN_IDENTIFIER '{' struct_declaration_list '}'
| struct_or_union '{' struct_declaration_list '}'
| struct_or_union TOKEN_IDENTIFIER
;

struct_or_union
: TOKEN_STRUCT
| TOKEN_UNION
;

struct_declaration_list
: struct_declaration
| struct_declaration_list struct_declaration
;

struct_declaration
: specifier_qualifier_list struct_declarator_list ';'
;

specifier_qualifier_list
: type_specifier specifier_qualifier_list { list_append($$ = $2, $1); }
| type_specifier { $$ = list_new(LI_ELEM, $1, NULL); }
| type_qualifier specifier_qualifier_list { list_append($$ = $2, $1); }
| type_qualifier { $$ = list_new(LI_ELEM, $1, NULL); }
;

struct_declarator_list
: struct_declarator { $$ = list_new(LI_ELEM, $1, NULL); }
| struct_declarator_list ',' struct_declarator  { list_append($$ = $1, $3); }
;

struct_declarator
: declarator
| ':' constant_expression
| declarator ':' constant_expression
;

enum_specifier
: TOKEN_ENUM '{' enumerator_list '}'
| TOKEN_ENUM TOKEN_IDENTIFIER '{' enumerator_list '}'
| TOKEN_ENUM TOKEN_IDENTIFIER
;

enumerator_list
: enumerator
| enumerator_list ',' enumerator
;

enumerator
: TOKEN_IDENTIFIER
| TOKEN_IDENTIFIER '=' constant_expression
;

type_qualifier
: TOKEN_CONST
| TOKEN_VOLATILE
;

declarator
: pointer direct_declarator
| direct_declarator
;

direct_declarator
: TOKEN_IDENTIFIER { $$ = symbol_new($1, last_type_name); }
| '(' declarator ')' { $$ = $2; }
| direct_declarator '[' constant_expression ']' {
    $$ = $1;
    $$->type = type_new_array_type_reversed($1->type, $3);
  }
| direct_declarator '[' ']' {
    $$ = $1;
    $$->type = type_new_array_type_reversed($1->type, void_expression);
  }
| direct_declarator '(' parameter_type_list ')'
| direct_declarator '(' identifier_list ')'
| direct_declarator '(' ')'
;

pointer
: '*'
| '*' type_qualifier_list
| '*' pointer
| '*' type_qualifier_list pointer
;

type_qualifier_list
: type_qualifier
| type_qualifier_list type_qualifier
;

parameter_type_list
: parameter_list
| parameter_list ',' TOKEN_ELLIPSIS
;

parameter_list
: parameter_declaration
| parameter_list ',' parameter_declaration
;

parameter_declaration
: declaration_specifiers declarator
| declaration_specifiers abstract_declarator
| declaration_specifiers
;

identifier_list
: TOKEN_IDENTIFIER { $$ = list_new(LI_ELEM, $1, NULL); }
| identifier_list ',' TOKEN_IDENTIFIER { list_append($$ = $1, $3); }
;

type_name
: specifier_qualifier_list
| specifier_qualifier_list abstract_declarator
;

abstract_declarator
: pointer
| direct_abstract_declarator
| pointer direct_abstract_declarator
;

direct_abstract_declarator
: '(' abstract_declarator ')'
| '[' ']'
| '[' constant_expression ']'
| direct_abstract_declarator '[' ']'
| direct_abstract_declarator '[' constant_expression ']'
| '(' ')'
| '(' parameter_type_list ')'
| direct_abstract_declarator '(' ')'
| direct_abstract_declarator '(' parameter_type_list ')'
;

initializer
: assignment_expression
| '{' initializer_list '}'
| '{' initializer_list ',' '}'
;

initializer_list
: initializer { $$ = list_new(LI_ELEM, $1, NULL); }
| initializer_list ',' initializer { list_append($$ = $1, $3); }
;

statement
: labeled_statement { $$ = $1; }
| compound_statement  { $$ = $1; }
| expression_statement { $$ = $1; }
| selection_statement { $$ = $1; }
| iteration_statement { $$ = $1; }
| jump_statement { $$ = $1; }
;

labeled_statement
: TOKEN_IDENTIFIER ':' statement
| TOKEN_CASE constant_expression ':' statement
| TOKEN_DEFAULT ':' statement
;

compound_statement
: '{' '}' { $$ = stmt_compound(list_new(0), list_new(0)); }
| '{' statement_list '}' { $$ = stmt_compound(list_new(0), $2); }
| '{' declaration_list '}' { $$ = stmt_compound($2, list_new(0)); }
| '{' declaration_list statement_list '}' { $$ = stmt_compound($2, $3); }
;

declaration_list
: declaration { $$ = list_new(LI_ELEM, $1, NULL); }
| declaration_list declaration { list_append($$ = $1, $2); }
;

statement_list
: statement { $$ = list_new(LI_ELEM, $1, NULL); }
| statement_list statement { list_append($$ = $1, $2); }
;

expression_statement
: ';' { $$ = stmt_expression(void_expression); }
| expression ';' { $$ = stmt_expression($1); }
;

selection_statement
: TOKEN_IF '(' expression ')' statement  { $$ = stmt_if($3, $5); }
| TOKEN_IF '(' expression ')' statement TOKEN_ELSE statement
{ $$ = stmt_if_else($3, $5, $7); }
| TOKEN_SWITCH '(' expression ')' statement { $$ = stmt_switch($3, $5); }
;

iteration_statement
: TOKEN_WHILE '(' expression ')' statement  { $$ = stmt_while($3, $5); }
| TOKEN_DO statement TOKEN_WHILE '(' expression ')' ';'
{ $$ = stmt_do_while($5, $2); }
| TOKEN_FOR '(' expression_statement expression_statement ')' statement
{ $$ = stmt_for($3->expr, $4->expr, void_expression, $6); }
| TOKEN_FOR '(' expression_statement expression_statement expression ')' statement
{ $$ = stmt_for($3->expr, $4->expr, $5, $7); }
;

jump_statement
: TOKEN_GOTO TOKEN_IDENTIFIER ';' { $$ = stmt_goto($2); }
| TOKEN_CONTINUE ';'  { $$ = stmt_continue(); }
| TOKEN_BREAK ';' { $$ = stmt_break(); }
| TOKEN_RETURN ';' { $$ = stmt_return(void_expression); }
| TOKEN_RETURN expression ';' { $$ = stmt_return($2); }
;

translation_unit
: external_declaration
| translation_unit external_declaration
;

external_declaration
: function_definition
| declaration
;

function_definition
: declaration_specifiers declarator declaration_list compound_statement
| declaration_specifiers declarator compound_statement
| declarator declaration_list compound_statement
| declarator compound_statement
;

%%
