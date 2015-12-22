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

#include "stmt_codegen.h"

/**** Helpers *************/

static inline const struct expression *
to_boolean(const struct expression *cond)
{
    if (!expr_is_test(cond)) {
	const struct expression *zero = expr_constant(type_int, 0);
	cond = expr_neq(cond, zero);
    }

    return cond;
}

/*******************/

static struct statement *stmt_new(enum statement_type st)
{
    struct statement *stmt = calloc(sizeof *stmt, 1);
    stmt->code = "";
    stmt->statement_type = st;
    return stmt;
}

struct statement *stmt_expression(const struct expression *expr)
{
    struct statement *stmt = stmt_new(STMT_EXPR);
    stmt->expr = expr;
    stmt->codegen = &stmt_cg_expression;
    return stmt;
}

struct statement *stmt_compound(const struct list *decl,
				const struct list *stmts)
{
    struct statement *stmt = stmt_new(STMT_COMPOUND);
    stmt->decl_list = decl;
    stmt->stmt_list = stmts;
    stmt->codegen = &stmt_cg_compound;
    return stmt;
}

struct statement *stmt_if(const struct expression *cond,
			  const struct statement *then)
{
    struct statement *stmt = stmt_new(STMT_SELECTION);
    cond = to_boolean(cond);
    stmt->if_cond = cond;
    stmt->then = then;
    stmt->codegen = &stmt_cg_if;
    return stmt;
}

struct statement *stmt_if_else(const struct expression *cond,
			       const struct statement *then,
			       const struct statement *eelse)
{
    struct statement *stmt = stmt_new(STMT_SELECTION);
    cond = to_boolean(cond);
    stmt->if_cond = cond;
    stmt->then = then;
    stmt->eelse = eelse;
    stmt->codegen = &stmt_cg_if_else;
    return stmt;
}

struct statement *stmt_for(const struct expression *init,
			   const struct expression *cond,
			   const struct expression *next,
			   const struct statement *body)
{
    body = stmt_compound(NULL,
			 list_new(LI_ELEM, body, stmt_expression(next), NULL));
    struct list *li = list_new(LI_ELEM, stmt_expression(init),
			       stmt_while(to_boolean(cond), body), NULL);
    return stmt_compound(list_new(0), li);
}

struct statement *stmt_while(const struct expression *cond,
			     const struct statement *body)
{
    struct statement *stmt = stmt_new(STMT_ITERATION);
    cond = to_boolean(cond);
    stmt->loop_cond = cond;
    stmt->body = body;
    stmt->codegen = &stmt_cg_while;
    return stmt;
}

struct statement *stmt_do_while(const struct expression *cond,
				const struct statement *body)
{
    struct statement *stmt = stmt_new(STMT_ITERATION);
    cond = to_boolean(cond);
    stmt->loop_cond = cond;
    stmt->body = body;
    stmt->codegen = &stmt_cg_do_while;
    return stmt;
}

struct statement *stmt_return_void(void)
{
    struct statement *stmt = stmt_new(STMT_JUMP);
    if (last_function_return_type != type_void) {
	error("return value can't be void. expected %s\n",
	      color("yellow", type_printable(last_function_return_type)));
    }
    stmt->codegen = &stmt_cg_return_void;
    return stmt;
}

struct statement *stmt_return(const struct expression *expr)
{
    struct statement *stmt = stmt_new(STMT_JUMP);

    if (last_function_return_type == type_void) {
	error("returning non void value\n");
    } else if (!type_equal(last_function_return_type, expr->type)) {
	if (type_is_basic(last_function_return_type) &&
	    type_is_basic(expr->type)) {
	    warning("return statement makes an implicit cast\n");
	    expr = expr_cast(expr, last_function_return_type);
	} else {
	    error("returning type %s %s %s %s",
		  color("yellow", type_printable(expr->type)),
		  color("light blue", "while"),
		  color("green",
			type_printable(last_function_return_type)),
		  color("light blue", "was expected.\n"));
	}
    }

    stmt->expr = expr;
    stmt->codegen = &stmt_cg_return;
    return stmt;
}
