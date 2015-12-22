#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include "string_literal.h"
#include "hash_table.h"
#include "string.h"
#include "error.h"
#include "string2.h"

static int str_count = 0;
struct hash_table *lits;

__attribute__((constructor))
static void init(void)
{
    lits = ht_create(0, NULL);
}

struct literal *string_get_or_create_literal(const char *literal)
{
    struct literal *newlit = NULL;
    if (ht_get_entry(lits, literal, &newlit) != 0)
    {
        newlit = calloc(sizeof*newlit, 1);
        asprintf(&newlit->reg, "@.str%d", ++str_count);
        newlit->value = strstrip2(literal+1);
        newlit->length = strlen(literal) - 1;
//        debug("Adding literal %s, %s\n", newlit->reg, literal);
        ht_add_entry(lits, literal, newlit);
    }

    return newlit;
}

struct list *string_get_literals_list(void)
{
//    debug("list size literals : %d\n" , list_size(ht_to_list(lits)));
    return ht_to_list(lits);
}
