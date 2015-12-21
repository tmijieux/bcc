#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"
#include "symbol.h"
#include "program.h"
#include "statement.h"
#include "function.h"

static const struct statement *
st_array_alloc_rec(const struct expression *array, int depth);

void symb_cg(struct symbol *sy)
{
    const char *typestr = type_cg(sy->type);
    char *init_code;

    asprintf(&init_code, "%s = alloca %s%s\n", symbol_fully_qualified_name(sy),
	     typestr, sy->type->type == TYPE_ARRAY ? ", align 8" : "");
    sy->variable.alloc_code = init_code;

    if (sy->variable.is_parameter) {
	asprintf(&init_code,
		 "store %s %%%s.%s, %s* %s\n",
		 typestr, sy->name, "param",
		 typestr, symbol_fully_qualified_name(sy));
//	printf("PARAMETER %s INITCODE//:%s\n", sy->name, init_code);
	sy->variable.init_code = init_code;
    } else {  // symbol is a variable but not a parameter
	if (type_is_array(sy->type) &&
	    is_not_zero_constant_expr(type_array_size(sy->type))) {
	    const struct expression *array = expr_symbol(sy);
	    const struct statement *array_init = st_array_alloc_rec(array, 0);

	    stmt_cg(array_init);
	    sy->variable.init_code = array_init->code;
	}
    }
}

// cette fonction est RECURSIVE (dans le compilateur)
// mais genere des boucles imbriqués (iteratives) dans le programme généré
// pour allouer les tableaux à dimensions multiples
static const struct statement *
st_array_alloc_rec(const struct expression *array, int depth)
{
    struct symbol *fun_sy, *loop_counter_sy, *fun_arg_sy;
    const struct expression *assign_expr, *postfix;
    const struct expression *funcall_param, *arr_memsize, *constant;
    const struct expression *init, *comp, *pre_inc, *loop_counter_expr;
    const struct expression *bitcast;
    struct statement *for_stmt, *assign_stmt;
    const struct type *type, *malloc_type;
    struct list *l, *instr;

    instr = list_new(0);
    type = array->type;

    // =  GC_malloc( SIZE_OF_ARRAY );

    l = list_new(0);
    fun_arg_sy = symbol_new("size", type_long);
    fun_arg_sy->symbol_type = SYM_VARIABLE;
    
    list_append(l, fun_arg_sy);	// prototype for GC_malloc
    malloc_type = type_new_function_type(type_generic, l);

    fun_sy = symbol_new("GC_malloc", malloc_type);
    fun_sy->symbol_type = SYM_FUNCTION;
    
    l = list_new(0);

    const struct expression *mul =
	expr_multiplication(type->array_type.array_size,
			    expr_constant(type_long,
					  type_size(type_array_values(type))));

    arr_memsize = expr_addition(expr_constant(type_long, 8), mul);

    list_append(l, arr_memsize);
    funcall_param = expr_funcall(fun_sy, l);
    bitcast = expr_bitcast(funcall_param, array->type);
    assign_expr = expr_assignment(array, bitcast);
    assign_stmt = stmt_expression(assign_expr);

    list_append(instr, assign_stmt);

    const struct expression *transfer_size =
	expr_assignment(expr_array_size(array),
			type_array_size(array->type));
    const struct statement *transfer_size_stmt =
	stmt_expression(transfer_size);

    list_append(instr, transfer_size_stmt);

    if (type_is_array(type_array_values(type))
	&& is_not_zero_constant_expr(type_array_size(type_array_values(type)))) {
	char *name;
	asprintf(&name, "i%d", depth);
	loop_counter_sy = symbol_new(name, type_int);
	loop_counter_sy->symbol_type = SYM_VARIABLE;
	loop_counter_sy->suffix = "alloc_gen";
	symb_cg(loop_counter_sy);
	fun_add_allocas(current_fun, loop_counter_sy);

	// i = 0
	loop_counter_expr = expr_symbol(loop_counter_sy);
	constant = expr_constant(type_int, 0);
	init = expr_assignment(loop_counter_expr, constant);

	// i < array_size
	// change that to variable when needed

	loop_counter_expr = expr_symbol(loop_counter_sy);
	comp = expr_lower(loop_counter_expr, type_array_size(type));

	// ++i
	loop_counter_expr = expr_symbol(loop_counter_sy);
	pre_inc = expr_pre_inc(loop_counter_expr);

	loop_counter_expr = expr_symbol(loop_counter_sy);
	postfix = expr_postfix(array, loop_counter_expr);

	for_stmt = stmt_for(init, comp, pre_inc,
			    st_array_alloc_rec(postfix, depth + 1));

	list_append(instr, for_stmt);
    }
    return stmt_compound(NULL, instr);
}
