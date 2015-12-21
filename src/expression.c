#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "expression.h"
#include "error.h"
#include "color.h"
#include "expr_codegen.h"
#include "string_literal.h"

static struct expression *expr_new(enum expression_type ext)
{
    struct expression *expr = calloc(sizeof(*expr), 1);
    expr->expression_type = ext;
    expr->vcode = expr->acode = expr->vreg = expr->areg =
	expr->source_code = "";
    return expr;
}

bool is_not_zero_constant_expr(const struct expression * expr)
{
    if (expr->expression_type == EXPR_CONSTANT) {
	if (expr->type == type_int && expr->constanti == 0)
	    return false;
	if (expr->type == type_long && expr->constantl == 0)
	    return false;
    }
    return true;
}

bool expr_is_test(const struct expression * e)
{
    return ((e->expression_type == EXPR_EQ) ||
	    (e->expression_type == EXPR_NEQ) ||
	    (e->expression_type == EXPR_LEQ) ||
	    (e->expression_type == EXPR_GEQ) ||
	    (e->expression_type == EXPR_LOWER) ||
	    (e->expression_type == EXPR_GREATER));
}

bool expr_is_operation(const struct expression * e)
{
    return ((e->expression_type == EXPR_ADDITION) ||
	    (e->expression_type == EXPR_SUBSTRACTION) ||
	    (e->expression_type == EXPR_MULTIPLICATION) ||
	    (e->expression_type == EXPR_DIVISION));

}

static void cast_to_greatest_precision(struct expression *expr)
{
    if (type_precision(expr->left_operand->type) >
	type_precision(expr->right_operand->type)) {
	expr->right_operand = expr_cast(expr->right_operand,
					expr->left_operand->type);
    } else if (type_precision(expr->left_operand->type) <
	       type_precision(expr->right_operand->type)) {
	expr->left_operand = expr_cast(expr->left_operand,
				       expr->right_operand->type);
    }
}

const struct expression *expr_symbol(struct symbol *sym)
{
    struct expression *expr = expr_new(EXPR_SYMBOL);

    expr->type = sym->type;
    expr->symbol = sym;
    symbol_use(sym);
    expr->codegen = &expr_cg_symbol;
    expr->areg = symbol_fully_qualified_name(sym);

    return expr;
}

const struct expression *expr_constant(const struct type *ty, ...)
{
    va_list ap;
    va_start(ap, ty);

    struct expression *expr = expr_new(EXPR_CONSTANT);
    expr->type = ty;

    if (expr->type == type_int) {
	expr->constanti = va_arg(ap, int);
    } else if (expr->type == type_float) {
	expr->constantf = (float) va_arg(ap, double);
	// there can't be a float in va_arg
    } else if (expr->type == type_long) {
	expr->constantl = va_arg(ap, long);
    } else if (expr->type == type_string) {
        expr->constantstr = va_arg(ap, char*);
        string_get_or_create_literal(expr->constantstr);
    } else {
	debug("%s\n", type_printable(ty));
	internal_error("unexpected parse error %s:%d\n", __FILE__, __LINE__);
    }

    va_end(ap);
    expr->codegen = &expr_cg_constant;
    return expr;
}

const struct expression *expr_map(const struct expression *fun,
				  const struct expression *array)
{
    bool valid_op_F = false, valid_op_A = false;

    struct expression *expr = expr_new(EXPR_MAP);
    expr->fun = fun;
    expr->array = array;

    int trigger_error =
	(fun->type != type_generic && array->type != type_generic);

    if (trigger_error && !type_is_function(fun->type)) {
	error("first operand to map operator" " must be a function.\n");
    } else {
	if (trigger_error && type_function_argc(fun->type) != 1) {
	    if (trigger_error)
		error("map first operand should"
		      " take exactly one parameter.\n");
	} else if (trigger_error) {
	    valid_op_F = true;
	}
    }

    if (trigger_error && !type_is_array(array->type)) {
	error("second operand to map operator" " must be an array.\n");
    } else if (trigger_error) {
	valid_op_A = true;
    }

    if (valid_op_F && valid_op_A) {
	struct symbol *tmp;
	// the function 1st (and last) argument
	tmp = list_get(type_function_argv(fun->type), 1);
	const struct type *ty = tmp->type;	// its type

	if (!type_equal(ty, type_array_values(array->type))) {
	    // must be the same as the array values
	    error("map operands: type mismatch\n");
	}
	expr->type = type_new_array_type(type_function_return(fun->type),
					 expr_array_size(array)
					 /*type_array_size( array->type )*/);
    } else {
	expr->type = type_generic;
    }

    expr->codegen = &expr_cg_map;
    return expr;
}

