#ifndef BCC_UTIL_ALLOC_H
#define BCC_UTIL_ALLOC_H

#include <stdlib.h>

void *gcmalloc(size_t size);
void gcfree(void *ptr);
void *gccalloc(size_t nmemb, size_t size);
void *gcrealloc(void *ptr, size_t size);

#endif // BCC_UTIL_ALLOC_H
