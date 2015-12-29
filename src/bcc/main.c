#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "option.h"
#include "util/error.h"

int compile_file(const char *filename, struct bcc_option *bopt);
int yyparse(void);
extern FILE *yyin;

char *yyfilename = NULL;

int main(int argc, char *argv[])
{
    struct bcc_option bopt ;//= { 0 };
    int err = 0;
    error_set_program_name(argv[0]);
    
    if (1 == argc) {
        internal_error("no input files\n");
        fprintf(stderr, "compilation terminated\n");
        exit(EXIT_FAILURE);
    }

    parse_options(&argc, argv, &bopt);
    int i = 1;
    while (i < argc) {
        FILE *input =  fopen(argv[i], "r");
        if (NULL == input) {
            perror(argv[i]);
            exit(EXIT_FAILURE);
        }
        
        char *mname = strdup(argv[i]);
        yyfilename = mname;
  
        err = 0;
        if (!err)
            ;
        else
            break;
        i++;
    }

    return err ? EXIT_FAILURE : EXIT_SUCCESS;
}
