#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdint.h>
#include <list.h>

#include "codegen.h"
#include "symbol.h"
#include "type.h"
#include "expression.h"

const char *type_cg_arglist_nameless(const struct list *l)
{
    char *tmp = "";
    int s = list_size(l);

    for (int i = 1; i <= s; ++i) {
	struct symbol *sy = (struct symbol *) list_get(l, i);
        asprintf(&tmp, "%s%s %s ", tmp, i > 1 ? "," : "", type_cg(sy->type));
    }

    return tmp;
}

const char *type_cg(const struct type *t)
{
    char *lt = "";

    switch (t->type) {
    case TYPE_ARRAY:
        //          {i32, [ 100 x type ] }
        asprintf(&lt, "{i64, [ 0 x %s ]}*", type_cg(type_array_values(t)));
        break;
    case TYPE_FUNCTION:
        asprintf(&lt, "%s (%s) *",
                 type_cg(type_function_return(t)),
                 type_cg_arglist_nameless(type_function_argv(t)));
        break;

    case TYPE_FLOAT:
        lt = "float";
        break;
    case TYPE_VOID:
        lt = "void";
        break;
    case TYPE_STRING:
    case TYPE_GENERIC:
        lt = "i8*";
        break;
    case TYPE_BOOL:
        lt = "i1";
        break;
    case TYPE_BYTE:
        lt = "i8";
        break;
    case TYPE_SHORT:
        lt = "i16";
        break;
    case TYPE_INT:
        lt = "i32";
        break;
    case TYPE_LONG:
        lt = "i64";
        break;
    default:
        lt = "undef";
        break;
    }
    return lt;
}

// take a list of symbols*
const char *type_cg_arglist(const struct list *l)
{
    char *tmp = "";
    int s = list_size(l);
    
    for (int i = 1; i <= s; ++i) {
        struct symbol *sy = (struct symbol *) list_get(l, i);
        asprintf(&tmp, "%s%s%s %%%s.%s", tmp,
                 i == 1 ? "" : ", ", type_cg(sy->type), sy->name, "param");
    }
    return tmp;
}
