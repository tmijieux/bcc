#include "pointer.h"
#include "../util/error.h"

struct pointer {
    struct list *qualifier_list;
    struct pointer *subpointer;
};

struct pointer *
pointer_new(struct list *qualifier_list, struct pointer *subpointer)
{
    struct pointer *p = calloc(sizeof*p, 1);
    p->qualifier_list = qualifier_list;
    p->subpointer = subpointer;
    return p;
}

struct list *pointer_get_qualifier_list(const struct pointer *p)
{
    return p->qualifier_list;
}

struct pointer *pointer_get_sub_pointer(const struct pointer *p)
{
    return p->subpointer;
}
