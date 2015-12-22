#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <assert.h>

#include "expression.h"
#include "symbol.h"
#include "type.h"
#include "error.h"
#include "program.h"
#include "codegen.h"
#include "expr_codegen.h"
#include "string_literal.h"

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
    e->codegen((struct expression *) e);	// ON PURPOSE UNCONSTING
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

#define expr_cg_xcrement_case(EXPR_TYPE_, PP_, OPNAME_)	\
    case EXPR_##EXPR_TYPE_:				\
    expr_cg_##PP_##_xcrement(e, OPNAME_);		\
    break

void expr_cg_xcrement(struct expression *e)
{
    switch (e->expression_type) {
	expr_cg_xcrement_case(POST_INC, post, "add");	//x++
	expr_cg_xcrement_case(POST_DEC, post, "sub");	//x--
	expr_cg_xcrement_case(PRE_INC, pre, "add");	//++x
	expr_cg_xcrement_case(PRE_DEC, pre, "sub");	//--x
    default:
	internal_error("expr_cg_xcrement: default clause reached");
    }
}

#undef expr_cg_xcrement_case


#define expr_cg_xoperation_case(TYPE_, OPNAME_, PREFIX_)		\
    case EXPR_##TYPE_:							\
    expr_cg_operation(e, OPNAME_, (t == type_float)?"f":PREFIX_);	\
    break

