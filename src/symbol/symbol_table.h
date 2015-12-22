#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include "list.h"

void st_init(void);
void st_pop(void);
void st_push(void);
void st_exit(void);

int st_add(struct symbol *sy);
int st_search(const char *name, struct symbol **sy_ret);

void st_set_parameters(struct list *l);

#endif	//SYMBOL_TABLE_H
