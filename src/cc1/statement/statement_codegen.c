#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "statement.h"
#include "../program.h"
#include "../codegen.h"
#include "../symbol/symbol.h"
#include "../util/error.h"
#include "../util/color.h"
#include "errorc.h"

static char *str_concat_list(const struct list *list,
                             const char *(*get_str__) (void *))
{
    if (!list)
    {
        return strdup("");
    }

    unsigned s = list_size(list);
    char *code = "";
    for (unsigned i = 1; i <= s; ++i)
    {
        asprintf(&code, "%s%s", code, get_str__(list_get(list, i)));
    }

    return code;
}

static const char *stmt_get_code(void *input)
{
    struct statement *stmt = input;
    ASSERT_MAGIC(stmt, MAGIC_STATEMENT);

    stmt->codegen(stmt);
    return stmt->code;
}

static const char *symb_get_init_code(void *st)
{
    struct symbol *sym = st;
    ASSERT_MAGIC(sym, MAGIC_SYMBOL);

    if (sym->variable.is_parameter)
    {
        return sym->variable.init_code;
    }
    return "";
}

const char *decl_init_list(const struct list *l)
{
    return str_concat_list(l, &symb_get_init_code);
}

/*******************/

void stmt_cg(const struct statement *st)
{
    if (error_count() > 0)
    {
        return;
    }
    st->codegen((struct statement *) st);
}

void stmt_cg_expression(struct statement *st)
{
    assert(NULL != st->expr);
    expr_cg(st->expr);
    st->code = st->expr->vcode;
}

void stmt_cg_declaration(struct statement *st)
{
    char *declaration = str_concat_list(st->symbol_list, &symb_get_init_code);
    st->code = declaration;
}

void stmt_cg_compound(struct statement *st)
{
    char *other_statement = str_concat_list(st->stmt_list, &stmt_get_code);
    st->code = other_statement;
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
