#ifndef MODULE_H
#define MODULE_H

#include "symbol.h"

struct module;
struct function;

extern struct module *m;

struct module *module_new(const char *module_name);
void module_free(struct module *m);

struct function *
module_get_or_create_function(struct module *m, struct symbol *sym);

void module_print(struct module *m, FILE * out);

void module_add_prototype(struct module *m, struct symbol *sym);
void module_add_global(struct module *m, struct symbol *sym, bool extern_);

#endif	//MODULE_H
