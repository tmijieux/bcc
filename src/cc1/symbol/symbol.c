#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol.h"
#include "symbol_table.h"

#include "../type/type.h"
#include "../util/error.h"
#include "../program.h"

struct symbol *symbol_new(const char *name, const struct type *t)
{
    struct symbol *sy = calloc(sizeof *sy, 1);

    assert(NULL != t);

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

struct symbol *symbol_generic(void)
{
    struct symbol *s = symbol_new("generic", type_generic);
    s->suffix = "generic";
    return s;
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


char *symbol_fully_qualified_name(const struct symbol *sym)
{
    char *level, *name;
    asprintf(&level, ".%d", sym->unique_id);
    asprintf(&name, "%s%s.%s%s", sym->variable.is_global ? "@" : "%",
	     sym->name, sym->suffix, (sym->level > 0) ? level : "");
    return name;
}
