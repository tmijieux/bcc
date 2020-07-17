#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../util/error.h"
#include "../magic.h"

#include "./declarator.h"
#include "./specifier.h"
#include "./errorc.h"

enum declarator_type {
    DECLARATOR_UNEXPECTED_ERROR = 0,
    DECLARATOR_IDENTIFIER = 58,
    DECLARATOR_ARRAY,
    DECLARATOR_POINTER,
    DECLARATOR_FUNCTION,
    DECLARATOR_FUNCTION_OLD, // old style
    DECLARATOR_STRUCT_FIELD,
    DECLARATOR_SPECIFIER,
    DECLARATOR_INITIALIZER,
};

struct declarator {
    magic_t magic;
    enum declarator_type declarator_type;

    const struct list *declaration_specifiers;

    union declarator_value {
        const char *identifier;
        const struct list *parameter_list;
        const struct list *identifier_list;
        struct pointer *pointer;
        const struct expression *const_expr_array_size;
        const struct expression *const_expr_bitcount;
        struct initializer *initializer;
    } value;

    const struct type *type;
    struct declarator *next;
};

static struct declarator *declarator_new(enum declarator_type dt,
                                         struct declarator *next)
{
    struct declarator *d = calloc(sizeof*d, 1);
    d->magic = MAGIC_DECLARATOR;
    d->declarator_type = dt;
    d->next = next;
    return d;
}

bool declarator_is_abstract(const struct declarator *de)
{
    return ((DECLARATOR_IDENTIFIER != de->declarator_type) &&
            (NULL == de->next));
}

struct declarator *
declarator_identifier(const char *identifier)
{
    struct declarator *d = declarator_new(DECLARATOR_IDENTIFIER, NULL);
    d->value.identifier = identifier;
    return d;
}

struct declarator *
declarator_pointer(struct declarator *de, struct pointer *ptr)
{
    struct declarator *d = declarator_new(DECLARATOR_POINTER, de);
    d->value.pointer = ptr;
    return d;
}

struct declarator *
declarator_array(struct declarator *de,
                 const struct expression *const_expr_array_size)
{
    struct declarator *d = declarator_new(DECLARATOR_ARRAY, de);
    d->value.const_expr_array_size = const_expr_array_size;
    return d;
}

struct declarator *
declarator_function(struct declarator *de, struct list *parameter_list)
{
    struct declarator *d = declarator_new(DECLARATOR_FUNCTION, de);
    d->value.parameter_list = parameter_list;
    return d;
}


struct declarator *
declarator_function_old(struct declarator *de, struct list *identifier_list)
{
    struct declarator *d = declarator_new(DECLARATOR_FUNCTION_OLD, de);
    d->value.identifier_list = identifier_list;
    return d;
}

struct declarator*
declarator_struct_field(struct declarator *de,
                        const struct expression *const_expr_bitcount)
{
    struct declarator *d = declarator_new(DECLARATOR_STRUCT_FIELD, de);
    d->value.const_expr_bitcount = const_expr_bitcount;
    return d;
}

struct declarator*
declarator_specifier(struct declarator *de,
                     const struct list *declaration_specifiers)
{
    struct declarator *d = declarator_new(DECLARATOR_SPECIFIER, de);
    d->declaration_specifiers = declaration_specifiers;
    return d;
}

struct declarator*
declarator_initializer(struct declarator *de,
                       struct initializer *initializer)
{
    struct declarator *d = declarator_new(DECLARATOR_INITIALIZER, de);
    d->value.initializer = initializer;
    return d;
}


const char *declarator_get_name(const struct declarator *de)
{

    while (de && DECLARATOR_IDENTIFIER != de->declarator_type)
        de = de->next;
    if (NULL == de)
        return "";
    return de->value.identifier;
}

struct decl2sym_args {
    const struct type *base_type;
    enum symbol_storage ssto;
};

