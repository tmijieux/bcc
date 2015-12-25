#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>

#include "symbol_table.h"
#include "../util/hash_table.h"
#include "../util/list.h"
#include "../error/error.h"
#include "../program.h"
#include "../codegen.h"
#include "../function.h"

static struct symbol_table *st;

struct symbol_table {
    int level;
    struct hash_table *ht;
    struct symbol_table *next;
    int64_t size;
};

/**
 *  This is a temporary variable used to save
 *  parameter of function definition to insert them
 *  once the function compound statement really starts
 */
static struct list *function_parameters = NULL;

static void check_variable_use(const struct hash_table *);

void st_set_parameters(struct list *l)
{
    function_parameters = l;
    if (st->level == 0)	{ // this has no meaning inside a function
        function_parameters = l;
    } else {
        internal_error("st_set_parameter was called inside a block\n");
    }
}

void st_init(void)
{
    st = calloc(sizeof *st, 1);
    st->ht = ht_create(0, NULL);
    st->next = NULL;
    st->level = 0;
}

/**
 * add the symbol 'sy' at the top of the symbol_table stack
 * if the symbol already exist **at the top** of the stack
 * no operation is performed and the function returns 0
 * otherwise the symbol is added, and the function returns 1
 *
 * N.B.: the symbol is added even if a symbol with the same name
 * exists somewhere **strictly lower than the top** in the stack
 */

int st_add(struct symbol *sy)
{
    sy->level = st->level;
    if (ht_has_entry(st->ht, sy->name))
	return 0;

    if (st->level >= 1) {
	symb_cg(sy);
	fun_add_allocas(current_fun, sy);
    }

    ht_add_entry(st->ht, sy->name, sy);
    return 1;
}

/**
 * search for symbol 'name'
 * if found, returns 1 and the symbol in *sy_ret
 * returns  0 otherwise
 */
int st_search(const char *name, struct symbol **sy_ret)
{
    struct symbol_table *sym = st;
    while (sym != NULL) {
	if (ht_get_entry(sym->ht, name, sy_ret) == 0)
	    return 1;
	sym = sym->next;
    }
    return 0;
}

/**
 * pop a symbol_table from the symbol table's stack
 * this is used to end the scope of local variables in a compound statement
 */
void st_pop(void)
{
    if (st->level > 0) {
	check_variable_use(st->ht);
        st->ht = NULL;
	st = st->next;
    }
}

/**
 * push a symbol_table to the symbol table's stack
 * this is used to create a new scope for  local variables in a
 * compound statement
 */
void st_push(void)
{
    struct symbol_table *new = calloc(sizeof *new, 1);
    new->ht = ht_create(100, NULL);
    new->next = st;    
    new->level = st->level + 1;
    st = new;

    if (st->level == 1)	{ // if we just entered inside a function
	int s = list_size(function_parameters);
	for (int i = 1; i <= s; ++i) {
	    // push the function parameters to the declared symbols
	    struct symbol *tmp = list_get(function_parameters, i);
	    if (s == 1) {
                // OOOHHHH We may want to vectorize this function!!!!!
		// symbol_prepare_vectorization(tmp);
	    }

	    if (!st_add(tmp))
		error("symbol multiple definition: %s \n", tmp->name);
            symb_cg(tmp);
	}
	function_parameters = list_new(0); // ... and reset the list
    }
}

/**
 * exit the symbol_table stack module
 * no action within this module is to be considered valid
 * after this function was called
 *
 */
void st_exit(struct symbol_table *st)
{
    if (NULL != st) st->ht = NULL;
    st = NULL;
}

/**
 * return the level of the symbol table
 * 0 is for out of any function
 * 1 if for a function
 * >= 2 is for an compound instruction (block) within a function
 */
int st_level(struct symbol_table *st)
{
    return st->level;
}

static void check_variable_use(const struct hash_table *ht)
{
    struct list *l = ht_to_list(ht);
    int si = list_size(l);
    for (int i = 1; i <= si; ++i) {
	struct symbol *sy = list_get(l, i);
	if (sy->symbol_type == SYM_VARIABLE && !sy->variable.used) {
	    warning("unused variable %s\n", sy->name);
	}
    }
}
