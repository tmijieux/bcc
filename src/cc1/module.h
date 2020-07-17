#ifndef BCC_MODULE_H
#define BCC_MODULE_H

#include <stdio.h>

struct module;
struct function;

#include "symbol/symbol.h"
#include "symbol/symbol_table.h"

struct module *module_new(const char *module_name);

struct function *
module_get_or_create_function(struct module *m, struct symbol *sym);

void module_print(struct module *m, FILE * out);

void module_add_prototype(struct module *m, struct symbol *sym);
void module_add_global(struct module *m, struct symbol *sym, bool extern_);


void module_set_last_function_name(struct module *m, const char *name);
const char *module_get_last_function_name(struct module *m);

extern struct module *globalModule;

#endif // BCC_MODULE_H

