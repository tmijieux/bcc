#ifndef FUNCTION_H
#define FUNCTION_H

#include "symbol.h"
#include "statement.h"
#include "module.h"

struct function {
	struct symbol *name_s;
	const struct type *type;
	struct statement *body;

	const char *code;
	const char *vcode;

	struct hash_table *alloc_init;
	struct list *allocas;

	int body_set;
};

extern struct function *current_fun;

struct function *fun_new(struct symbol *sym);
int fun_set_body(struct function *fun,
		 const struct statement *compound_statement);	// = body
void fun_add_allocas(struct function *fun, struct symbol *sym);
struct symbol *
function_declare(struct symbol *declarator, struct list *param_list,
                 struct module *m);

#endif	//FUNCTION_H
