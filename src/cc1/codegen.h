#ifndef CODEGEN_H
#define CODEGEN_H

#include "function.h"

#include "expression/expression.h"
#include "statement/statement.h"
#include "type/type.h"
#include "util/list.h"

const char *type_cg(const struct type *);
const char *type_cg_arglist(const struct list *);	// list of symbols
const char *type_cg_arglist_nameless(const struct list *);

void symb_cg(struct symbol *);
void expr_cg(const struct expression *);
void stmt_cg(const struct statement *);
void fun_cg(struct function *);

#endif	//CODEGEN_H
