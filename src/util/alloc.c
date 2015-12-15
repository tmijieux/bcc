#include <gc.h>
#include <stdlib.h>
#include <string.h>

#include "alloc.h"

void *gcmalloc(size_t size)
{
    return GC_MALLOC(size);
}

void gcfree(void *ptr)
{
    /* do nothing */
}

void *gccalloc(size_t nmemb, size_t size)
{
    void *ptr = GC_MALLOC(nmemb * size);
    memset(ptr, 0, nmemb * size);
    return ptr;
}

void *gcrealloc(void *ptr, size_t size)
{
    return GC_REALLOC(ptr, size);
}
