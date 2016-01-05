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

void bopt_init(struct bcc_option *bopt)
{
    memset(bopt, 0, sizeof*bopt);

    bopt->last_stage = ccs_linking;
    bopt->cpp_arg = list_new(0);
    bopt->cc1_arg = list_new(0);
    bopt->opt_arg = list_new(0);
    bopt->llc_arg = list_new(0);
    bopt->gas_arg = list_new(0);
}

#define set_last_stage(first_stop__, second_stop__, optcharstr__)       \
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
    
    const char *optstring = "ES::c::o:h::vxI:L:l::";
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
        case 'E':
            set_last_stage(ccs_llvm_opt, ccs_preprocessor, "c");
            break;
        case 'c':
            set_last_stage(ccs_llvm_opt, ccs_assembly, "o");
            break;
        case 'S':
            set_last_stage(ccs_compilation, ccs_llvm_compilation, "S");
            break;
        case 'I':
            list_append(bopt->cpp_arg, "I");
            list_append(bopt->cpp_arg, strdup(optarg));
            // pass option to cpp
            break;
        case 'L':
            list_append(bopt->gas_arg, "L");
            list_append(bopt->gas_arg, strdup(optarg));
            // pass option to ld
            break;
        case 'l':
            if (NULL != optarg) {
                char *str;
                asprintf(&str, "-l%s", optarg);
                list_append(bopt->gas_arg, str);
            } else {
                internal_error("missing argument to option `-l´\n");
            }
            // pass option to ld
            break;

	case '?':
            if ('L' == optopt || 'I' == optopt) {
                internal_fatal_error(
                    "missing argument to option `-%c´\n", optopt);
            } else {
                internal_fatal_error(
                    "unrecognized command line option `-%c´\n", optopt);
            }
	    break;
	}
    }
    *argc -= optind - 1;
    *argv += optind - 1;

    return 0;
}
#undef set_last_stage

int last_stage_by_option(const struct bcc_option *bopt)
{
    return bopt->last_stage;
}

void option_check(const struct bcc_option *bopt, int file_count)
{
    if (file_count >= 2 && NULL != bopt->output &&
        ccs_linking != bopt->last_stage)
    {
        internal_fatal_error(
            "-E, -c and -S cannot be combined with -o "
            "when more than one input file is given\n");
    }

    // ...
}

