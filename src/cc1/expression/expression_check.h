#ifndef BCC_EXPRESSION_CHECK_H
#define BCC_EXPRESSION_CHECK_H

void expr_ck(const struct expression *);

void expr_ck_symbol(struct expression *e);
void expr_ck_constant(struct expression *e);
void expr_ck_funcall(struct expression *e);
void expr_ck_array(struct expression *e);
void expr_ck_sizeof(struct expression *e);
void expr_ck_unary_minus(struct expression *e);
void expr_ck_assignment(struct expression *e);
void expr_ck_fpsicast(struct expression *e);
void expr_ck_bitcast(struct expression *e);
void expr_ck_sign_extend(struct expression *e);
void expr_ck_zero_extend(struct expression *e);
void expr_ck_trunc(struct expression *e);

void expr_ck_xcrement(struct expression *e);
void expr_ck_xoperation(struct expression *e);

#endif // BCC_EXPRESSION_CHECK_H
