#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <assert.h>

#include "expression.h"
#include "expression_codegen.h"

#include "../program.h"
#include "../codegen.h"

#include "../symbol/symbol.h"
#include "../type/type.h"
#include "../error/error.h"

static const char *
build_cmp_op(const struct type *t, const char *prefix)
{
    char *op;
    if (type_float == t)
        op = "cmp o";
    else
        op = "cmp s";
    asprintf(&op, "%s%s", op, prefix);
    return op;
}

static const char *
build_eq_op(const struct type *t, const char *prefix)
{
    char *op;
    if (type_float == t)
        op = "cmp o";
    else
        op = "cmp ";
    asprintf(&op, "%s%s", op, prefix);
    return op;
}

inline void expr_cg(const struct expression *e)
{
    if (error_count() > 0)
        return;
    e->codegen((struct expression *) e);        // ON PURPOSE UNCONSTING
}
// -- helpers -- >>

static char *new_register(void)
{
    char *reg;
    asprintf(&reg, "%%t%u", prgm_get_unique_id());
    return reg;
}

static void new_registers(int n, char *tab[])
{
    for (int i = 0; i < n; i++)
        tab[i] = new_register();
}

static void
expr_cg_operation(struct expression *e, const char *op, const char *prefix)
{
    expr_cg(e->left_operand);
    expr_cg(e->right_operand);

    e->vreg = new_register();
    asprintf(&e->vcode, "%s%s %s = %s%s %s %s, %s\n",
             e->left_operand->vcode, e->right_operand->vcode,
             e->vreg, prefix, op, type_cg(e->left_operand->type),
             e->left_operand->vreg, e->right_operand->vreg);
}

static void
expr_cg_xcrementimpl(struct expression *e, const char *op, char *reg)
{
    expr_cg(e->operand);

    const char *tstr = type_cg(e->type);
    asprintf(&e->vcode, "%s %s = %s i32 %s, 1\n"
             "store %s %s, %s* %s\n",
             e->operand->vcode, reg, op, e->operand->vreg,
             tstr, reg, tstr, e->operand->areg);
}

static void expr_cg_post_xcrement(struct expression *e, const char *op)
{
    char *tmpreg = new_register();
    expr_cg_xcrementimpl(e, op, tmpreg);
    e->vreg = e->operand->vreg;
}

static void expr_cg_pre_xcrement(struct expression *e, const char *op)
{
    e->vreg = new_register();
    expr_cg_xcrementimpl(e, op, e->vreg);
}

// << -- helpers end --

#define expr_cg_xcrement_case(EXPR_TYPE_, PP_, OPNAME_) \
    case EXPR_##EXPR_TYPE_:                             \
    expr_cg_##PP_##_xcrement(e, OPNAME_);               \
    break

void expr_cg_xcrement(struct expression *e)
{
    switch (e->expression_type) {
        expr_cg_xcrement_case(POST_INC, post, "add");   //x++
        expr_cg_xcrement_case(POST_DEC, post, "sub");   //x--
        expr_cg_xcrement_case(PRE_INC, pre, "add");     //++x
        expr_cg_xcrement_case(PRE_DEC, pre, "sub");     //--x
    default:
        internal_error("expr_cg_xcrement: default clause reached");
    }
}

#undef expr_cg_xcrement_case


#define expr_cg_xoperation_case(TYPE_, OPNAME_, PREFIX_)                \
    case EXPR_##TYPE_:                                                  \
    expr_cg_operation(e, OPNAME_, (t == type_float)?"f":PREFIX_);       \
    break

void expr_cg_xoperation(struct expression *e)
{
    const struct type *t = e->left_operand->type;
    switch (e->expression_type) {
        expr_cg_xoperation_case(MULTIPLICATION, "mul", "");
        expr_cg_xoperation_case(DIVISION, "div", "s");
        expr_cg_xoperation_case(ADDITION, "add", "");
        expr_cg_xoperation_case(SUBSTRACTION, "sub", "");
        expr_cg_xoperation_case(LOWER, build_cmp_op(t, "lt"), "i");
        expr_cg_xoperation_case(GREATER, build_cmp_op(t, "gt"), "i");
        expr_cg_xoperation_case(LEQ, build_cmp_op(t, "le"), "i");
        expr_cg_xoperation_case(GEQ, build_cmp_op(t, "ge"), "i");
        expr_cg_xoperation_case(NEQ, build_eq_op(t, "ne"), "i");
        expr_cg_xoperation_case(EQ, build_eq_op(t, "eq"), "i");

    default:
        internal_error("expr_cg_operation: default clause reached");
        break;
    }
}

#undef expr_cg_xoperation_case

void expr_cg_symbol(struct expression *e)
{
    e->vreg = new_register();
    asprintf(&e->vcode, "%s = load %s* %s\n", e->vreg,
             type_cg(e->type), e->areg);
}

