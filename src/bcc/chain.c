#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "util/error.h"

#define MAX_ARGS 128
#define NEVER_REACHED -42
#define ARRAY_SIZE(x__) (sizeof(x__)/sizeof(*(x__)))

#include <stdio.h>
#include "chain.h"

struct {
    enum c_compil_stage ccs;
    char *extension;
} stext[] =  {
    { ccs_preprocessor, "c" },
    { ccs_compilation, "ll" },
    { ccs_llvm_opt, "bc" },
    { ccs_llvm_compilation, "s" },
    { ccs_assembly, "o" },
    { ccs_linking, "" },
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
    for (int i = 0; i < ARRAY_SIZE(stext); ++i) {
        if (0 == strcmp(stext[i].extension, ext)) {
            return stext[i].ccs;
        }
    }
    internal_fatal_error("extension not recognized: %s\n", ext);
    return NEVER_REACHED;
}

void split_extension(const char *filename__, char *file_extension[2])
{
    int i, s;
    char *filename = strdup(filename__);
    
    s = strlen(filename);
    for (i = s-1; s >= 0; --i) {
        if ('.' == filename[i]) {
            filename[i] = '\0';
            file_extension[0] = filename;
            file_extension[1] = &filename[i+1];
            break;
        }
    }
    if (i < 0)
        file_extension[0] = file_extension[1] = filename;
}

static int exec_program(char * const argv[], int input, int output)
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

static int x_stage(const char *cmd, struct list *arglist,
                   int input, int output)
{
    int si = list_size(arglist), i, ret = 0;
    char **args = calloc(si + 2, sizeof*args);

    i = 0;
    args[i++] = strdup(cmd);
    for (; i <= si; ++i)
        args[i] = list_get(arglist, i);
    args[i] = NULL;
    ret = exec_program(args, input, output);
    args = NULL;
    return ret;
}
/* { "opt", "-std-compile-opts", "-mem2reg", NULL }, */

#define prepare_stage(stage_name__)                     \
    do {                                                \
        if (ccs_##stage_name__ == bopt->last_stage) {   \
            debug("last stage is %s\n", #stage_name__); \
            output = stdout;                            \
        } else {                                        \
            output = tmpfile();                         \
        }                                               \
    } while (0)                                         \
        
#define run_stage(stage_command__, stage_short__)                  \
    do {                                                           \
        ret = x_stage(stage_command__, bopt->stage_short__##_arg,  \
                      fileno(input), fileno(output));              \
    } while(0)                                                     \
        

#define end_stage(stage_name__)                                \
    do {                                                       \
        if (ret || ccs_##stage_name__ == bopt->last_stage) {   \
            return ret;                                        \
        }                                                      \
    } while(0)                                                 \


#define stage(stage_name__, stage_command__, stage_short__)     \
    do {                                                        \
        debug("stage: %s reached\n", #stage_name__);            \
        prepare_stage(stage_name__);                            \
        run_stage(stage_command__, stage_short__);              \
        end_stage(stage_name__);                                \
        fclose(input);                                          \
        input = output; rewind(input);                          \
        output = tmpfile();                                     \
    } while(0)                                                  \


int compile_chain(const char *input_name, const struct bcc_option *bopt)
{
    int ret = -1;
    FILE *input, *output;
    
    int fstage, lstage;
    char *file_extension[2], *output_name;
    const char *ext;
    
    split_extension(input_name, file_extension);
    fstage = first_stage_by_extension(file_extension[1]);
    lstage = last_stage_by_option(bopt);
    ext = extension_by_stage(lstage);
    asprintf(&output_name, "%s%s%s", basename(file_extension[0]),
             strlen(ext) > 0 ? "." : "", ext);

    input = fopen(input_name, "r");

    stage(preprocessor, "cpp", cpp);
    stage(compilation, "./cc1", cc1);
    stage(llvm_opt, "opt", opt);
    stage(llvm_compilation, "llc", llc);
    stage(assembly, "as", gas);
    
    
    return ret;
}
