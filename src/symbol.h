#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdlib.h>
#include <stdint.h>

#include <list.h>

#include "type.h"

#define SYM_MAX_SIZE 16

enum symbol_type {
    SYM_VARIABLE,
    SYM_FUNCTION // no storage, always resolved at compile/link time
};

enum variable_storage {
    VAR_STATIC,
    VAR_AUTO
};

enum visibility {
    VSB_DEFAULT,
    VSB_HIDDEN,
    VSB_PROTECTED
};

enum linkage {
    LNK_PRIVATE,
    LNK_INTERNAL,
    LNK_AVAILABLE_EXTERNALLY,
    LNK_LINKONCE,
    LNK_WEAK,
    LNK_COMMON,
    LNK_APPENDING,
    LNK_EXTERN_WEAK,
    LNK_LINKONCE_ODR,
    LNK_WEAK_ODR,
    EXTERNAL
};

struct symbol_variable {
    int is_global;
    int is_parameter;
    int used;
    
    const char *alloc_code;
    const char *init_code;
    // for retrieving parameter value and
    // allocate the arrays

    int assigned_constant;
    enum enum_type constant_type;
    union {
	float valuef;
	float valuei;
    };
};

struct symbol_function {

};

struct symbol {
    const char *name;

    /**
       suffix is used to differentiate between
       generated code and user code   */
    const char *suffix;

    enum symbol_type symbol_type;
    const struct type *type;

    enum linkage linkage;
    enum visibility visibility;

    int level;
    int unique_id;

    size_t size;
    union {
	struct symbol_variable variable;
	struct symbol_function function;
    };
};

struct symbol *symbol_new(const char *name, const struct type *t);

// check a symbol is defined in the symbol_table and get it
// or return NULL if it is not defined
struct symbol *symbol_check(const char *name);

// symbol helpers
void symbol_print(const struct symbol *sy);
char *symbol_fully_qualified_name(const struct symbol *sym);
void symbol_use(struct symbol *sy);

#endif	//SYMBOL_H
