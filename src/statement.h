#ifndef STATEMENT_H
#define STATEMENT_H

#include "list.h"
#include "expression.h"

enum statement_type {
    STMT_COMPOUND,
    STMT_EXPR,
    STMT_SELECTION,
    STMT_ITERATION,
    STMT_JUMP
};

struct statement {
    enum statement_type statement_type;
    void (*codegen) (struct statement *);
    char *code;

    union {
	struct {
	    const struct list *decl_list;	// for compound
	    const struct list *stmt_list;	// for compound
	};

	const struct expression *expr;	// return / expression statement
	struct {
	    const struct expression *if_cond;	// if
	    const struct statement *then;
	    const struct statement *eelse;
	};
	struct {
	    const struct expression *init;	// loops
	    const struct expression *loop_cond;
	    const struct expression *next;
	    const struct statement *body;
	};
    };
};
// symbol list
const char *decl_init_list(const struct list *decl_list);
struct statement *stmt_expression(const struct expression *expr);

struct statement *stmt_compound(const struct list *decl,
				const struct list *stmts);

struct statement *stmt_if(const struct expression *cond,
			  const struct statement *then);

struct statement *stmt_if_else(const struct expression *cond,
			       const struct statement *then,
			       const struct statement *eelse);

struct statement *stmt_for(const struct expression *init,
			   const struct expression *cond,
			   const struct expression *next,
			   const struct statement *body);

struct statement *stmt_while(const struct expression *cond,
			     const struct statement *body);

struct statement *stmt_do_while(const struct expression *cond,
				const struct statement *body);

struct statement *stmt_return_void(void);
struct statement *stmt_return(const struct expression *expr);

#endif	//STATEMENT_H
