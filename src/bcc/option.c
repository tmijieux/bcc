#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "util/error.h"
#include "option.h"

extern char *optarg;
extern int optopt, opterr;

static struct option option[] = {
    { "language", 1, NULL, 'x' },
    { "version", 0, NULL, 'v' },
    { "help", 2, NULL, 'h' },
    { "output", 2, NULL, 'o' },
    { 0 }
};

void print_help(void)
{
    printf("help\n");
}

void print_version(void)
{
    printf("version\n");
}

#define last_stage(first_stop__, second_stop__, optcharstr__)           \
    do {                                                                \
        if (NULL != optarg) {                                           \
            if (!strcmp(optarg, "1")) {                                 \
                bopt->last_stage = first_stop__;                        \
            } else if (!strcmp(optarg, "2")) {                          \
                bopt->last_stage = second_stop__;                       \
            } else {                                                    \
                internal_fatal_error("argument to -"optcharstr__        \
                                     " option must be 1 or 2\n");       \
            }                                                           \
        } else {                                                        \
            bopt->last_stage = second_stop__;                           \
        }                                                               \
    } while (0)                                                         \
    
int parse_options(int *argc, char ***argv, struct bcc_option *bopt)
{
    char c;
    opterr = 0;
    
    const char *optstring = "ES::c::o:h::vxI:L:";
    while ((c = getopt_long(*argc, *argv, optstring, option, NULL)) != -1) {
	switch (c) {
        case 'h':
            print_help();
            exit(EXIT_FAILURE);
            break;
        case 'v':
            print_version();
            exit(EXIT_FAILURE);
            break;
        case 'o':
            bopt->output = strdup(optarg);
            break;
        case 'c':
            last_stage(ccs_llvm_opt, ccs_assembly, "c");
            break;
        case 'S':
            last_stage(ccs_compilation, ccs_llvm_compilation, "S");
            break;
        case 'I':
            // pass option to cpp
            break;
        case 'L':
            // pass option to ld
            break;
	case '?':
            internal_error("unrecognized command line option `-%c´\n", optopt);
	    break;
	}
    }
    *argc -= optind - 1;
    *argv += optind - 1;
    return 0;
}
#undef last_stage

int last_stage_by_option(const struct bcc_option *bopt)
{
    return 5;
}
