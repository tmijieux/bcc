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
    error_set_program_name(argv[0]);
    parse_options(&argc, &argv, &bopt);
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
  
        err = compile_file(argv[i], &bopt);
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

int compile_file(const char *filename, struct bcc_option *bopt)
{
    int fstage, lstage;
    char *file_extension[2], *output_name;
    const char *ext;
    
    split_extension(filename, file_extension);
    fstage = first_stage_by_extension(file_extension[1]);
    lstage = last_stage_by_option(bopt);
    ext = extension_by_stage(lstage);
    asprintf(&output_name, "%s%s%s", basename(file_extension[0]),
             strlen(ext) > 0 ? "." : "", ext);
    return compile_chain(filename, output_name, fstage, lstage);
}
