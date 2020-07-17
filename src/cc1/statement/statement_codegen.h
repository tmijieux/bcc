#ifndef BCC_STATEMENT_CODEGEN_H
#define BCC_STATEMENT_CODEGEN_H

void stmt_cg_declaration(struct statement *st);
void stmt_cg_expression(struct statement *st);
void stmt_cg_compound(struct statement *st);
void stmt_cg_if(struct statement *st);
void stmt_cg_if_else(struct statement *st);
void stmt_cg_for(struct statement *st);
void stmt_cg_while(struct statement *st);
void stmt_cg_do_while(struct statement *st);
void stmt_cg_return_void(struct statement *st);
void stmt_cg_return(struct statement *st);

#endif // BCC_STATEMENT_CODEGEN_H
