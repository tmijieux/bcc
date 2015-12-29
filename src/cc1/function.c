#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>

#include "function.h"
#include "codegen.h"
#include "symbol/symbol.h"
#include "symbol/symbol_table.h"
#include "util/hash_table.h"
#include "statement/statement.h"
#include "util/error.h"
#include "errorc.h"

#include "module.h"

struct function *current_fun = NULL;

struct function *fun_new(struct symbol *name_s)
{
    struct function *fun = calloc(sizeof *fun, 1);

    fun->name_s = name_s;
    fun->type = name_s->type;

    fun->body_set = 0;
    fun->code = "";
    fun->vcode = "";

    fun->alloc_init = ht_create(100, NULL);
    fun->allocas = list_new(0);

    return fun;
}

int fun_set_body(struct function *fun, const struct statement *compnd)
{
    if (fun->body_set)
	return -1;

    assert(STMT_COMPOUND == compnd->statement_type);

    if (NULL != compnd->stmt_list) {
	int si = list_size(compnd->stmt_list);
	struct statement *st = list_get(compnd->stmt_list, si);
	if (st->statement_type != STMT_RETURN) {
	    if (type_function_return(fun->name_s->type) == type_void) {
		// add an implicit return void at end of
		// void function :
		struct list *l = list_copy(compnd->stmt_list);
		list_append(l, stmt_return(void_expression));
		compnd = stmt_compound(compnd->decl_list, l);
	    } else {
		// if the function is not void, it MUST
		// have a return statement
		error("last statement in function "
		      "must be a return statement\n");
	    }
	}
	fun->body = (struct statement *) compnd;
    }
    fun->body_set = 1;
    return 0;
}

void fun_add_allocas(struct function *fun, struct symbol *sym)
{
    const char *fname = symbol_fully_qualified_name(sym);

    if (!ht_has_entry(fun->alloc_init, fname)) {
	ht_add_entry(fun->alloc_init, fname, NULL /*useless dummy */ );

	if (sym->variable.alloc_code != NULL)
	    list_append(fun->allocas, sym->variable.alloc_code);
    }
}

void fun_cg(struct function *fun)
{
    if (!fun->body_set || !fun->body) {
	fun->code = "";
	fun->vcode = "";
	return;
    }

    if (NULL == fun->body->stmt_list) {
	internal_error("fun_cg: compnd: no code\n");
	return;
    }

    struct statement *compnd = fun->body;
    stmt_cg(compnd);

    char *allocas = "";
    int si = list_size(fun->allocas);
    for (int i = 1; i <= si; ++i)
	asprintf(&allocas, "%s%s", allocas,
		 (char *) list_get(fun->allocas, i));

    struct symbol *funsymb = fun->name_s;
    char *funcode;
    asprintf(&funcode, "define %s @%s(%s) {\n"
	     "start:\n"
	     "%s"	// all function alloca
	     "%s"	// parameter init // all function init
	     "%s"	// function body code
	     "}\n",
	     type_cg(type_function_return(fun->type)), funsymb->name,
	     type_cg_arglist(type_function_argv(fun->type)), allocas,
	     decl_init_list(type_function_argv(fun->type)), compnd->code);
    fun->code = funcode;

    if (type_function_argc(fun->type) == 1) {
	// GENERATE VECTORIZED META SUPPPPAAAA CODE

	
	asprintf(&funcode, "define %s @%s.vectorize(%s) {\n"
		 "start:\n"
		 "%s"	// all function alloca
		 "%s"	// parameter init // all function init
		 "%s"	// function body code
		 "}\n",
		 type_cg(type_function_return(fun->type)), funsymb->name,
		 type_cg_arglist(type_function_argv(fun->type)),
		 allocas,
		 decl_init_list(type_function_argv(fun->type)),
		 compnd->code);
	fun->vcode = funcode;
    }
}

struct symbol *
function_declare(struct symbol *declarator,
                 const struct list *param_list, struct module *m)
{
    assert( type_is_function(declarator->type) );

    st_set_parameters(param_list);
    declarator->symbol_type = SYM_FUNCTION;
    
    struct symbol *tmpsy;
    if ( !st_search(declarator->name, &tmpsy) ) {
	// first declaration : add to the table
	st_add(declarator);
    } else {
	if ( !type_equal( tmpsy->type, declarator->type ) ) {
	    error("declaration of function '%s' does "
		  "not match previous declaration\n", declarator->name);
	}
    }
    
    for (int i = 1; i <= list_size(param_list); ++i)
	assert(((struct symbol*)list_get(param_list,i))
               ->variable.is_parameter);
    
    last_function_return_type = type_function_return(declarator->type);
    current_fun = module_get_or_create_function(m, declarator);
    return declarator;
}
