#ifndef BCC_OPTION_H
#define BCC_OPTION_H

struct bcc_option;

#include "util/list.h"
#include "./chain.h"

struct bcc_option {
    char *output;
    enum c_compil_stage last_stage;

    struct list *cpp_arg;
    struct list *cc1_arg;
    struct list *opt_arg;
    struct list *llc_arg;
    struct list *gas_arg;
};

void opt_init(struct bcc_option *opt);
int parse_options(int *argc, char ***argv, struct bcc_option *opt);
void option_check(const struct bcc_option *opt, int file_count);
int last_stage_by_option(const struct bcc_option *opt);

#endif // BCC_OPTION_H
