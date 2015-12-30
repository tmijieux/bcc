#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"
#include "module.h"
#include "function.h"

#include "symbol/symbol_table.h"
#include "util/error.h"
#include "errorc.h"

int yyparse(void);
extern FILE *yyin;

char *yyfilename = "<stdin>";

int main(int argc, char *argv[])
{
    int err = 0;
    error_set_program_name(argv[0]);

    st_init();
    m = module_new(yyfilename);
    yyin = stdin;
    yyparse();
    
    err = error_count();
    if (!err)
        module_print(m, stdout);
    return err ? EXIT_FAILURE : EXIT_SUCCESS;
}
