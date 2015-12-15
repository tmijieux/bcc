#ifndef EXPR_CODEGEN_H
#define EXPR_CODEGEN_H

void expr_cg(const struct expression *);

void expr_cg_map(struct expression *e);
void expr_cg_reduce(struct expression *e);
void expr_cg_symbol(struct expression *e);
void expr_cg_constant(struct expression *e);
void expr_cg_funcall(struct expression *e);
void expr_cg_postfix(struct expression *e);
void expr_cg_unary_minus(struct expression *e);
void expr_cg_assignment(struct expression *e);
void expr_cg_fpsicast(struct expression *e);
void expr_cg_bitcast(struct expression *e);
void expr_cg_sign_extend(struct expression *e);
void expr_cg_zero_extend(struct expression *e);
void expr_cg_trunc(struct expression *e);
void expr_cg_array_size(struct expression *e);

void expr_cg_xcrement(struct expression *e);
void expr_cg_xoperation(struct expression *e);

#endif	//EXPR_CODEGEN_H
