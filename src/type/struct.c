#include "struct.h"
#include "../error/error.h"


struct symbol *struct_unnamed_field(const struct expression *const_expr)
{
    internal_warning("struct_unnamed_field not implemented");
    return symbol_generic();
}

struct symbol *struct_named_field(struct symbol *sym,
                                  const struct expression *const_expr)
{
    internal_warning("struct_named_field not implemented");
    return symbol_generic();
}
