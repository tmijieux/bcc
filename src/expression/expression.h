
#ifndef EXPRESSION_H
#define EXPRESSION_H

struct expression;

#include <stdbool.h>
#include "../module.h"
#include "../symbol/symbol.h"
#include "../type/type.h"
#include "../constant/constant.h"

enum expression_type {
    EXPR_VOID,
    EXPR_SYMBOL,
    EXPR_CONSTANT,
    EXPR_UNARY_MINUS,	// -x
    EXPR_PRE_INC,	//  ++x
    EXPR_PRE_DEC,	//   --x
    EXPR_POST_INC,	//  x++
    EXPR_POST_DEC,	//  x--
    EXPR_ARRAY,	// a[i]
    EXPR_SIZEOF,
    EXPR_MULTIPLICATION,
    EXPR_MODULO,
    EXPR_DIVISION,
    EXPR_ADDITION,
    EXPR_SUBSTRACTION,
    EXPR_LOWER,
    EXPR_GREATER,
    EXPR_LEQ,
    EXPR_GEQ,
    EXPR_EQ,
    EXPR_NEQ,
    EXPR_AND,
    EXPR_OR,
    EXPR_XOR,
    EXPR_LOGICAL_AND,
    EXPR_LOGICAL_OR,
    EXPR_SHR,
    EXPR_SHL,
    EXPR_ASSIGNMENT,
    EXPR_FUNCALL,
    EXPR_FPSI_CAST,
    EXPR_BITCAST,
    EXPR_SIGN_EXTEND,
    EXPR_ZERO_EXTEND,
    EXPR_TRUNC,
    EXPR_UNDEF,
    EXPR_GENERIC
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

//    bool constant;
    struct constant *constant;
    
    const struct type *target_type;
    const char *identifier;
    struct symbol *symbol;

    char *vcode;// code for computing value
    char *vreg;	// register for value

    char *acode;// code for computing address
    char *areg;	// register for address

    char *source_code;

    void (*codegen) (struct expression *);
    void (*check) (struct expression *);
    // why c++ when you have c
};

bool is_not_zero_constant_expr(const struct expression *expr);
bool expr_is_test(const struct expression *e);
bool expr_is_operation(const struct expression *e);

const struct expression *expr_constant(struct constant *cst);
const struct expression *expr_symbol(struct module *m, const char *identifier);

const struct expression *expr_map(const struct expression *fun,
				  const struct expression *array);
const struct expression *expr_reduce(const struct expression *fun,
				     const struct expression *array);
const struct expression *expr_funcall(const struct expression *fun,
                                      struct list *args);
const struct expression *expr_array(const struct expression *array,
		                    const struct expression *index);

const struct expression *
expr_struct_access(const struct expression *struct_,
                   const char *field_name);
const struct expression *
expr_struct_deref(const struct expression *struct_,
                  const char *field_name);



// Unary ops
const struct expression *expr_unary(char c, const struct expression *e);
const struct expression *expr_unary_minus(const struct expression *op);
const struct expression *expr_post_dec(const struct expression *op);
const struct expression *expr_pre_dec(const struct expression *op);
const struct expression *expr_post_inc(const struct expression *op);
const struct expression *expr_pre_inc(const struct expression *op);
const struct expression *expr_generic(void);

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
const struct expression *expr_modulo(const struct expression *lop,
                                     const struct expression *rop);
const struct expression *expr_shift_right(const struct expression *lop,
                                          const struct expression *rop);

const struct expression *expr_shift_left(const struct expression *lop,
                                         const struct expression *rop);

const struct expression *expr_and(const struct expression *lop,
                                  const struct expression *rop);
const struct expression *expr_or(const struct expression *lop,
                                 const struct expression *rop);
const struct expression *expr_xor(const struct expression *lop,
                                 const struct expression *rop);
const struct expression *expr_logical_and(const struct expression *lop,
                                          const struct expression *rop);
const struct expression *expr_logical_or(const struct expression *lop,
                                         const struct expression *rop);


const struct expression *expr_assignment(const struct expression *lop,
                                         char c,
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
const struct expression *expr_sizeof_expr(const struct expression *expr);
const struct expression *expr_sizeof_typename(const struct type *t);


const struct expression *expr_list(const struct expression *expr_list,
                                   const struct expression *expr);

extern const struct expression *void_expression;



#endif	//EXPRESSION_H
