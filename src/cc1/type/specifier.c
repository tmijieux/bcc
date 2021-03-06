#include "specifier.h"
#include "../util/alloc.h"
#include "../type/type.h"
#include "../util/error.h"

struct specifier {
    enum specifier_type specifier_type;
    const struct type *typename_type;
};

struct specifier *specifier_new(enum specifier_type specifier_type)
{
    struct specifier *s = calloc(sizeof*specifier_new, 1);
    s->specifier_type = specifier_type;
    return s;
}

struct specifier *specifier_typename(const struct type *typename)
{
    struct specifier *sp = specifier_new(SPEC_TYPE_TYPENAME);
    sp->typename_type = typename;
    return sp;
}

enum symbol_storage
specifier_list_get_storage_class(const struct list *specifiers)
{
    int si = list_size(specifiers);
    for (int i = 1; i <= si; ++i) {
        struct specifier *sp = list_get(specifiers, i);
        switch (sp->specifier_type) {
        case SPEC_TYPEDEF:
            return STO_TYPEDEF;
            break;
        case SPEC_EXTERN:
            return STO_EXTERN;
            break;
        case SPEC_STATIC:
            return STO_STATIC;
            break;
        case SPEC_AUTO:
            return STO_AUTO;
            break;
        case SPEC_REGISTER:
            return STO_REGISTER;
            break;
        default:
//            debug("specifier value: %d\n", sp->specifier_type);
            continue;
            break;
        }
    }
    if (st_global_context())
        return STO_STATIC;
    return STO_AUTO;
}

const struct type *specifier_list_get_type(const struct list *specifiers)
{
    int si = list_size(specifiers);
//    debug("specifier list size: %d\n", si);
    for (int i = 1; i <= si; ++i) {
        struct specifier *sp = list_get(specifiers, i);
        switch (sp->specifier_type) {
        case SPEC_TYPE_VOID:
            return type_void;
            break;
        case SPEC_TYPE_CHAR:
            return type_char;
            break;
        case SPEC_TYPE_SHORT:
            return type_short;
            break;
        case SPEC_TYPE_INT:
            return type_int;
            break;
        case SPEC_TYPE_LONG:
            return type_long;
            break;
        case SPEC_TYPE_FLOAT:
            return type_float;
            break;
        case SPEC_TYPE_DOUBLE:
            return type_double;
            break;
        case SPEC_TYPE_TYPENAME:
            return sp->typename_type;
            break;
        default:
//            debug("specifier value: %d\n", sp->specifier_type);
            continue;
            break;
        }
    }
    internal_warning("specifier_list_get_type not implemented\n");
    return type_generic;
}

int check_declaration_specifiers(struct list *declarator_specifiers)
{
    // check non - abstract ?
    internal_warning("check_declaration_specifiers not implemented\n");
    return 0;
}
