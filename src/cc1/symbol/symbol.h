#ifndef BCC_SYMBOL_H
#define BCC_SYMBOL_H

struct symbol;

#include <stdlib.h>
#include <stdint.h>

#include "symbol_table.h"
#include "../type/type.h"

#define SYM_MAX_SIZE 16

enum symbol_type {
    SYM_UNDEF,
    SYM_VARIABLE = 12,
    SYM_FUNCTION,
    SYM_ARRAY,
    SYM_TYPENAME,
};

enum symbol_storage {
    STO_UNDEF,
    STO_AUTO= 42,
    STO_STATIC,
    STO_TYPEDEF,
    STO_EXTERN,
    STO_REGISTER,
};

enum symbol_visibility {
    VSB_DEFAULT,
    VSB_HIDDEN,
    VSB_PROTECTED,
};

enum symbol_linkage {
    SLNK_DO_NOT_APPLY,
    SLNK_PRIVATE,
    SLNK_INTERNAL,
    SLNK_AVAILABLE_EXTERNALLY,
    SLNK_LINKONCE,
    SLNK_WEAK,
    SLNK_COMMON,
    SLNK_APPENDING,
    SLNK_EXTERN_WEAK,
    SLNK_LINKONCE_ODR,
    SLNK_WEAK_ODR,
    SLNK_EXTERNAL,
};

struct symbol_variable {
    const char *alloc_code;
    bool is_parameter;
    const char *init_code; /* for retrieving parameter value */
};

struct symbol_function {

};

struct symbol_typename {
    const struct type *type;
};

struct symbol {
    enum symbol_type symbol_type;
    union {
	struct symbol_variable variable;
	struct symbol_function function;
        struct symbol_typename typename;
    };
    enum symbol_linkage linkage;
    enum symbol_visibility visibility;
    enum symbol_storage storage;

    const char *name;
    const char *suffix;
    /** suffix is used to differentiate between
       generated code and user code ...   */

    const struct type *type;

    unsigned int scope_level;
    int unique_id;
    size_t size;
    bool used;
    bool in_table;
};

struct symbol *symbol_new(const char *name,
                          enum symbol_type symbol_type,
                          const struct type *t,
                          enum symbol_storage ssto);

struct symbol *symbol_generic(const char *name);
void symbol_notice_use(struct symbol *sy);
char *symbol_fully_qualified_name(const struct symbol *sym);
const char *symbol_get_name(const struct symbol *sy);
const struct type *symbol_get_type(const struct symbol *sy);
bool symbol_is_variable(const struct symbol *sy);
bool symbol_is_array(const struct symbol *sy);
bool symbol_is_function(const struct symbol *sy);
bool symbol_is_typename(const struct symbol *sy);
bool symbol_is_global(const struct symbol *sy);
bool symbol_used(const struct symbol *sy);
void symbol_debug_print(const struct symbol *sy);


#endif // BCC_SYMBOL_H
