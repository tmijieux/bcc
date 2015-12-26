#ifndef SPECIFIER_H
#define SPECIFIER_H

struct specifier;

enum specifier_type {
    SPEC_UNIMPLEMENTED = 0,
    
    SPEC_TYPE_VOID = 37,
    SPEC_TYPE_CHAR,
    SPEC_TYPE_SHORT,
    SPEC_TYPE_INT,
    SPEC_TYPE_LONG,
    SPEC_TYPE_FLOAT,
    SPEC_TYPE_DOUBLE,
    SPEC_TYPE_SIGNED,
    SPEC_TYPE_UNSIGNED,
    SPEC_TYPE_TYPENAME,

    SPEC_CONST,
    SPEC_VOLATILE,
    
    SPEC_TYPEDEF,
    SPEC_EXTERN,
    SPEC_STATIC,
    SPEC_AUTO,
    SPEC_REGISTER,
};


#include "../util/list.h"

struct specifier *specifier_new(enum specifier_type specifier_type);
struct specifier *specifier_typename(const char *typename);
const struct type *specifier_list_get_type(const struct list *specifiers);
int check_declaration_specifiers(struct list *declarator_specifiers);
    
#endif //SPECIFIER_H
