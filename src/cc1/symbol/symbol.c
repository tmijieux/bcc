#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol.h"
#include "symbol_table.h"

#include "../type/type.h"
#include "../util/error.h"
#include "../program.h"

struct symbol *symbol_new(const char *name,
                          enum symbol_type symbol_type,
                          const struct type *type,
                          enum symbol_storage ssto)
{
    assert(type != NULL);
    struct symbol *sym = calloc(sizeof *sym, 1);
    sym->magic = MAGIC_SYMBOL;

    sym->symbol_type = symbol_type;
    sym->type = type;
    sym->name = name;

    sym->used = false;
    sym->in_table = false;
    sym->suffix = "input.stack";	// default value

    sym->unique_id = prgm_get_unique_id();
    sym->variable.alloc_code = NULL;
    sym->variable.init_code = "";
    /* used to differentiate between generated code and user code   */

    return sym;
}

struct symbol *sym_new_function_symbol(const char *name,
                                       const struct type *t,
                                       enum symbol_visibility vby,
                                       enum symbol_storage sto)
{
    internal_error("sym_new_function_symbol not implemented\n");
    return symbol_generic(name);
}

struct symbol *symbol_generic(const char *name)
{
    struct symbol *s = symbol_new(name, SYM_UNDEF, type_generic, STO_UNDEF);
    s->suffix = "generic";
    return s;
}

void symbol_notice_use(struct symbol *sy)
{
    sy->used = true;
}


#ifndef stringify
#define stringify(x__) #x__
#endif

static const char* symbol_type_printable(enum symbol_type st)
{
    if (SYM_UNDEF == st)
        return stringify(SYM_UNDEF);
    if (SYM_VARIABLE == st)
        return stringify(SYM_VARIABLE);
    if (SYM_FUNCTION == st)
        return stringify(SYM_FUNCTION);
    if (SYM_ARRAY == st)
        return stringify(SYM_ARRAY);
    if (SYM_TYPENAME == st)
        return stringify(SYM_TYPENAME);
    return "unexpected sym_type; may be serious problem";
}

void symbol_debug_print(const struct symbol *sy)
{
    fprintf(stderr, "Sym: \t'%s' \t: %s : %s\n",
            sy->name,
            symbol_type_printable(sy->symbol_type),
            type_printable(sy->type));
}

char *symbol_fully_qualified_name(const struct symbol *sym)
{
    char *id, *name;
    bool global = symbol_is_global(sym);

    asprintf(&id, ".%d", sym->unique_id);
    asprintf(&name, "%s%s.%s%s", global ? "@" : "%",
             sym->name, sym->suffix, global ? "" : id);
    return name;
}

bool symbol_is_variable(const struct symbol *sy)
{
    return (SYM_VARIABLE == sy->symbol_type);
}

bool symbol_is_array(const struct symbol *sy)
{
    return (SYM_ARRAY == sy->symbol_type);
}

bool symbol_is_function(const struct symbol *sy)
{
    return (SYM_FUNCTION == sy->symbol_type);
}

bool symbol_is_typename(const struct symbol *sy)
{
    return (SYM_TYPENAME == sy->symbol_type);
}

bool symbol_is_global(const struct symbol *sy)
{
    return (0 == sy->scope_level);
}

bool symbol_used(const struct symbol *sy)
{
    return sy->used;
}

const char *symbol_get_name(const struct symbol *sy)
{
    return sy->name;
}

const struct type *symbol_get_type(const struct symbol *sy)
{
    return sy->type;
}
