#ifndef CODEGEN_H
#define CODEGEN_H

#include "list.h"
#include "type.h"
#include "expression.h"
#include "statement.h"
#include "function.h"

const char *type_cg(const struct type *);
const char *type_cg_arglist(const struct list *);	// list of symbols
const char *type_cg_arglist_nameless(const struct list *);

void symb_cg(struct symbol *);
void expr_cg(const struct expression *);
void stmt_cg(const struct statement *);
void fun_cg(struct function *);

#endif	//CODEGEN_H
