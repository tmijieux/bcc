#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "expression.h"
#include "expression_codegen.h"
#include "../constant/string_literal.h"
#include "../util/error.h"
#include "../util/color.h"

extern struct module *m; // FIXME

bool expr_ck_symbol(struct expression *e)
{
    assert( EXPR_SYMBOL == e->expression_type );
    
    e->symbol = stable_get(module_get_symbol_table(m), e->identifier);
    e->type = e->symbol->type;

    symbol_use(e->symbol);
    
    if (type_generic == e->type)
        return false;
    return true;
}

bool expr_ck_constant(struct expression *cst)
{
    return true;
}

bool expr_ck_funcall(struct expression *e)
{
    assert(e->args != NULL);

    if (!type_is_function(e->fun->type)) {
	fatal_error("'%s' is not a function.\n", e->fun->source_code);
	e->type = type_generic;
	return false;
    }

    const struct list *proto = type_function_argv(e->fun->type);
    unsigned int s = list_size(proto);

    e->type = type_function_return(e->fun->type);

    if (list_size(e->args) != s) {
	error("%s: illegal number of arguments.\n", e->fun->source_code);
        return false;
    }

    for (unsigned int i = 1; i <= s; ++i) {
	struct symbol *tmp = list_get(proto, i);
	const struct type *tparg = tmp->type;	// type in definition

	struct expression *tmp2 = list_get(e->args, i);
	const struct type *targ = tmp2->type;	// type given

	if (!type_equal(tparg, targ)) {
	    error("%s(): argument %d has invalid type.\n"
		  "expected %s %s %s %s\n", e->fun->source_code, i,
		  color("green", type_printable(tparg)),
		  color("light blue", "but"),
		  color("yellow", type_printable(targ)),
		  color("light blue", "was given."));
	}
    }

    return true;
}

const struct expression *expr_ck_array(const struct expression *array,
                                       const struct expression *index)
{
    struct expression *expr = expr_new(EXPR_ARRAY);

    e->array = array;
    e->index = index;

    if (!type_is_array(array->type) && array->type != type_generic) {
	error("There must be an array prior to []\n");
	e->type = type_generic;
    } else {
	e->type = type_array_values(array->type);
    }

    if (index->type != type_int && index->type != type_generic) {
	error("array index must be an integer\n");
    }

    e->codegen = &expr_cg_array;
    return expr;
}

const struct expression *expr_ck_unary_minus(struct expression *op)
{
    struct expression *expr = expr_new(EXPR_UNARY_MINUS);

    e->operand = op;
    e->type = op->type;

    if (e->type != type_int &&
	e->type != type_float && e->type != type_generic) {
	error("unary minus does not apply to type %s\n",
	      color("yellow", type_printable(e->type)));
	e->type = type_generic;
    }

    e->codegen = &expr_cg_unary_minus;
    return expr;
}

// factorization for all increments and decrements:
static const struct expression *xcrement(enum expression_type et,
					 const struct expression *op,
					 const char *opname)
{
    struct expression *expr = expr_new(et);

    e->operand = op;
    e->type = op->type;
    e->symbol = op->symbol;

    if (op->expression_type != EXPR_ARRAY &&
	op->expression_type != EXPR_SYMBOL) {
	error("%s cannot be applied\nto non left"
	      " value '%s'\n", opname,
	      color("green", e->operand->source_code));
	e->type = type_generic;
	return expr;
    }

    if (e->type != type_int && e->type != type_generic) {
	error("cannot %s on type %s\n", opname,
	      color("yellow", type_printable(e->type)));
	e->type = type_generic;
	return expr;
    }
    e->codegen = &expr_cg_xcrement;
    return expr;
}

const struct expression *expr_ck_post_dec( struct expression *op)
{
    return xcrement(EXPR_POST_DEC, op, "decrement");
}

const struct expression *expr_ck_pre_dec( struct expression *op)
{
    return xcrement(EXPR_PRE_DEC, op, "decrement");
}

const struct expression *expr_ck_post_inc( struct expression *op)
{
    return xcrement(EXPR_POST_INC, op, "increment");
}

const struct expression *expr_ck_pre_inc( struct expression *op)
{
    return xcrement(EXPR_PRE_INC, op, "increment");
}

