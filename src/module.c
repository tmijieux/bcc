#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include "module.h"
#include "function.h"
#include "symbol.h"
#include "hash_table.h"
#include "codegen.h"

struct module {
    struct hash_table *funtable;
    struct list *funlist;

    struct list *protolist;
    struct list *globlist;

    const char *name;
};

struct prototype {
    const char *name;
    char *code;
};

struct module *m = NULL;

struct module *module_new(const char *module_name)
{
    struct module *m = calloc(sizeof *m, 1);
    m->funtable = ht_create(0, NULL);

    m->funlist = list_new(0);
    m->protolist = list_new(0);
    m->globlist = list_new(0);

    m->name = module_name;
    return m;
}

void module_free(struct module *m)
{
    ht_free(m->funtable);
    list_free(m->funlist);
    free(m);
}

struct function *
module_get_or_create_function(struct module *m, struct symbol *sym)
{
    struct function *fun;
    if (ht_get_entry(m->funtable, sym->name, &fun) != 0) {
	fun = fun_new(sym);
	ht_add_entry(m->funtable, sym->name, fun);
	list_append(m->funlist, fun);
    }
    return fun;
}

void module_print(struct module *m, FILE * out)
{
    int si;
    puts("declare i8* @GC_malloc(i64 %s)");
    puts("declare void @map(i8*)");
    puts("declare void @reduce(i8*)");

    fputs("\n", out);

    si = list_size(m->protolist);
    for (int i = 1; i <= si; ++i) {
	struct prototype *pt = list_get(m->protolist, i);
	struct function *f;
	ht_get_entry(m->funtable, pt->name, &f);
	if (!f->body_set)
	    fputs(pt->code, out);
    }
    
    fputs("\n", out);
    si = list_size(m->globlist);
    for (int i = 1; i <= si; ++i)
	fputs(list_get(m->globlist, i), out);

    fputs("\n", out);

    si = list_size(m->funlist);
    for (int i = 1; i <= si; ++i) {
	struct function *fun = list_get(m->funlist, i);
	fun_cg(fun);
	fputs(fun->code, out);
    }
}

void module_add_prototype(struct module *m, struct symbol *sym)
{
    assert(sym->type->type == TYPE_FUNCTION);
    struct prototype *pt = calloc(sizeof*pt, 1);
    pt->name = sym->name;
    asprintf(&pt->code, "declare %s @%s(%s)\n",
	     type_cg(type_function_return(sym->type)), sym->name,
	     type_cg_arglist_nameless(type_function_argv(sym->type)));
    list_append(m->protolist, pt);
}

void module_add_global(struct module *m, struct symbol *sym)
{
    assert(sym->type->type != TYPE_FUNCTION);
    assert(sym->type->type != TYPE_VOID);
    assert(sym->type->type != TYPE_UNDEF);

    sym->suffix = "input.global";
    sym->variable.is_global = 1;

    char *code;
    asprintf(&code, "%s = global %s 0\n",
	     symbol_fully_qualified_name(sym), type_cg(sym->type));

    list_append(m->globlist, code);

}
