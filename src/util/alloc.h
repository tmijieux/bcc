#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

void *gcmalloc(size_t size);
void gcfree(void *ptr);
void *gccalloc(size_t nmemb, size_t size);
void *gcrealloc(void *ptr, size_t size);

#endif	//ALLOC_H
