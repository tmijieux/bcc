#include <stdio.h>
#include "list.h"
#include "program.h"
#include "error.h"

unsigned int prgm_get_unique_id(void)
{
    static unsigned int unique = 0;
    return unique++;
}
