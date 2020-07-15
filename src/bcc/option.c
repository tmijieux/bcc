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

void opt_init(struct bcc_option *opt)
{
    memset(opt, 0, sizeof*opt);

    opt->last_stage = CCS_LINKING;
    opt->cpp_arg = list_new(0);
    opt->cc1_arg = list_new(0);
    opt->opt_arg = list_new(0);
    opt->llc_arg = list_new(0);
    opt->gas_arg = list_new(0);
}

void set_last_stage(struct bcc_option *opt,
                      enum c_compil_stage first_stop,
                      enum c_compil_stage second_stop,
                      const char *optcharstr)
{

    if (optarg != NULL)
    {
        if (!strcmp(optarg, "1"))
        {
            opt->last_stage = first_stop;
        }
        else if (!strcmp(optarg, "2"))
        {
            opt->last_stage = second_stop;
        }
        else
        {
            internal_fatal_error("argument to -%s option must be 1 or 2\n", optcharstr);
        }
    }
    else
    {
        opt->last_stage = second_stop;
    }
}

int parse_options(int *argc, char ***argv, struct bcc_option *opt)
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
            opt->output = strdup(optarg);
            break;
        case 'E':
            set_last_stage(opt, CCS_LLVM_OPT, CCS_PREPROCESSOR, "c");
            break;
        case 'c':
            set_last_stage(opt, CCS_LLVM_OPT, CCS_ASSEMBLY, "o");
            break;
        case 'S':
            set_last_stage(opt, CCS_COMPILATION, CCS_LLVM_COMPILATION, "S");
            break;
        case 'I':
            list_append(opt->cpp_arg, "I");
            list_append(opt->cpp_arg, strdup(optarg));
            // pass option to cpp
            break;
        case 'L':
            list_append(opt->gas_arg, "L");
            list_append(opt->gas_arg, strdup(optarg));
            // pass option to ld
            break;
        case 'l':
            if (NULL != optarg) {
                char *str;
                asprintf(&str, "-l%s", optarg);
                list_append(opt->gas_arg, str);
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

int last_stage_by_option(const struct bcc_option *opt)
{
    return opt->last_stage;
}

void option_check(const struct bcc_option *opt, int file_count)
{
    if (file_count >= 2
        && NULL != opt->output
        && CCS_LINKING != opt->last_stage)
    {
        internal_fatal_error(
            "-E, -c and -S cannot be combined with -o "
            "when more than one input file is given\n");
    }

    // ...
}

