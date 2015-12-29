#ifndef POINTER_H
#define POINTER_H

struct pointer;
#include "../symbol/symbol.h"
#include "../util/list.h"

struct pointer *pointer_new(struct list *qualifier_list,
                            struct pointer *subpointer);
struct list *pointer_get_qualifier_list(const struct pointer *p);
struct pointer *pointer_get_sub_pointer(const struct pointer *p);

#endif //POINTER_H
