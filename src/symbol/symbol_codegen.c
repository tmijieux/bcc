#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol.h"
#include "../codegen.h"
#include "../program.h"
#include "../function.h"
#include "../statement/statement.h"

void symb_cg(struct symbol *sy)
{
    const char *typestr = type_cg(sy->type);
    char *init_code;

    asprintf(&init_code, "%s = alloca %s%s\n", symbol_fully_qualified_name(sy),
             typestr, sy->type->type == TYPE_ARRAY ? ", align 8" : "");
    sy->variable.alloc_code = init_code;

    if (sy->variable.is_parameter) {
        asprintf(&init_code,
                 "store %s %%%s.%s, %s* %s\n",
                 typestr, sy->name, "param",
                 typestr, symbol_fully_qualified_name(sy));
        sy->variable.init_code = init_code;
    }
}

