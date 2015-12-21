#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>
#include "module.h"
#include "function.h"
#include "symbol.h"
#include "hash_table.h"
#include "codegen.h"
#include "string_literal.h"
#include "error.h"

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

static int module_add_default_prototype(struct module *m);
static void check_main_prototype(struct symbol *main);

struct module *module_new(const char *module_name)
{
    struct module *m = calloc(sizeof *m, 1);
    m->funtable = ht_create(0, NULL);

    m->funlist = list_new(0);
    m->protolist = list_new(0);
    m->globlist = list_new(0);

    m->name = module_name;

    module_add_default_prototype(m);
    
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

        if (!strcmp(sym->name, "main")) {
            check_main_prototype(sym);
        }
    }

    
    return fun;
}

static int module_add_default_prototype(struct module *m)
{
    struct symbol *param, *fun;
    
    param = symbol_new("size", type_long);
    param->variable.is_parameter = true;
    fun = function_declare(symbol_new("GC_malloc", type_generic),
                           list_new(LI_ELEM, param, NULL), m);
    module_add_prototype(m, fun);

    param = symbol_new("map_controller", type_generic);
    param->variable.is_parameter = true;
    fun = function_declare(symbol_new("map", type_void), 
                           list_new(LI_ELEM, param, NULL), m); // arguments
    module_add_prototype(m, fun);

    param = symbol_new("reduce_controller", type_generic);
    param->variable.is_parameter = true;
    fun = function_declare(symbol_new("reduce", type_void), 
                           list_new(LI_ELEM, param, NULL), m); // arguments
    module_add_prototype(m, fun);

    return 0;
}

void module_print(struct module *m, FILE * out)
{
    int si;
    /* puts("declare i8* @GC_malloc(i64 %s)"); */
    /* puts("declare void @map(i8*)"); */
    /* puts("declare void @reduce(i8*)"); */

    /* fputs("\n", out); */

    si = list_size(m->protolist);
//    debug("protolist size: %d\n", si);
    for (int i = 1; i <= si; ++i) {
        
	struct prototype *pt = list_get(m->protolist, i);
	struct function *f = NULL;
	ht_get_entry(m->funtable, pt->name, &f);
	if (!f->body_set)
	    fputs(pt->code, out);
        /* else
           debug("code is set: %s\n", pt->name); */
    }

    fputs("\n;literals\n", out);
    struct list *literals = string_get_literals_list();
    si = list_size(literals);
    for (int i = 1; i <= si; ++i) {
        struct literal *lit = list_get(literals, i);
        fprintf(out, "%s = private unnamed_addr constant [%zu x i8] c\"%s\\00\"",
                lit->reg, lit->length, lit->value);
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

    /* debug("prototype added %s\n", sym->name, pt->code); */
}

void module_add_global(struct module *m, struct symbol *sym, bool extern_)
{
    assert(sym->type->type != TYPE_FUNCTION);
    assert(sym->type->type != TYPE_VOID);
    assert(sym->type->type != TYPE_UNDEF);

    sym->suffix = "input.global";
    sym->variable.is_global = 1;

    char *code;
    asprintf(&code, "%s =%s global %s %s\n",
	     symbol_fully_qualified_name(sym),
             extern_ ? " external" : "",
             type_cg(sym->type),
             extern_ ? "" : "0");

    list_append(m->globlist, code);

}

static void display_main_proto(void)
{
    warning("\nmain definition should follow one of the following prototype:\n"
            "void/int main();\n"
            "void/int main(int argc, string argv[]);\n"
            "void/int main(int argc, string argv[], string envp[]);\n");
}

static void check_main_prototype(struct symbol *main)
{
    int argc = type_function_argc(main->type);
    if (argc != 0 && argc != 2 && argc != 3) {
        display_main_proto();
        return;
    }


    const struct type *returnv = type_function_return(main->type);
    if (returnv != type_void && returnv != type_int) {
        display_main_proto();
        return;
    }

    const struct list *l = type_function_argv(main->type);
    const struct type *t1, *t2, *t3;
    switch (argc) {
        
    case 2:
        t1 = ((struct symbol*)list_get(l, 1))->type;
        t2 = ((struct symbol*)list_get(l, 2))->type;
        if (t1 != type_int) {
            display_main_proto();
            return;
        }
        if (!type_is_array(t2) || type_array_values(t2) != type_string) {
            display_main_proto();
            return;
        }

        
        break;

    case 3:
        t1 = ((struct symbol*)list_get(l, 1))->type;
        t2 = ((struct symbol*)list_get(l, 2))->type;
        t3 = ((struct symbol*)list_get(l, 2))->type;
        if (t1 != type_int) {
            display_main_proto();
            return;
        }
        if (!type_is_array(t3) || type_array_values(t3) != type_string) {
            display_main_proto();
            return;
        }
        if (!type_is_array(t3) || type_array_values(t3) != type_string) {
            display_main_proto();
            return;
        }
        break;
        
    default:
        break;
    }
}
