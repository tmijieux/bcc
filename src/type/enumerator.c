#include "enumerator.h"


#include "../error/error.h"

struct enumerator *enumerator_new(const char *name, bool have_value,
                                  const struct expression *const_expr)
{
    internal_warning("enumerator_new not implemented");
    return calloc(sizeof*enumerator_new, 1);
}
