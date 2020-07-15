#ifndef BCC_DECLARATOR_H
#define BCC_DECLARATOR_H

#include <stdint.h>

struct declarator;

#include "./pointer.h"
#include "../expression/expression.h"
#include "../misc/initializer.h"
#include "../util/list.h"

/* Constructors for different kind of declarator */
struct declarator *declarator_identifier(const char *identifier);

struct declarator *declarator_pointer(struct declarator *base_declarator,
                                      struct pointer *ptr);

struct declarator *declarator_array(struct declarator *base_declarator,
                                    const struct expression *const_expr_array_size);

struct declarator *declarator_function(struct declarator *base_declarator,
                                       struct list *parameter_list);

struct declarator *declarator_function_old(struct declarator *base_declarator,
                                           struct list *identifier_list);

struct declarator *declarator_struct_field(struct declarator *base_declarator,
                                           const struct expression *const_expr_bitcount);

struct declarator *declarator_specifier(struct declarator *base_declarator,
                                        const struct list *declaration_specifiers);

struct declarator *declarator_initializer(struct declarator *base_declarator,
                                          struct initializer *initializer);

/* misc methods */

/* abstract declarator is declarator without symbol name
 * (for example in function prototype without name)
 * there is only a type a no name for this kind of declarator
 */
bool declarator_is_abstract(const struct declarator *decl);

const char *declarator_get_name(const struct declarator *decl);


/* declarator is a chained (nested) structure
 * this function is a recursive helper to compute the actual type of the declarator.
 * base_type is the type coming from the declaration_specifiers
 */
const struct type *declarator_type(const struct declarator *declarator,
                                   const struct type *base_type);

/* apply the declaration_specifiers to all the declarators in the declarator list
 * and transform the list of declarator (function argument list)
 * into a list of symbols (into -> ret_list)
 *
 * NOTE: this function ADD the symbol into the symbol table
 * it is meant to handle variable declaration at global scope or function scope
 * (BUT NOT FUNCTION PARAMETER LIST, use declarator_process_param_list for function parameters !!)
 */
int declarator_process_list(struct list *declaration_specifiers,
                            struct list *declarators,
                            struct list **ret_list);

/* transform the list of declarator (function argument list)
 * into a list of symbols (into -> ret_list)
 *
 * NOTE: this function DOES NOT ADD the symbol(s) into the symbol table !!!
 * it is meant to handle function argument, and add them in the symbol table
 * later, only when the symbol context for function is actually created
 * which is later due to yacc parsing order
 */
int declarator_process_param_list(struct list *declarator_list,
                                  struct list **ret_list);

const struct list *declarator_deepest_param_list(const struct declarator *declarator);





#endif // BCC_DECLARATOR_H
