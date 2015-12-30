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

struct stage_extension {
    int stage_nb;
    char *extension;
};

static struct stage_extension stext[] = {
    { 0, "c" },
    // cpp --> ".c"
    { 1, ""},
    { 2, "ll" },
    { 3, "bc" },
    { 4, "s" },
    { 5, "o" },
    { 6, "" }
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
            return stext[i].stage_nb;
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

int compile_chain(const char *input_name, const char *output_name,
                  int first_stage, int last_stage)
{
    int ret;
    FILE *input, *output, *next, *prev;
    char *stage_cmd[][MAX_ARGS] = {
        { "cat", NULL },
        { "cpp", NULL },
        { "../cc1/cc1", NULL },
        { "opt", "-std-compile-opts", "-mem2reg", NULL },
        { "llc", NULL },
        { "as", NULL}
    };
    input = fopen(input_name, "r");
    output = fopen(output_name, "w+");
    
    /* First stage: */
    prev = tmpfile();
    if (first_stage == last_stage)
        prev = freopen(output_name, "w+", output);
    
    ret = exec_program(stage_cmd[first_stage], fileno(input), fileno(prev));
    if (ret)
        return ret;
    
    if (first_stage == last_stage)
        return 0;

    /* Middle stages: */
    for (int i = first_stage+1; i <= last_stage-1; ++i) {
        next = tmpfile();
        rewind(prev);
        ret = exec_program(stage_cmd[i], fileno(prev), fileno(next));
        fclose(prev);
        if (ret)
            return ret;
  
        prev = next;
    }

    /* Last stage */
    rewind(prev);
    ret = exec_program(stage_cmd[last_stage], fileno(prev), fileno(output));
    fclose(prev);
    
    return ret;
}