void expr_cg_xoperation(struct expression *e)
{
    const struct type *t = e->left_operand->type;
    switch (e->expression_type) {
	expr_cg_xoperation_case(MULTIPLICATION, "mul", "");
	expr_cg_xoperation_case(DIVISION, "div", "s");
        expr_cg_xoperation_case(MODULO, "rem", "s");
	expr_cg_xoperation_case(ADDITION, "add", "");
	expr_cg_xoperation_case(SUBSTRACTION, "sub", "");
        expr_cg_xoperation_case(AND, "and", "");
        expr_cg_xoperation_case(OR, "or", "");
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

void expr_cg_map(struct expression *e)
{
    char *syname, *rettab;

    expr_cg(e->fun);
    expr_cg(e->array);

    const char *funtypestr = type_cg(e->fun->type);
    const char *paramarraytypestr = type_cg(e->array->type);
    const char *retarraytypestr = type_cg(e->type);

    char *reg[6];
    new_registers(6, reg);

    int d1, d2;
    d1 = prgm_get_unique_id();
    d2 = prgm_get_unique_id();

    // RETURN ARRAY:
    asprintf(&rettab, "map%u", d1);

    // printf("type map ret %s\n\n\n\n\n", type_printable(e->type));
    struct symbol *rettab_symb = symbol_new(rettab, e->type);
    rettab_symb->symbol_type = SYM_VARIABLE;
    rettab_symb->suffix = "mapcg";
    symb_cg(rettab_symb);

    // MAP ARGS:
    asprintf(&syname, "mapcont%u", d2);

    uint64_t mpc =				// map call type
	(type_size(e->array->type->array_type.values) == 4 ? 0L : 1L)
	+ 2 * (type_size(e->type->array_type.values) == 4 ? 0L : 1L);

    char *mapconttypestr;
    asprintf(&mapconttypestr, "{i64, %s, %s, %s}",
	     paramarraytypestr, retarraytypestr, funtypestr);

    char *mapcont_code;
    asprintf(&mapcont_code, "%%%s.mapcg = alloca %s\n"	// struct mapcont
	     "%s = getelementptr %s* %%%s.mapcg, i64 0, i32 0\n"
	     "store i64 %ld, i64* %s\n"	// set map_call_type
	     "%s" "%s = getelementptr %s* %%%s.mapcg, i64 0, i32 1\n"
	     "store %s %s, %s* %s\n"	// set param array
	     "%s = getelementptr %s* %%%s.mapcg, i64 0, i32 2\n"
	     "%s = load %s* %%%s.mapcg\n"
	     "store %s %s, %s* %s\n"// set return array
	     "%s = getelementptr %s* %%%s.mapcg, i64 0, i32 3\n"
	     "store %s @%s, %s* %s\n"	// set method
	     "%s = bitcast %s* %%%s.mapcg to i8*\n"
	     "call void @map(i8* %s)\n",	// call map
	     syname, mapconttypestr,	// struct mapcont
	     reg[0], mapconttypestr,
	     syname, mpc, reg[0],	// set map_call_type
	     e->array->vcode, reg[1], mapconttypestr, syname,
	     paramarraytypestr, e->array->vreg,
	     paramarraytypestr, reg[1],	// set param array
	     reg[2], mapconttypestr, syname, reg[4],
	     retarraytypestr, rettab, retarraytypestr, reg[4],
	     retarraytypestr, reg[2],	// set return array
	     reg[3], mapconttypestr, syname, funtypestr,
	     e->fun->symbol->name, funtypestr, reg[3],	// set method
	     reg[5], mapconttypestr, syname, reg[5]);	// call map

    symb_cg(rettab_symb);
    asprintf(&mapcont_code, "%s%s%s", rettab_symb->variable.alloc_code,
	     rettab_symb->variable.init_code, mapcont_code);
    e->vcode = mapcont_code;
    e->vreg = reg[4];
}

void expr_cg_reduce(struct expression *e)
{
    char *syname, *ret;

    expr_cg(e->fun);
    expr_cg(e->array);

    const char *funtypestr = type_cg(e->fun->type);
    const char *paramarraytypestr = type_cg(e->array->type);
    const char *rettypestr = type_cg(e->type);

    char *reg[6];
    new_registers(6, reg);
    int d1, d2;
    d1 = prgm_get_unique_id();
    d2 = prgm_get_unique_id();

    // RETURN ARRAY:
    asprintf(&ret, "redret%u", d1);
    struct symbol *ret_symb = symbol_new(ret, e->type);
    ret_symb->symbol_type = SYM_VARIABLE;
    ret_symb->suffix = "redcg";
    symb_cg(ret_symb);

    // MAP ARGS:
    asprintf(&syname, "redcont%u", d2);

    char *redconttypestr;
    asprintf(&redconttypestr, "{i64, %s, %s*, %s}",
	     paramarraytypestr, rettypestr, funtypestr);

    char *redcont_code;
    asprintf(&redcont_code, "%%%s.redcg = alloca %s\n"	// struct redcont
	     "%s = getelementptr %s* %%%s.redcg,"
	     " i64 0, i32 0\n" "store i64 %ld, i64* %s\n"// set red_call_type
	     "%s" "%s = getelementptr %s* %%%s.redcg,"
	     " i64 0, i32 1\n" "store %s %s, %s* %s\n"	// set param array
	     "%s = getelementptr %s* %%%s.redcg, i64 0, i32 2\n"
	     "store %s* %%%s.redcg, %s** %s\n"	// set return value
	     "%s = getelementptr %s* %%%s.redcg, i64 0, i32 3\n"
	     "store %s @%s, %s* %s\n"	// set method
	     "%s = bitcast %s* %%%s.redcg to i8*\n"
	     "call void @reduce(i8* %s)\n"	// call red
	     "%s = load %s* %%%s.redcg\n",	//retval
	     syname, redconttypestr,	// struct redcont
	     reg[0], redconttypestr, syname,
	     type_size(e->array->type->array_type.values) == 4 ? 0L : 1L,
	     reg[0],	// set red_call_type
	     e->array->vcode, reg[1], redconttypestr, syname,
	     paramarraytypestr, e->array->vreg,
	     paramarraytypestr, reg[1],	// set param array
	     reg[2], redconttypestr, syname, rettypestr,
	     ret, rettypestr, reg[2],	// set return value
	     reg[3], redconttypestr, syname, funtypestr,
	     e->fun->symbol->name, funtypestr, reg[3],	// set method
	     reg[5], redconttypestr, syname, reg[5],	// call red
	     reg[4], rettypestr, ret);	//retval

    asprintf(&redcont_code, "%s%s%s", ret_symb->variable.alloc_code,
	     ret_symb->variable.init_code, redcont_code);

    e->vcode = redcont_code;
    e->vreg = reg[4];
}

void expr_cg_array_size(struct expression *e)
{
    expr_cg(e->array);
    e->areg = new_register();
    e->vreg = new_register();
    asprintf(&e->acode, "%s %s = getelementptr %s %s, i64 0, i32 0\n",
	     e->array->vcode, e->areg, type_cg(e->array->type),
	     e->array->vreg);
    asprintf(&e->vcode, "%s %s = load i64* %s\n", e->acode, e->vreg, e->areg);
}

void expr_cg_symbol(struct expression *e)
{
    e->vreg = new_register();
    asprintf(&e->vcode, "%s = load %s* %s\n", e->vreg,
	     type_cg(e->type), e->areg);
}

void expr_cg_constant(struct expression *e)
{
    e->vreg = new_register();
    if (e->type == type_int) {
	asprintf(&e->vcode, "%s = add i32 %d, 0\n", e->vreg, e->constanti);
    } else if (e->type == type_float) {
	double tmp = (double) e->constantf;
	asprintf(&e->vcode, "%s = fadd float %#018lx, 0.\n",
		 e->vreg, *(uint64_t *) (&tmp));
    } else if (e->type == type_long) {
	asprintf(&e->vcode, "%s = add i64 %ld, 0\n", e->vreg, e->constantl);
    } else if (e->type == type_string) {
        struct literal *lit = string_get_or_create_literal(e->constantstr);
        asprintf(&e->vcode, "%s = bitcast [%zu x i8]* %s to i8*\n", e->vreg,
                 lit->length, lit->reg);
    } else {
        internal_error("%s: %d", __FILE__, __LINE__);
    }
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

void expr_cg_postfix(struct expression *e)
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
    char *cast_instr = "unimplemented";

    if (e->operand->type == type_float && type_is_integer(e->target_type)) {
	cast_instr = "fptosi";
    } else if (type_is_integer(e->operand->type)
	       && e->target_type == type_float) {
	cast_instr = "sitofp";
    }  else if (type_string == e->operand->type 
                && e->target_type == type_int) {
	cast_instr = "ptrtoint";
    }

    expr_cg(e->operand);
    e->vreg = new_register();
    asprintf(&e->vcode, "%s %s = %s %s %s to %s\n",
	     e->operand->vcode, e->vreg, cast_instr,
	     type_cg(e->operand->type), e->operand->vreg,
	     type_cg(e->target_type));
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
