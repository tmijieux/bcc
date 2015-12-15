#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "type.h"
#include "symbol_table.h"
#include "error.h"
#include "program.h"

struct symbol *symbol_new(const char *name, const struct type *t)
{
    struct symbol *sy = calloc(sizeof *sy, 1);
    sy->name = name;
    sy->type = t;
    sy->variable = (struct symbol_variable) {0};
    sy->unique_id = prgm_get_unique_id();
    sy->suffix = "input.stack";	// DEFAULT
    /* used to differentiate between generated code and user code   */

    sy->variable.alloc_code = NULL;
    sy->variable.init_code = "";
    sy->variable.used = false;
    
    return sy;
}

void symbol_use(struct symbol *sy)
{
    sy->variable.used = true;
}

void symbol_print(const struct symbol *sy)
{
    fprintf(stderr, "SYMBOL: ");
    fprintf(stderr, "%s\n%s\b\n", sy->name, type_printable(sy->type));
    fputs("\b\n", stderr);
}

struct symbol *symbol_check(const char *name)
{
    struct symbol *sy = NULL;
    if (!st_search(name, &sy)) {
	error("undefined reference to %s\n", name);
	sy = symbol_new(name, type_generic);
    }

    return sy;
}

char *symbol_fully_qualified_name(const struct symbol *sym)
{
    char *level, *name;
    asprintf(&level, ".%d", sym->unique_id);
    asprintf(&name, "%s%s.%s%s", sym->variable.is_global ? "@" : "%",
	     sym->name, sym->suffix, (sym->level > 0) ? level : "");
    return name;
}