void expr_cg_constant(struct expression *e)
{
    e->vreg = new_register();
    if (e->type == type_int)
        asprintf(&e->vcode, "%s = add i32 %d, 0\n", e->vreg,
                 e->constant->integer.intv.signed_);
    else if (e->type == type_float) {
        double tmp = (double) e->constant->floatv;
        asprintf(&e->vcode, "%s = fadd float %#018lx, 0.\n",
                 e->vreg, *(uint64_t *) (&tmp));
    } else if (e->type == type_long)
        asprintf(&e->vcode, "%s = add i64 %ld, 0\n", e->vreg,
                 e->constant->integer.longv.signed_);
}

void expr_cg_funcall(struct expression *e)
{
    char *params_code = "";
    char *params_val = "";
    char *call_code = "";

    int s = list_size(e->args);
    for (int i = 1; i <= s; ++i) {
        struct expression *arg;
        arg = list_get(e->args, i);
        expr_cg(arg);
        asprintf(&params_code, "%s%s", params_code, arg->vcode);
        asprintf(&params_val, "%s%s %s%s", params_val, type_cg(arg->type),
                 arg->vreg, i == s ? "" : ",");
    }

    asprintf(&call_code, "call %s @%s(%s)\n",
             type_cg(e->type), e->symbol->name, params_val);

    if (e->type != type_void) {
        e->vreg = new_register();
        asprintf(&call_code, "%s = %s", e->vreg, call_code);
    }

    asprintf(&e->vcode, "%s%s", params_code, call_code);
}

void expr_cg_array(struct expression *e)
{
    expr_cg(e->array);
    expr_cg(e->index);

    assert(e->array != e->index);

    e->vreg = new_register();
    e->areg = new_register();

    asprintf(&e->acode,
             "%s%s %s = getelementptr %s %s, i64 0, i32 1, %s %s\n",
             e->array->vcode, e->index->vcode, e->areg,
             type_cg(e->array->type), e->array->vreg,
             type_cg(e->index->type), e->index->vreg);

    asprintf(&e->vcode, "%s %s = load %s* %s\n",
             e->acode, e->vreg, type_cg(e->type), e->areg);
}

void expr_cg_unary_minus(struct expression *e)
{//TODO make expr_unary_minus return expresion_substraction(epxr_constant,
    //and eventually remove this function
    expr_cg(e->operand);
    e->vreg = new_register();
    asprintf(&e->vcode, "%s %s = sub %s 0, %s\n", e->operand->vcode,
             e->vreg, type_cg(e->operand->type), e->operand->vreg);
}

void expr_cg_assignment(struct expression *e)
{
    expr_cg(e->left_operand);
    expr_cg(e->right_operand);
    e->vreg = e->right_operand->vreg;

    if (e->left_operand->expression_type == EXPR_SYMBOL)
        assert(e->left_operand->symbol->type == type_generic ||
               e->left_operand->symbol->symbol_type == SYM_VARIABLE);

    const char *tstr = type_cg(e->left_operand->type);
    asprintf(&e->vcode, "%s%s store %s %s, %s* %s\n",
             e->left_operand->acode, e->right_operand->vcode,
             tstr, e->right_operand->vreg, tstr, e->left_operand->areg);
}

void expr_cg_fpsicast(struct expression *e)
{
    char *cast_instr = "unimplemented cast";

    if (e->operand->type == type_float && type_is_integer(e->target_type)) {
        cast_instr = "fptosi";
    } else if (type_is_integer(e->operand->type)
               && e->target_type == type_float) {
        cast_instr = "sitofp";
    }

    expr_cg(e->operand);
    e->vreg = new_register();
    asprintf(&e->vcode, "%s %s = %s %s %s to %s\n",
             e->operand->vcode, e->vreg, cast_instr,
             type_cg(e->operand->type), e->operand->vreg,
             type_cg(e->target_type));
}

void expr_cg_sizeof(struct expression *e)
{
    expr_cg(e->array);
    e->areg = new_register();
    e->vreg = new_register();
    asprintf(&e->acode, "%s %s = getelementptr %s %s, i64 0, i32 0\n",
	     e->array->vcode, e->areg, type_cg(e->array->type),
	     e->array->vreg);
    asprintf(&e->vcode, "%s %s = load i64* %s\n", e->acode, e->vreg, e->areg);
}

static void
expr_cg_constant_expression(struct expression *e, const char *opname)
{
    expr_cg(e->operand);
    e->vreg = new_register();
    asprintf(&e->vcode, "%s %s = %s %s %s to %s\n",
             e->operand->vcode, e->vreg, opname, type_cg(e->operand->type),
             e->operand->vreg, type_cg(e->target_type));
}

void expr_cg_bitcast(struct expression *e)
{
    expr_cg_constant_expression(e, "bitcast");
}

void expr_cg_sign_extend(struct expression *e)
{
    expr_cg_constant_expression(e, "sext");
}

void expr_cg_zero_extend(struct expression *e)
{
    expr_cg_constant_expression(e, "zext");
}

void expr_cg_trunc(struct expression *e)
{
    expr_cg_constant_expression(e, "trunc");
}
