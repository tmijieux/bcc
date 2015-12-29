#ifndef MODULE_H
#define MODULE_H

struct module;
struct function;

#include <stdio.h>
#include "symbol/symbol.h"
#include "symbol/symbol_table.h"

struct module *module_new(const char *module_name);

struct function *
module_get_or_create_function(struct module *m, struct symbol *sym);

void module_print(struct module *m, FILE * out);

void module_add_prototype(struct module *m, struct symbol *sym);
void module_add_global(struct module *m, struct symbol *sym, bool extern_);

extern struct module *m;

#endif	//MODULE_H

