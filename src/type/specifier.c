#include "specifier.h"
#include "../util/alloc.h"
#include "../type/type.h"
#include "../error/error.h"

struct specifier {
    enum specifier_type specifier_type;
};
    
struct specifier *specifier_new(enum specifier_type specifier_type)
{
    return calloc(sizeof*specifier_new, 1);
}

struct specifier *specifier_typename(const char *typename)
{
    return specifier_new(SPEC_TYPE_TYPENAME);
}

const struct type *specifier_list_get_type(const struct list *specifiers)
{
    internal_warning("specifier_list_get_type not implemented\n");
    return type_generic;
}
