#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "function.h"
#include "symbol_table.h"
#include "program.h"
#include "module.h"

extern void yyparse();

extern FILE *yyin;
char *yyfilename = NULL;

int main(int argc, char *argv[])
{
    FILE *input = NULL;
    m = module_new("module0");
    st_init();

    if (argc == 2) {
	input = fopen(argv[1], "r");
	yyfilename = strdup(argv[1]);
	if (input) {
	    yyin = input;
	} else {
	    fprintf(stderr, "%s: Could not open %s\n", *argv, argv[1]);
	    return EXIT_FAILURE;
	}
    } else {
	yyfilename = *argv;
	internal_error("\nusage: %s sourcefile.u\n", argv[0]);
	return EXIT_FAILURE;
    }
    yyparse();
    fclose(input);

    int err = error_count();
    if (!err)
	module_print(m, stdout);

    free(yyfilename);

    return err ? EXIT_FAILURE : EXIT_SUCCESS;
}
