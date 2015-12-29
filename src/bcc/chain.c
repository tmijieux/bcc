#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define MAX_ARGS 128

extern char **environ;

int exec_program(char * const argv[], int input, int output)
{
    int ret = 0;
    pid_t p = fork();
    
    switch (p) {
    case 0:
        // child
        dup2(input, STDIN_FILENO);
        dup2(output, STDOUT_FILENO);
        execve(argv[0], argv, environ);
        fprintf(stderr, "exec failed\n");
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

int chain(const char *input_name, const char *output_name, int last_stage)
{
    char *stage_cmd[][MAX_ARGS] =  {
        { "cpp", NULL },
        { "./cc1", NULL },
        { "opt", "-std-compile-opts", "-mem2reg", NULL },
        { "llc", NULL },
        { "as", NULL}
    };
    
    return 0;
}