const struct expression *expr_reduce(const struct expression *fun,
				     const struct expression *array)
{
    bool valid_op_F = false, valid_op_A = false;

    struct expression *expr = expr_new(EXPR_REDUCE);
    expr->fun = fun;
    expr->array = array;

    if (!type_is_function(fun->type)) {
	error("First operand to reduce operator must be" " a function.\n");
    } else {
	if (type_function_argc(fun->type) != 2) {
	    error("reduce first operand should take exactly "
		  "two parameters.\n");
	} else {
	    valid_op_F = true;
	}
    }

    if (!type_is_array(array->type)) {
	error("Second operand to reduce operator must be an array.\n");
    } else {
	valid_op_A = 1;
    }

    if (valid_op_A && valid_op_F) {
	struct symbol *sy1, *sy2;
	const struct type *ty1, *ty2;
	const struct list *argv = type_function_argv(fun->type);

	sy1 = list_get(argv, 1);
	ty1 = sy1->type;

	sy2 = list_get(argv, 2);
	ty2 = sy2->type;

	if (!type_equal(ty1, ty2)) {
	    error("reduce first operand: invalid parameters\n");
	}

	if (!type_equal(ty1, type_array_values(array->type))) {
	    error("reduce operands: type mismatch\n");
	}

	expr->type = type_function_return(fun->type);
    } else {
	expr->type = type_generic;
    }
    expr->codegen = &expr_cg_reduce;
    return expr;
}

const struct expression *expr_funcall(struct symbol *fun, struct list *args)
{
    struct expression *expr = expr_new(EXPR_FUNCALL);
    expr->codegen = &expr_cg_funcall;
    expr->args = args;
    expr->symbol = fun;

    assert(args != NULL);

    if (!type_is_function(fun->type)) {
	fatal_error("'%s' is not a function.\n", fun->name);
	expr->type = type_generic;
	return expr;
    }

    const struct list *proto = type_function_argv(fun->type);
    unsigned int s = list_size(proto);

    expr->type = type_function_return(fun->type);

    if (list_size(args) != s) {
	error("%s: illegal number of arguments.\n", fun->name);
	return expr;
    }

    for (unsigned int i = 1; i <= s; ++i) {
	struct symbol *tmp = list_get(proto, i);
	const struct type *tparg = tmp->type;	// type in definition

	struct expression *tmp2 = list_get(args, i);
	const struct type *targ = tmp2->type;	// type given

	if (!type_equal(tparg, targ)) {
	    error("%s(): argument %d has invalid type.\n"
		  "expected %s %s %s %s\n", fun->name, i,
		  color("green", type_printable(tparg)),
		  color("light blue", "but"),
		  color("yellow", type_printable(targ)),
		  color("light blue", "was given."));
	}
    }

    return expr;
}

const struct expression *expr_postfix(const struct expression *array,
				      const struct expression *index)
{
    struct expression *expr = expr_new(EXPR_POSTFIX);

    expr->array = array;
    expr->index = index;

    if (!type_is_array(array->type) && array->type != type_generic) {
	error("There must be an array prior to []\n");
	expr->type = type_generic;
    } else {
	expr->type = type_array_values(array->type);
    }

    if (index->type != type_int && index->type != type_generic) {
	error("array index must be an integer\n");
    }

    expr->codegen = &expr_cg_postfix;
    return expr;
}

const struct expression *expr_unary_minus(const struct expression *op)
{
    struct expression *expr = expr_new(EXPR_UNARY_MINUS);

    expr->operand = op;
    expr->type = op->type;

    if (expr->type != type_int &&
	expr->type != type_float && expr->type != type_generic) {
	error("unary minus does not apply to type %s\n",
	      color("yellow", type_printable(expr->type)));
	expr->type = type_generic;
    }

    expr->codegen = &expr_cg_unary_minus;
    return expr;
}

// factorization for all increments and decrements:
static const struct expression *xcrement(enum expression_type et,
					 const struct expression *op,
					 const char *opname)
{
    struct expression *expr = expr_new(et);

    expr->operand = op;
    expr->type = op->type;
    expr->symbol = op->symbol;

    if (op->expression_type != EXPR_POSTFIX &&
	op->expression_type != EXPR_SYMBOL) {
	error("%s cannot be applied\nto non left"
	      " value '%s'\n", opname,
	      color("green", expr->operand->source_code));
	expr->type = type_generic;
	return expr;
    }

    if (expr->type != type_int && expr->type != type_generic) {
	error("cannot %s on type %s\n", opname,
	      color("yellow", type_printable(expr->type)));
	expr->type = type_generic;
	return expr;
    }
    expr->codegen = &expr_cg_xcrement;
    return expr;
}

