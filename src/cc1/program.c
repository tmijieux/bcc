#include <stdio.h>

#include "program.h"
#include "util/list.h"
#include "util/error.h"

unsigned int prgm_get_unique_id(void)
{
    static unsigned int unique = 0;
    return unique++;
}
