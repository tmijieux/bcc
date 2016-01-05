#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "option.h"
#include "chain.h"
#include "util/error.h"

int compile_file(const char *filename, struct bcc_option *bopt);
void stat_files(int *argc, char **argv);

int yyparse(void);
extern FILE *yyin;

char *yyfilename = NULL;

int main(int argc, char **argv)
{
    struct bcc_option bopt = { 0 };
    int err = 0;

    bopt_init(&bopt);
    error_set_program_name(argv[0]);
    parse_options(&argc, &argv, &bopt);
    option_check(&bopt, argc-1);
    stat_files(&argc, argv);

    if (1 == argc)
        internal_fatal_error("no input files\ncompilation terminated.\n");
    
    int i = 1;
    while (i < argc) {
        FILE *input = fopen(argv[i], "r");
        if (NULL == input) {
            perror(argv[i]);
            exit(EXIT_FAILURE);
        }
        
        char *mname = strdup(argv[i]);
        yyfilename = mname;
        err = compile_chain(argv[i], &bopt);

        if (err)
            break;
        i++;
    }
    return err ? EXIT_FAILURE : EXIT_SUCCESS;
}

void stat_files(int *argc, char *argv[])
{
    for (int i = 1; i < *argc; ++i) {
        struct stat st;
        if (stat(argv[i], &st) < 0) {
            internal_error("%s: %s\n", argv[i], strerror(errno));
            char *tmp = argv[*argc-1];
            argv[*argc-1] = argv[i];
            argv[i] = tmp;
            --(*argc);
        }
    }
}
