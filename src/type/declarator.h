#ifndef DECLARATOR_H
#define DECLARATOR_H

struct declarator;

#include <stdint.h>
#include "pointer.h"
#include "../expression/expression.h"
#include "../misc/initializer.h"
#include "../util/list.h"

struct declarator *
declarator_identifier(const char *identifier);
struct declarator *
declarator_pointer(struct declarator *de, struct pointer *ptr);
struct declarator *
declarator_array(struct declarator *de,
                 const struct expression *const_expr_array_size);

struct declarator *
declarator_function(struct declarator *de, struct list *parameter_list);
struct declarator *
declarator_function_old(struct declarator *de, struct list *identifier_list);

struct declarator*
declarator_struct_field(struct declarator *de,
                        const struct expression *const_expr_bitcount);
struct declarator*
declarator_specifier(struct declarator *de,
                     const struct list *declaration_specifiers);
struct declarator*
declarator_initializer(struct declarator *de,
                       struct initializer *initializer);

bool
declarator_is_abstract(const struct declarator *de);

const char *
declarator_get_name(const struct declarator *de);

int
check_declaration_specifiers(struct list *declarator_specifiers);

struct symbol *
declarator_to_symbol(struct declarator *declarator,
                     const struct type *base_type);
    
int
declarator_process_list(struct list *declaration_specifiers,
                        struct list *declarator,
                        struct list **ret_list);

const struct type *
declarator_type(const struct declarator *de, const struct type *base_type);

#endif //DECLARATOR_H