const struct expression *expr_post_dec(const const struct expression *op)
{
    return xcrement(EXPR_POST_DEC, op, "decrement");
}

const struct expression *expr_pre_dec(const const struct expression *op)
{
    return xcrement(EXPR_PRE_DEC, op, "decrement");
}

const struct expression *expr_post_inc(const const struct expression *op)
{
    return xcrement(EXPR_POST_INC, op, "increment");
}

const struct expression *expr_pre_inc(const const struct expression *op)
{
    return xcrement(EXPR_PRE_INC, op, "increment");
}

//factorization for all basic operations
static const struct expression *operation(enum expression_type et,
					  const char *opname,
					  const struct expression *lop,
					  const struct expression *rop)
{
    struct expression *expr = expr_new(et);

    expr->left_operand = lop;
    expr->right_operand = rop;
    assert(lop != rop);

    if (!(type_is_basic(lop->type) && type_is_basic(rop->type))) {
	error("%s impossible: have %s %s %s\n", opname,
	      color("yellow", type_printable(lop->type)),
	      color("light blue", "and"),
	      color("yellow", type_printable(rop->type)));

	expr->type = type_generic;
	return expr;
    }

    if (expr_is_test(lop))
	lop = expr->left_operand = expr_zero_extend(lop, type_int);

    if (expr_is_test(rop))
	rop = expr->right_operand = expr_zero_extend(rop, type_int);

    if (!type_equal(lop->type, rop->type)) {
	cast_to_greatest_precision(expr);
	lop = expr->left_operand;
	rop = expr->right_operand;
    }

    if (expr_is_test(expr)) {
	expr->type = type_bool;
    } else { // expression is an operation
	expr->type = lop->type;
    }

    expr->codegen = &expr_cg_xoperation;
    return expr;
}

const struct expression *expr_neq(const const struct expression *lop,
				  const struct expression *rop)
{
    return operation(EXPR_NEQ, "comparison", lop, rop);
}

const struct expression *expr_eq(const struct expression *lop,
				 const struct expression *rop)
{
    return operation(EXPR_EQ, "comparison", lop, rop);
}

const struct expression *expr_leq(const struct expression *lop,
				  const struct expression *rop)
{
    return operation(EXPR_LEQ, "comparison", lop, rop);
}

const struct expression *expr_geq(const struct expression *lop,
				  const struct expression *rop)
{
    return operation(EXPR_GEQ, "comparison", lop, rop);
}

const struct expression *expr_greater(const struct expression *lop,
				      const struct expression *rop)
{
    return operation(EXPR_GREATER, "comparison", lop, rop);
}

const struct expression *expr_lower(const struct expression *lop,
				    const struct expression *rop)
{
    return operation(EXPR_LOWER, "comparison", lop, rop);
}

const struct expression *expr_addition(const struct expression *lop,
				       const struct expression *rop)
{
    return operation(EXPR_ADDITION, "addition", lop, rop);
}

const struct expression *expr_substraction(const struct expression *lop,
					   const struct expression *rop)
{
    return operation(EXPR_SUBSTRACTION, "substraction", lop, rop);
}

const struct expression *expr_multiplication(const struct expression *lop,
					     const struct expression *rop)
{
    return operation(EXPR_MULTIPLICATION, "multiplication", lop, rop);
}

const struct expression *expr_modulo(const struct expression *lop,
                                     const struct expression *rop)
{
    if (!(type_is_integer(lop->type) && type_is_integer(rop->type))) {
        error("modulo require both operands to be og integer type\n");
        struct expression *expr = expr_new(EXPR_MODULO);
        expr->type = type_generic;
        return expr;
    }

    return operation(EXPR_MODULO, "mod", lop, rop);
}

const struct expression *expr_division(const struct expression *lop,
				       const struct expression *rop)
{
    return operation(EXPR_DIVISION, "division", lop, rop);
}

const struct expression *expr_and(const struct expression *lop,
                                  const struct expression *rop)
{
    const struct expression *zero = expr_constant(type_int, 0);
    return operation(EXPR_AND, "and",
                     operation(EXPR_NEQ, "zero test", lop, zero),
                     operation(EXPR_NEQ, "zero test", rop, zero));
}

