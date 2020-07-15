#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "util/error.h"
#include "chain.h"


#define MAX_ARGS 128
#define NEVER_REACHED -42
#define ARRAY_SIZE(X) (sizeof(X)/sizeof(X[0]))



struct {
    enum c_compil_stage ccs;
    char *extension;
} stext[] =  {
    { CCS_PREPROCESSOR, "c" },
    { CCS_COMPILATION, "ll" },
    { CCS_LLVM_OPT, "bc" },
    { CCS_LLVM_COMPILATION, "s" },
    { CCS_ASSEMBLY, "o" },
    { CCS_LINKING, "" },
};

const char *extension_by_stage(unsigned int stage)
{
    if (stage >= ARRAY_SIZE(stext))
        internal_fatal_error("unexpected error %d %s:%d\n", stage,
                             __FILE__, __LINE__);
    return stext[stage].extension;
}

int first_stage_by_extension(const char *ext)
{
    for (unsigned i = 0; i < ARRAY_SIZE(stext); ++i) {
        if (0 == strcmp(stext[i].extension, ext)) {
            return stext[i].ccs;
        }
    }
    internal_fatal_error("extension not recognized: %s\n", ext);
    return NEVER_REACHED;
}

void split_extension(const char *input_filename, char *file_extension[2])
{
    char *filename = strdup(input_filename);

    int s = strlen(filename);
    int i = s -1;
    for (; s >= 0; --i)
    {
        if ('.' == filename[i])
        {
            filename[i] = '\0';
            file_extension[0] = filename;
            file_extension[1] = &filename[i+1];
            break;
        }
    }
    if (i < 0)
        file_extension[0] = file_extension[1] = filename;
}

static int exec_program(char *const argv[], int input, int output)
{
    int ret = 0;
    pid_t p = fork();
    switch (p) {
    case 0:
        // child
        dup2(input, STDIN_FILENO);
        dup2(output, STDOUT_FILENO);
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(EXIT_FAILURE);
        break;
    case -1:
        fprintf(stderr, "cannot fork: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
        break;
    default:
        // parent
        waitpid(p, &ret, 0);
        if (!WIFEXITED(ret)) {
            fprintf(stderr, "%s exited abnormally\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        break;
    }
    return WEXITSTATUS(ret);
}

static int run_stage(const char *cmd, struct list *arglist, int input, int output)
{
    int ret = 0;
    int si = list_size(arglist);
    char **args = calloc(si + 2, sizeof*args);
    int i = 0;

    args[i++] = strdup(cmd);
    for (; i <= si; ++i) {
        args[i] = list_get(arglist, i);
    }
    args[i] = NULL;
    ret = exec_program(args, input, output);
    args = NULL;
    return ret;
}
/* { "opt", "-std-compile-opts", "-mem2reg", NULL }, */


static int do_stage(const struct bcc_option *options,
                    enum c_compil_stage stage,
                    const char *command,
                    const char *stage_name,
                    FILE **input_file)
{
    FILE *output_file = NULL;

    debug("stage %s reached \n", stage_name);
    if (stage == options->last_stage) {
        debug("last stage is %s\n", stage_name);
        output_file = stdout;
    } else {
        output_file = tmpfile();
    }

    struct list *arg_list = NULL;
    switch (stage) {
    case CCS_PREPROCESSOR: arg_list = options->cpp_arg; break;
    case CCS_COMPILATION: arg_list = options->cc1_arg; break;
    case CCS_LLVM_OPT: arg_list = options->opt_arg; break;
    case CCS_LLVM_COMPILATION: arg_list = options->llc_arg; break;
    case CCS_ASSEMBLY: arg_list = options->gas_arg; break;
    default: arg_list = NULL; break;
    }

    // run
    int ret =  run_stage(command, arg_list,
                         fileno(*input_file),
                         fileno(output_file));

    fclose(*input_file);
    *input_file = output_file;
    rewind(*input_file);
    return ret;
}


int compile_chain(const char *input_name, const struct bcc_option *options)
{
    /* int fstage; */
    int lstage = 0;
    char *file_extension[2] = {NULL,NULL};
    char *output_name = NULL;
    const char *ext = 0;

    split_extension(input_name, file_extension);
    /* fstage = first_stage_by_extension(file_extension[1]); */
    lstage = last_stage_by_option(options);
    ext = extension_by_stage(lstage);

    asprintf(&output_name,
             "%s%s%s",
             basename(file_extension[0]),
             ((strlen(ext) > 0) ? "." : ""),
             ext);

    FILE *input_file = fopen(input_name, "r");

    do_stage(options, CCS_PREPROCESSOR, "cpp", "CCS_PREPROCESSOR", &input_file);
    do_stage(options, CCS_COMPILATION, "./cc1", "CCS_COMPILATION", &input_file);
    do_stage(options, CCS_LLVM_OPT, "opt", "CCS_LLVM_OPT", &input_file);
    do_stage(options, CCS_LLVM_COMPILATION, "llc", "CCS_LLVM_COMPILATION", &input_file);
    int ret = do_stage(options, CCS_ASSEMBLY, "as", "CCS_ASSEMBLY", &input_file);

    fclose(input_file);

    return ret;
}
