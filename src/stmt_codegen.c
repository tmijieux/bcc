#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include "statement.h"
#include "program.h"
#include "symbol.h"
#include "codegen.h"
#include "color.h"
#include "error.h"

static const char *str_concat_list(const struct list *l,
				   const char *(*get_str__) (void *))
{
    if (!l)
	return "";
    int s = list_size(l);
    char *code = "";
    for (int i = 1; i <= s; ++i)
	asprintf(&code, "%s%s", code, get_str__(list_get(l, i)));
    return code;
}

static const char *stmt_get_code(void *st)
{
    ((struct statement *) st)->codegen(st);
    return ((struct statement *) st)->code;
}

static const char *symb_get_init_code(void *st)
{
    struct symbol *s = st;
//    printf("INITCODE %s INITCODE\n", s->variable.init_code);
    return s->variable.init_code;
}

const char *decl_init_list(const struct list *l)
{
    return str_concat_list(l, &symb_get_init_code);
}

/*******************/

void stmt_cg(const struct statement *st)
{
    if (error_count() > 0)
	return;
    st->codegen((struct statement *) st);
}

void stmt_cg_expression(struct statement *st)
{
    assert(NULL != st->expr);
    expr_cg(st->expr);
    st->code = st->expr->vcode;
}

void stmt_cg_compound(struct statement *st)
{
    asprintf(&st->code, "%s%s",
	     str_concat_list(st->decl_list, &symb_get_init_code),
	     str_concat_list(st->stmt_list, &stmt_get_code));
}

void stmt_cg_if(struct statement *st)
{
    unsigned int d = prgm_get_unique_id();
    expr_cg(st->if_cond);
    stmt_cg(st->then);
    asprintf(&st->code,
	     "br label %%cond%d\n" // end previous block with a br instruction
	     "cond%d:\n"
	     "%s"
	     "br i1 %s, label %%then%u, label %%end%u\n"
	     "then%u:\n"
	     "%s"
	     "br label %%end%u\n"
	     "end%u:\n",
	     d, d, st->if_cond->vcode,
	     st->if_cond->vreg, d, d, d, st->then->code, d, d);
}

void stmt_cg_if_else(struct statement *st)
{
    unsigned int d = prgm_get_unique_id();
    expr_cg(st->if_cond);
    stmt_cg(st->then);
    stmt_cg(st->eelse);
    asprintf(&st->code,
	     "br label %%cond%d\n"// end previous block with a br instruction
	     "cond%d:\n"
	     "%s"
	     "br i1 %s, label %%then%u, label %%else%u\n"
	     "then%u:\n"
	     "%s"
	     "br label %%end%u\n"
	     "else%u:\n"
	     "%s"
	     "br label %%end%u\n"
	     "end%u:\n",
	     d, d, st->if_cond->vcode,
	     st->if_cond->vreg, d, d,
	     d, st->then->code, d, d, st->eelse->code, d, d);
}

void stmt_cg_while(struct statement *st)
{
    unsigned int d = prgm_get_unique_id();
    expr_cg(st->loop_cond);
    stmt_cg(st->body);
    asprintf(&st->code,
	     "br label %%cond%d\n"// end previous block with a br instruction
	     "cond%d:\n"
	     "%s"
	     "br i1 %s, label %%loop%u, label %%end%u\n"
	     "loop%u:\n"
	     "%s"
	     "br label %%cond%u\n"
	     "end%u:\n",
	     d, d, st->loop_cond->vcode,
	     st->loop_cond->vreg, d, d, d, st->body->code, d, d);
}

void stmt_cg_do_while(struct statement *st)
{
    unsigned int d = prgm_get_unique_id();
    expr_cg(st->loop_cond);
    stmt_cg(st->body);
    asprintf(&st->code,
	     "br label %%start%d\n"
	     "start%u:\n"
	     "%s"
	     "%s"
	     "br i1 %s, label %%start%u, label %%end%u\n"
	     "end%u:\n",
	     d, d, st->body->code, st->loop_cond->vcode,
	     st->loop_cond->vreg, d, d, d);
}

void stmt_cg_return_void(struct statement *st)
{
    st->code = "ret void\n";
}

void stmt_cg_return(struct statement *st)
{
    expr_cg(st->expr);
    asprintf(&st->code, "%s ret %s %s\n", st->expr->vcode,
	     type_cg(st->expr->type), st->expr->vreg);
}