const struct expression *expr_or(const struct expression *lop,
                                  const struct expression *rop)
{
    const struct expression *zero = expr_constant(type_int, 0);
    return operation(EXPR_OR, "or",
                     operation(EXPR_NEQ, "zero test", lop, zero),
                     operation(EXPR_NEQ, "zero test", rop, zero));
}

const struct expression *expr_assignment(const struct expression *lop,
					 const struct expression *rop)
{
    struct expression *expr = expr_new(EXPR_ASSIGNMENT);
    expr->left_operand = lop;
    expr->right_operand = rop;

    if (expr_is_test(rop))
	rop = expr->right_operand = expr_zero_extend(rop, type_int);

    if (!type_equal(lop->type, rop->type)) {
	if (type_is_basic(lop->type) && type_is_basic(rop->type)) {
	    warning("assignment makes an implicit cast\n");
	    rop = expr->right_operand = expr_cast(rop, lop->type);
	} else {
	    error("assignment: type mismatch\n");
	    expr->type = type_generic;
	    return expr;
	}
    }
    expr->type = lop->type;

    switch (lop->expression_type) {
    case EXPR_SYMBOL:
    case EXPR_POSTFIX:
    case EXPR_ARRAY_SIZE:
	// nothing
	break;
    default:
	error("assignment: invalid left value\n");
	expr->type = type_generic;
	break;
    }
    expr->codegen = &expr_cg_assignment;
    return expr;
}

static struct expression *generic_cast_builder(enum expression_type et,
					       const struct expression *op,
					       const struct type *target)
{
    struct expression *expr = expr_new(et);

    expr->operand = op;
    expr->target_type = target;
    expr->type = target;
    return expr;
}

const struct expression *expr_fpsicast(const struct expression *op,
				       const struct type *target)
{
    struct expression *e;
    e = generic_cast_builder(EXPR_FPSI_CAST, op, target);
    e->codegen = &expr_cg_fpsicast;
    return e;
}

// generic cast operator
const struct expression *expr_cast(const struct expression *op,
				   const struct type *target)
{
    if (type_is_integer(op->type) && type_is_integer(target)) {
	if (type_precision(target) > type_precision(op->type))
	    return expr_zero_extend(op, target);
	// I think this should be sign_extend here instead of zero_extend
	// TODO --> check that
	else
	    return expr_trunc(op, target);
    }

    return expr_fpsicast(op, target);
}

const struct expression *expr_bitcast(const struct expression *op,
				      const struct type *target)
{
    struct expression *e;
    e = generic_cast_builder(EXPR_BITCAST, op, target);
    e->codegen = &expr_cg_bitcast;
    return e;
}

const struct expression *expr_sign_extend(const struct expression *op,
					  const struct type *target)
{
    struct expression *e;
    assert(type_is_integer(target));
    e = generic_cast_builder(EXPR_SIGN_EXTEND, op, target);
    e->codegen = &expr_cg_sign_extend;
    return e;
}

const struct expression *expr_zero_extend(const struct expression *op,
					  const struct type *target)
{
    struct expression *e;
    assert(type_is_integer(target));
    e = generic_cast_builder(EXPR_ZERO_EXTEND, op, target);
    e->codegen = &expr_cg_zero_extend;
    return e;
}

const struct expression *expr_trunc(const struct expression *op,
				    const struct type *target)
{
    struct expression *e;
    assert(type_is_integer(target));
    e = generic_cast_builder(EXPR_TRUNC, op, target);
    e->codegen = &expr_cg_trunc;
    return e;
}

const struct expression *expr_array_size(const struct expression *array)
{
    struct expression *expr = expr_new(EXPR_ARRAY_SIZE);
    if (!type_is_array(array->type)) {
	error("size operator can only be applied on arrays\n");

	expr->type = type_generic;
	return expr;
    }

    expr->type = type_long;
    expr->array = array;
    expr->codegen = &expr_cg_array_size;
    return expr;
}

const struct expression *expr_unary(char c, const struct expression *e)
{
    switch (c) {
    case '-':
        return expr_unary_minus(e);
        break;
        
    default:
        internal_error("unary operator '%c' not implemented", c);
        break;
    }

    return expr_generic();
}

const struct expression *expr_generic(void)
{
    struct expression *expr = expr_new(EXPR_GENERIC);
    expr->type = type_generic;
    return expr;
}
