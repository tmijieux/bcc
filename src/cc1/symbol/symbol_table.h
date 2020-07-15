#ifndef BCC_SYMBOL_TABLE_H
#define BCC_SYMBOL_TABLE_H

#include <stdbool.h>

// SYMBOL TABLES are hashtables meant to store symbols
// symbols may refer to:
// - variables names,
// - typedef'd typename
// - struct names
// - union names
// - enum names

// - there is a global symbol table per file for global variables/types
// - there is a symbol table for each function // each braces pair (only compound statement)
// (some  statement that use braces like switch case does not have a compound statement)
// (one may define a struct / typedef in any scope, including function / compound statement scope )


struct symbol_table;

#include "symbol.h"
#include "../util/list.h"


void st_init(void);
int st_add(struct symbol *sy);
int st_search(const char *name, struct symbol **sy_ret);

void st_pop(void);
void st_push(void);
bool st_global_context(void);
int st_level(void);
void st_set_parameters(const struct list *l);
void st_dump(void);

#endif // BCC_SYMBOL_TABLE_H
