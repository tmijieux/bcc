%{
/* grammar by Jutta Degener, 1995 */

#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "module.h"
#include "program.h"
#include "codegen.h"
#include "scanner.h"

#include "symbol/symbol.h"
#include "symbol/symbol_table.h"
#include "type/type.h"
#include "type/pointer.h"
#include "type/struct.h"
#include "type/specifier.h"
#include "type/enumerator.h"
#include "type/declarator.h"

#include "constant/constant.h"
#include "expression/expression.h"
#include "statement/statement.h"

#include "util/list.h"
#include "util/alloc.h"
#include "error/error.h"

extern int yylex();
int check_declaration_specifiers(struct list *declarator_specifiers);
%}
/*          %reentrant : 
            %pure-parser
            %locations
            %defines
            %error-verbose
            %lex-param { void *scanner }
*/
/*%expect 1*/

%token <string> TOKEN_IDENTIFIER
%token <constant> TOKEN_CONSTANT
%token <string> TOKEN_TYPE_NAME
                        
%token TOKEN_PTR_OP TOKEN_INC_OP TOKEN_DEC_OP TOKEN_LEFT_OP TOKEN_RIGHT_OP
%token TOKEN_LE_OP TOKEN_GE_OP TOKEN_EQ_OP TOKEN_NE_OP
                        
%token TOKEN_AND_OP TOKEN_OR_OP TOKEN_MUL_ASSIGN TOKEN_DIV_ASSIGN
%token TOKEN_MOD_ASSIGN TOKEN_ADD_ASSIGN TOKEN_SUB_ASSIGN TOKEN_LEFT_ASSIGN
%token TOKEN_RIGHT_ASSIGN TOKEN_AND_ASSIGN TOKEN_XOR_ASSIGN TOKEN_OR_ASSIGN

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
%type <list> type_qualifier_list

%type <list> declaration_specifiers
%type <list> declaration
%type <list> struct_declaration
                        
%type <statement> labeled_statement
%type <statement> compound_statement
%type <statement> expression_statement
%type <statement> selection_statement
%type <statement> iteration_statement
%type <statement> jump_statement
%type <statement> statement

%type <pointer> pointer
%type <specifier> storage_class_specifier
%type <specifier> type_specifier
%type <specifier> type_qualifier

%type <enumerator> enumerator
%type <declarator> direct_abstract_declarator
%type <declarator> declarator
%type <declarator> init_declarator
%type <declarator> direct_declarator
%type <declarator> struct_declarator
%type <declarator> abstract_declarator
%type <declarator> parameter_declaration
%type <function> function_definition
%type <symbol> function_definition_header
%type <initializer> initializer
%type <type> type_name

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
    struct enumerator *enumerator;
    struct declarator *declarator;
    struct pointer *pointer;
    struct list *list;
};
%%

primary_expression
: TOKEN_IDENTIFIER { $$ = expr_symbol(m, $1); }
| TOKEN_CONSTANT { $$ = expr_constant($1); }
| '(' expression ')' { $$ = $2; }
;

postfix_expression
: primary_expression { $$ = $1; }
| postfix_expression '[' expression ']' { $$ = expr_array($1, $3); }
| postfix_expression '(' ')' { $$ = expr_funcall($1, list_new(0)); }
| postfix_expression '(' argument_expression_list ')'
{ $$ = expr_funcall($1, $3); }

| postfix_expression '.' TOKEN_IDENTIFIER { $$ = expr_struct_access($1, $3); }

| postfix_expression TOKEN_PTR_OP TOKEN_IDENTIFIER
{ $$ = expr_struct_deref($1, $3); }

| postfix_expression TOKEN_INC_OP { $$ = expr_post_inc($1); }
| postfix_expression TOKEN_DEC_OP { $$ = expr_post_dec($1); }
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
{ $$ = expr_multiplication($1, $3); }
| multiplicative_expression '/' cast_expression { $$ = expr_division($1, $3); }
| multiplicative_expression '%' cast_expression { $$ = expr_modulo($1, $3); }
;

additive_expression
: multiplicative_expression { $$ = $1; }
| additive_expression '+' multiplicative_expression { $$ = expr_addition($1, $3); }
| additive_expression '-' multiplicative_expression
{ $$ = expr_substraction($1, $3); }
;

