#ifndef STRUCT_H
#define STRUCT_H

#include "../symbol/symbol.h"
#include "../expression/expression.h"

struct symbol *struct_unnamed_field(const struct expression *const_expr);
struct symbol *struct_named_field(struct symbol *sym,
                                  const struct expression *const_expr);

#endif //STRUCT_H