static void *to_symbol_add_table__(void *list_elem, void *additional_arg)
{
    struct declarator *decl = list_elem;
    ASSERT_MAGIC(decl, MAGIC_DECLARATOR);

    struct decl2sym_args *args = additional_arg;
    enum symbol_type st;

    if (STO_TYPEDEF == args->ssto)
    {
        st = SYM_TYPENAME;
    }
    else
    {
        if (decl->declarator_type == DECLARATOR_ARRAY)
        {
            st = SYM_ARRAY;
        }
        else if (DECLARATOR_FUNCTION == decl->declarator_type)
        {
            st = SYM_FUNCTION;
        }
        else
        {
            st = SYM_VARIABLE;
        }
    }
    decl->type = declarator_type(decl, args->base_type);

    struct symbol *sym;
    sym = symbol_new(
        declarator_get_name(decl),
        st,
        decl->type,
        args->ssto
    );

    if (!st_add(sym))
    {
        error("symbol multiple definition: %s \n", sym->name);
    }
    return sym;
}

int declarator_process_list(struct list *declaration_specifiers,
                            struct list *declarators,
                            struct list **ret_list)
{
    const struct type *base_type;
    if (check_declaration_specifiers(declaration_specifiers) != 0)
    {
        base_type = type_generic;
    }
    else
    {
        base_type = specifier_list_get_type(declaration_specifiers);
    }

    unsigned s = list_size(declarators);
    for (unsigned i = 1 ; i <= s; ++i)
    {
        struct declarator *decl = list_get(declarators, i);
        decl->declaration_specifiers = declaration_specifiers;
    }

    struct decl2sym_args d2a;
    memset(&d2a, 0, sizeof d2a);

    d2a.base_type = base_type;
    d2a.ssto = specifier_list_get_storage_class(declaration_specifiers);

    *ret_list = list_map_r(declarators, &to_symbol_add_table__, &d2a);
    return 0;
}

static void *to_symbol_param__(void *list_elem)
{
    struct declarator *decl = list_elem;
    ASSERT_MAGIC(decl, MAGIC_DECLARATOR);

    assert(DECLARATOR_SPECIFIER == decl->declarator_type);
    struct symbol *sym = symbol_new(declarator_get_name(decl),
                                    SYM_VARIABLE,
                                    declarator_type(decl, NULL),
                                    STO_AUTO);

    sym->variable.is_parameter = true;
    return sym;
}

int declarator_process_param_list(struct list *declarator_list,
                                  struct list **ret_list)
{
    *ret_list = list_map(declarator_list, &to_symbol_param__);
    return 0;
}

const struct type *
declarator_type(const struct declarator *de, const struct type *base_type)
{
    if (de == NULL)
    {
        return base_type;
    }

    switch (de->declarator_type) {
    case DECLARATOR_IDENTIFIER:
        return base_type;
    case DECLARATOR_ARRAY:
        return declarator_type(
            de->next,
            type_get_array_type_reversed(
                base_type,
                de->value.const_expr_array_size
            )
        );
    case DECLARATOR_POINTER:
        return declarator_type(
            de->next,
            type_get_pointer_type(de->value.pointer, base_type));
    case DECLARATOR_FUNCTION:
        return declarator_type(
            de->next,
            type_get_function_type(base_type, de->value.parameter_list));
    case DECLARATOR_FUNCTION_OLD:
        internal_warning("old style function definition "
                         "currently not supported\n");
         return type_generic;
    case DECLARATOR_SPECIFIER:
        return declarator_type(
            de->next,
            specifier_list_get_type(de->declaration_specifiers));
    case DECLARATOR_INITIALIZER:
        return declarator_type(de->next, base_type);
    default:
        internal_warning("declarator_type: this case is not implemented\n");
        break;
    }
    return type_generic;
}

const struct list *
declarator_deepest_param_list(const struct declarator *de)
{
    if (NULL == de->next) {
        if (DECLARATOR_FUNCTION == de->declarator_type)
            return de->value.parameter_list;
        else
            return NULL;
    } else {
        const struct list *l = declarator_deepest_param_list(de->next);
        if (NULL == l) {
            if (DECLARATOR_FUNCTION == de->declarator_type)
                return de->value.parameter_list;
            else
                return NULL;
        } else {
            return l;
        }
    }
}