shift_expression
: additive_expression { $$ = $1; }
| shift_expression TOKEN_LEFT_OP additive_expression
{ $$ = expr_shift_left($1, $3); }
| shift_expression TOKEN_RIGHT_OP additive_expression
{ $$ = expr_shift_right($1, $3); }
;

relational_expression
: shift_expression { $$ = $1; }
| relational_expression '<' shift_expression { $$ = expr_lower($1, $3); } 
| relational_expression '>' shift_expression { $$ = expr_greater($1, $3); } 
| relational_expression TOKEN_LE_OP shift_expression  { $$ = expr_leq($1, $3); } 
| relational_expression TOKEN_GE_OP shift_expression { $$ = expr_geq($1, $3); } 
;

equality_expression
: relational_expression { $$ = $1; }
| equality_expression TOKEN_EQ_OP relational_expression { $$ = expr_eq($1, $3); }
| equality_expression TOKEN_NE_OP relational_expression { $$ = expr_neq($1, $3); }
;

and_expression
: equality_expression { $$ = $1; } 
| and_expression '&' equality_expression { $$ = expr_and($1, $3); }
;

exclusive_or_expression
: and_expression { $$ = $1; }
| exclusive_or_expression '^' and_expression { $$ = expr_xor($1, $3); }
;

inclusive_or_expression
: exclusive_or_expression { $$ = $1; }
| inclusive_or_expression '|' exclusive_or_expression { $$ = expr_or($1, $3); }
;

logical_and_expression
: inclusive_or_expression { $$ = $1; }
| logical_and_expression TOKEN_AND_OP inclusive_or_expression
{ $$ = expr_logical_and($1, $3); }
;

logical_or_expression
: logical_and_expression { $$ = $1; }
| logical_or_expression TOKEN_OR_OP logical_and_expression
{ $$ = expr_logical_or($1, $3); }
;

conditional_expression
: logical_or_expression { $$ = $1; }
| logical_or_expression '?' expression ':' conditional_expression
{ $$ = expr_neq($1, $3); }
;

assignment_expression
: conditional_expression { $$ = $1; }
| unary_expression assignment_operator assignment_expression
{ $$ = expr_assignment($1, $2, $3); }
;

assignment_operator
: '='                 { $$ = '='; }
| TOKEN_MUL_ASSIGN    { $$ = '*'; }
| TOKEN_DIV_ASSIGN    { $$ = '/'; }
| TOKEN_MOD_ASSIGN    { $$ = '%'; }
| TOKEN_ADD_ASSIGN    { $$ = '+'; }
| TOKEN_SUB_ASSIGN    { $$ = '-'; }
| TOKEN_LEFT_ASSIGN   { $$ = '<'; }
| TOKEN_RIGHT_ASSIGN  { $$ = '>'; }
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
: declaration_specifiers ';' { $$ = list_new(0);
     warning("declaration does not declare anything\n");
 }
| declaration_specifiers init_declarator_list ';' // beware of typedef storage class
{ declarator_process_list($1, $2, &$$); }
// --> check declarations specifiers once before
// $$ =  list_map($2, declarator_to_symbols, $2);
// --> insert in table
;

declaration_specifiers
: storage_class_specifier { $$ = list_new(LI_ELEM, $1, NULL); }
| type_qualifier { $$ = list_new(LI_ELEM, $1, NULL); }
| type_specifier { $$ = list_new(LI_ELEM, $1, NULL); }

| storage_class_specifier declaration_specifiers { list_append($$ = $2, $1); }
| type_specifier declaration_specifiers { list_append($$ = $2, $1); }
| type_qualifier declaration_specifiers { list_append($$ = $2, $1); }
;

init_declarator_list
: init_declarator { $$ = list_new(LI_ELEM, $1, NULL); }
| init_declarator_list ',' init_declarator { list_append($$ = $1, $3); }
;

init_declarator
: declarator { $$ = $1 }
| declarator '=' initializer { $$ = declarator_initializer($1, $3); }
;

