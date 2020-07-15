#ifndef BCC_UTIL_LIST_H
#define BCC_UTIL_LIST_H

#include <stdlib.h>
#include <assert.h>

// FLAGS for list_new():
#define LI_ELEM  (1 << 1)	// null terminated initializer list
#define LI_FREE  (1 << 2)	// second argument is a free function for elements
// END FLAGS

struct list;

// ! !
// NUMBERED FROM 1 !!!!!!!!
// ! !

struct list *list_new(int flags, ...);
void list_free(struct list*);
size_t list_size(const struct list*); // element count
void * list_get(const struct list*, unsigned int i); // returns data
void list_add(struct list*, const void*);
void list_insert(struct list*, unsigned int i, const void *data);
void list_remove(struct list*, unsigned int i);

void list_append(struct list *list, const void *element);
void list_append_list(struct list *l1, const struct list *l2);
struct list *list_copy(const struct list *l);
void *list_to_array(const struct list *l);
struct hash_table *list_to_hashtable(const struct list *l,
				     const char *(*element_keyname) (void *));
void list_each(const struct list *l, void (*fun)(void*));
void list_each_r(const struct list *l, void (*fun)(void*, void*), void *args);
struct list *list_map(const struct list *l, void *(*fun)(void*));
struct list *list_map_r(const struct list *l,
			void *(*fun)(void*, void*), void *args);

#endif // BCC_UTIL_LIST_H
