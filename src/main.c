#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "error.h"
#include "function.h"
#include "symbol_table.h"
#include "program.h"
#include "module.h"
#include "option.h"
#include "scanner.h"
#include "grammar.h"

char *yyfilename = NULL;

int main(int argc, char *argv[])
{
    struct bcc_option bopt;
    FILE *input = NULL;
    int err = 0;

    parse_options(&argc, argv, &bopt);

    for (int i = 1; NULL != argv[i]; ++i) {
        input = fopen(argv[i], "r");
        if (NULL != input) {
            int err;
            
            yyin = input;
            yyfilename = strdup(argv[i]);
            m = module_new(yyfilename);
            
            st_init();
            yyparse();
            st_exit();
            
            err &= error_count();
            if (!err)
                module_print(m, stdout);

            free(yyfilename);
            fclose(input);
        } else {
            fprintf(stderr, "%s: error: %s: %s\n", *argv, argv[1], strerror(errno));
            exit(EXIT_FAILURE);
        }

        i++;
    }
    
    return err ? EXIT_FAILURE : EXIT_SUCCESS;
}
