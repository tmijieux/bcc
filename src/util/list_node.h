#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <stdlib.h>

struct list_node {
    const void *data;
    struct list_node *next;
    int is_sentinel;
};

#define SENTINEL_NODE 1
#define DATA_NODE     0

#define node_new(da, sen)						\
    ({ struct list_node *n = (struct list_node*) malloc(sizeof(*n));	\
	n->data = (da);							\
	n->is_sentinel = (sen);						\
	n;})
#define node_free(no)	       (free(no))
#define node_get_next(no)      ((no)->next)
#define node_set_next(no, ne)  ((no)->next = (ne))
#define node_get_data(no)      ((no)->data)
#define node_set_data(no, da)  ((no)->data = (da))
#define node_is_sentinel(no)   ((no)->is_sentinel)

#endif	//LIST_NODE_H
