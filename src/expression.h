#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <stdbool.h>
#include "symbol.h"
#include "type.h"

enum expression_type {
    EXPR_SYMBOL,			       
    EXPR_CONSTANT,
    EXPR_UNARY_MINUS,	// -x
    EXPR_PRE_INC,	//  ++x
    EXPR_PRE_DEC,	//   --x
    EXPR_POST_INC,	//  x++
    EXPR_POST_DEC,	//  x--
    EXPR_POSTFIX,	// a[i]
    EXPR_ARRAY_SIZE,
    EXPR_MULTIPLICATION,
    EXPR_DIVISION,
    EXPR_ADDITION,
    EXPR_SUBSTRACTION,
    EXPR_LOWER,
    EXPR_GREATER,
    EXPR_LEQ,
    EXPR_GEQ,
    EXPR_EQ,
    EXPR_NEQ,
    EXPR_ASSIGNMENT,
    EXPR_MAP,
    EXPR_REDUCE,
    EXPR_FUNCALL,
    EXPR_FUNCALL_PARAMS,
    EXPR_FPSI_CAST,
    EXPR_BITCAST,
    EXPR_SIGN_EXTEND,
    EXPR_ZERO_EXTEND,
    EXPR_TRUNC,
    EXPR_UNDEF
};

struct expression {
    enum expression_type expression_type;
    const struct type *type;

    // sub-expression / composing expression:
    const struct expression *operand;
    const struct expression *left_operand;
    const struct expression *right_operand;
    const struct expression *fun;
    const struct expression *array;
    const struct expression *index;
    const struct list *args; // expression list for function calls

    bool constant;
    union {
	int constanti;
	float constantf;
	long constantl;
	struct symbol *symbol;
	const struct type *target_type;
    };

    char *vcode;// code for computing value
    char *vreg;	// register for value

    char *acode;// code for computing address
    char *areg;	// register for address

    char *source_code;

    void (*codegen) (struct expression *);
    // why c++ when you have c
};

bool is_not_zero_constant_expr(const struct expression *expr);

bool expr_is_test(const struct expression *e);
bool expr_is_operation(const struct expression *e);

const struct expression *expr_constant(const struct type *ty, ...);
const struct expression *expr_symbol(struct symbol *sym);	// var ref

const struct expression *expr_map(const struct expression *fun,
				  const struct expression *array);
const struct expression *expr_reduce(const struct expression *fun,
				     const struct expression *array);
const struct expression *expr_funcall(struct symbol *fun, struct list *args);
const struct expression *expr_postfix(const struct expression *array,
				      const struct expression *index);

// Unary ops
const struct expression *expr_unary_minus(const struct expression *op);
const struct expression *expr_post_dec(const struct expression *op);
const struct expression *expr_pre_dec(const struct expression *op);
const struct expression *expr_post_inc(const struct expression *op);
const struct expression *expr_pre_inc(const struct expression *op);

// Comparisons
const struct expression *expr_neq(const struct expression *lop,
				  const struct expression *rop);
const struct expression *expr_eq(const struct expression *lop,
				 const struct expression *rop);
const struct expression *expr_leq(const struct expression *lop,
				  const struct expression *rop);
const struct expression *expr_geq(const struct expression *lop,
				  const struct expression *rop);
const struct expression *expr_greater(const struct expression *lop,
				      const struct expression *rop);
const struct expression *expr_lower(const struct expression *lop,
				    const struct expression *rop);


// Basic operations
const struct expression *expr_addition(const struct expression *lop,
				       const struct expression *rop);
const struct expression *expr_substraction(const struct expression *lop,
					   const struct expression *rop);
const struct expression *expr_multiplication(const struct expression *lop,
					     const struct expression *rop);
const struct expression *expr_division(const struct expression *lop,
				       const struct expression *rop);

const struct expression *expr_assignment(const struct expression *lop,
					 const struct expression *rop);


// CASTS AND CO
const struct expression *expr_cast(const struct expression *op,
				   const struct type *target);
const struct expression *expr_bitcast(const struct expression *op,
				      const struct type *target);
const struct expression *expr_sign_extend(const struct expression *op,
					  const struct type *target);
const struct expression *expr_zero_extend(const struct expression *op,
					  const struct type *target);
const struct expression *expr_trunc(const struct expression *op,
				    const struct type *target);

const struct expression *expr_array_size(const struct expression *array);

#endif	//EXPRESSION_H