storage_class_specifier
: TOKEN_TYPEDEF { $$ = specifier_new(SPEC_TYPEDEF); }
| TOKEN_EXTERN  { $$ = specifier_new(SPEC_EXTERN); }
| TOKEN_STATIC  { $$ = specifier_new(SPEC_STATIC); }
| TOKEN_AUTO    { $$ = specifier_new(SPEC_AUTO); }
| TOKEN_REGISTER { $$ = specifier_new(SPEC_REGISTER); }
;

type_specifier
: TOKEN_VOID { $$ = specifier_new(SPEC_TYPE_VOID); }
| TOKEN_CHAR { $$ = specifier_new(SPEC_TYPE_CHAR); }
| TOKEN_SHORT { $$ = specifier_new(SPEC_TYPE_SHORT); }
| TOKEN_INT { $$ = specifier_new(SPEC_TYPE_INT); }
| TOKEN_LONG { $$ = specifier_new(SPEC_TYPE_LONG); }
| TOKEN_FLOAT { $$ = specifier_new(SPEC_TYPE_FLOAT); }
| TOKEN_DOUBLE { $$ = specifier_new(SPEC_TYPE_DOUBLE); }
| TOKEN_SIGNED { $$ = specifier_new(SPEC_TYPE_SIGNED); }
| TOKEN_UNSIGNED { $$ = specifier_new(SPEC_TYPE_UNSIGNED); }
| struct_or_union_specifier { $$ = specifier_new(SPEC_UNIMPLEMENTED); }
| enum_specifier { $$ = specifier_new(SPEC_UNIMPLEMENTED); }
| TOKEN_TYPE_NAME { $$ = specifier_typename($1); }
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
: struct_declaration { $$ = $1; }
| struct_declaration_list struct_declaration { list_append_list($$ = $1, $2); }
;

struct_declaration
: specifier_qualifier_list struct_declarator_list ';' { $$ = $2; }
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
: declarator { $$ = declarator_struct_field($1, void_expression); }
| ':' constant_expression { $$ = declarator_struct_field(NULL, $2); }
| declarator ':' constant_expression { $$ = declarator_struct_field($1, $3); }
;

enum_specifier
: TOKEN_ENUM '{' enumerator_list '}'
| TOKEN_ENUM TOKEN_IDENTIFIER '{' enumerator_list '}'
| TOKEN_ENUM TOKEN_IDENTIFIER
;

enumerator_list
: enumerator { $$ = list_new(LI_ELEM, $1, NULL); }
| enumerator_list ',' enumerator { list_append($$ = $1, $3); }
;

enumerator
: TOKEN_IDENTIFIER { $$ = enumerator_new($1, false, NULL); }
| TOKEN_IDENTIFIER '=' constant_expression { $$ = enumerator_new($1, true, $3); }
;

type_qualifier
: TOKEN_CONST { $$ = specifier_new(SPEC_CONST); }
| TOKEN_VOLATILE { $$ = specifier_new(SPEC_VOLATILE); }
;

declarator
: pointer direct_declarator { $$ = declarator_pointer($2, $1); }
| direct_declarator { $$ = $1; }
;

direct_declarator
: TOKEN_IDENTIFIER { $$ = declarator_identifier($1); }
| '(' declarator ')' { $$ = $2; }
| direct_declarator '[' constant_expression ']' { $$ = declarator_array($1, $3); }
| direct_declarator '[' ']' { $$ = declarator_array($1, void_expression); }
| direct_declarator '(' parameter_type_list ')'
{ $$ = declarator_function($1, $3); }
| direct_declarator '(' identifier_list ')' // old style
{ $$ = declarator_function_old($1, $3); } 
| direct_declarator '(' ')' { $$ = declarator_function($1, list_new(0)); }
;

pointer
: '*' { $$ = pointer_new(list_new(0), NULL); }
| '*' type_qualifier_list { $$ = pointer_new($2, NULL); }
| '*' pointer { $$ = pointer_new(list_new(0), $2); }
| '*' type_qualifier_list pointer { $$ = pointer_new($2, $3); }
;

type_qualifier_list
: type_qualifier {$$ = list_new(LI_ELEM, $1, NULL); }
| type_qualifier_list type_qualifier { list_append($$ = $1, $2); }
;