//factorization for all basic operations
bool ck_operation(enum expression_type et,
                  const char *opname,
                  const struct expression *lop,
                  const struct expression *rop)
{

    e->left_operand = lop;
    e->right_operand = rop;
    assert(lop != rop);

    if (!(type_is_basic(lop->type) && type_is_basic(rop->type))) {
	error("%s impossible: have %s %s %s\n", opname,
	      color("yellow", type_printable(lop->type)),
	      color("light blue", "and"),
	      color("yellow", type_printable(rop->type)));

	e->type = type_generic;
	return expr;
    }

    if (expr_is_test(lop))
	lop = e->left_operand = expr_zero_extend(lop, type_int);

    if (expr_is_test(rop))
	rop = e->right_operand = expr_zero_extend(rop, type_int);

    if (!type_equal(lop->type, rop->type)) {
	cast_to_greatest_precision(expr);
	lop = e->left_operand;
	rop = e->right_operand;
    }

    if (expr_is_test(expr)) {
	e->type = type_bool;
    } else { // expression is an operation
	e->type = lop->type;
    }

    return true;
}

const struct expression *expr_neq(const const struct expression *lop,
				  const struct expression *rop)
{

}

const struct expression *expr_eq(const struct expression *lop,
				 const struct expression *rop)
{

}

bool
expr_ck_leq(struct expression *e)
{
    return true;
}

bool
expr_ck_geq(struct expression *e);
            
{
    return true;
}

bool
expr_greater(struct expression *e);
{
    return true;
}

bool
expr_ck_lower(struct expression *e)
{
    return true;
}

bool expr_ck_addition(struct expression *e)
{
    return true;
}

bool expr_ck_substraction(struct expression *e)
{
    return true;
}

bool expr_ck_multiplication(struct expression *e)
{
    return true;
}

bool
expr_ck_modulo(struct expression *e)
{
    if (!(type_is_integer(lop->type) && type_is_integer(rop->type))) {
        error("modulo require both operands to be of integer type\n");
        struct expression *expr = expr_new(EXPR_MODULO);
        e->type = type_generic;
        return false;
    }

    return true;
}

bool
expr_ck_shift_left(const struct expression *e)
{
    if (!(type_is_integer(lop->type) && type_is_integer(rop->type))) {
        error("modulo require both operands to be of integer type\n");
        struct expression *expr = expr_new(EXPR_MODULO);
        e->type = type_generic;
        return false;
    }

    return true;
}

bool
expr_ck_shift_right(struct expression *e)
{
    return true;
}

bool
expr_ck_division(struct expression *e)
{
    return true;
}

bool expr_ck_and(struct expression *e)
{
    return true;
}

bool expr_ck_logical_and(struct expression *e)
{
    return true;
}

bool expr_ck_or(const struct expression *e)
{
    return true;
}

bool expr_ck_xor(struct expression *e)
{
    return true;
}


bool expr_logical_or(struct expression *e)
{
    return true;
}


bool expr_ck_assignment(struct expression *e)
{
    return true;
}

static struct expression *generic_cast_builder(enum expression_type et,
					       const struct expression *op,
					       const struct type *target)
{
    return true;
}

bool expr_ck_fpsicast(struct expression *e)
{
    return true;
}

// generic cast operator
bool expr_ck_cast(const struct expression *op,
                  const struct type *target)
{
    return true;
}

bool expr_ck_bitcast(const struct expression *op,
                     const struct type *target)
{
    return true;
}

bool expr_ck_sign_extend(const struct expression *op,
                         const struct type *target)
{
    return true;
}

bool expr_ck_zero_extend(const struct expression *op,
                         const struct type *target)
{
    return true;
}

bool expr_ck_trunc(const struct expression *op,
                   const struct type *target)
{
    return true;
}

bool expr_ck_unary(char c, const struct expression *e)
{
    return true;
}

bool expr_ck_generic(void)
{
    return true;
}

bool expr_ck_sizeof_expr(const struct expression *array)
{
    return true;
}


bool expr_ck_sizeof_typename(struct expression *e)
{
    return true;
}

bool
expr_ck_struct_access(struct expression *e)
{
    return true;
}

bool
expr_ck_struct_deref(struct expression *e)
{
    return true;
}

bool
expr_ck_list(struct expression *e)
{
    return true;
}