parameter_type_list
: parameter_list { declarator_process_param_list($1, &$$); }
| parameter_list ',' TOKEN_ELLIPSIS
{ declarator_process_param_list($1, &$$);
  internal_warning("param_list ellipsis not handled "); }
;

parameter_list
: parameter_declaration { $$ = list_new(LI_ELEM, $1, NULL); }
| parameter_list ',' parameter_declaration { list_append($$ = $1, $3); }
;

parameter_declaration
: declaration_specifiers declarator { $$ = declarator_specifier($2, $1); }
| declaration_specifiers abstract_declarator { $$ = declarator_specifier($2, $1); }
| declaration_specifiers { $$ = declarator_specifier(NULL, $1); } 
;

identifier_list // old style function declaration only
: TOKEN_IDENTIFIER { $$ = list_new(LI_ELEM, $1, NULL); }
| identifier_list ',' TOKEN_IDENTIFIER { list_append($$ = $1, $3); }
;

type_name
: specifier_qualifier_list { $$ = specifier_list_get_type($1);  }
| specifier_qualifier_list abstract_declarator
{ $$ = declarator_type($2, specifier_list_get_type($1)); }
;

abstract_declarator
: pointer { $$ = declarator_pointer(NULL, $1); }
| direct_abstract_declarator { $$ = $1; }
| pointer direct_abstract_declarator { $$ = declarator_pointer($2, $1); }
;

direct_abstract_declarator
: '(' abstract_declarator ')' { $$ = $2; }
| '[' ']' { $$ = declarator_array(NULL, void_expression); }
| '[' constant_expression ']' { $$ = declarator_array(NULL, $2); }
| direct_abstract_declarator '[' ']'
{ $$ = declarator_array($1, void_expression); }
| direct_abstract_declarator '[' constant_expression ']'
{ $$ = declarator_array($1, $3); }
| '(' ')'  { $$ = declarator_function(NULL, list_new(0)); }
| '(' parameter_type_list ')'  { $$ = declarator_function(NULL, $2); }
| direct_abstract_declarator '(' ')' { $$ = declarator_function($1, list_new(0)); }
| direct_abstract_declarator '(' parameter_type_list ')'
{ $$ = declarator_function($1, $3); }
;

initializer
: assignment_expression { $$ = initializer_expression($1); }
| '{' initializer_list '}' { $$ = initializer_list($2); }
| '{' initializer_list ',' '}' { $$ = initializer_list($2); }
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
: TOKEN_IDENTIFIER ':' statement { $$ = stmt_label($3, $1); }
| TOKEN_CASE constant_expression ':' statement { $$ = stmt_case($4, $2); }
| TOKEN_DEFAULT ':' statement { $$ = stmt_default($3); }
;

compound_statement
: '{' '}' { $$ = stmt_compound(list_new(0), list_new(0)); }
| left_brace statement_list right_brace { $$ = stmt_compound(list_new(0), $2); }
| left_brace declaration_list right_brace { $$ = stmt_compound($2, list_new(0)); }
| left_brace declaration_list statement_list right_brace
{ $$ = stmt_compound($2, $3); }
;

left_brace
: '{' { st_push(); }

right_brace
: '}' { st_pop(); }

declaration_list
: declaration { $$ = $1 };
| declaration_list declaration { list_append_list($$ = $1, $2); }
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
| declaration { // maybe handle typedef at this level
    int si = list_size($1);
    for (int i = 1; i <= si; ++i)
        module_add_global(m, list_get($1, i), false);
 }
;

function_definition
: function_definition_header compound_statement
{ $$ = module_get_or_create_function(m, $1);
    fun_set_body($$, $2);
 }
;

function_definition_header
: declaration_specifiers declarator declaration_list
 {  internal_error("old style function declaration not supported"); }
| declaration_specifiers declarator {
    struct symbol *sy = symbol_new(
        declarator_get_name($2),
        declarator_type($2, specifier_list_get_type($1)));
    $$ = function_declare(sy, declarator_deepest_param_list($2), m);  // FIXME
 }
| declarator declaration_list
 {  internal_error("old style function declaration not supported"); }
| declarator {
    struct symbol *sy = symbol_new(declarator_get_name($1),
                                   declarator_type($1, type_int));
    $$ = function_declare(sy, declarator_deepest_param_list($1), m);
}
;

%%
