#ifndef OPTION_H
#define OPTION_H
struct bcc_option;


#include <util/list.h>
#include "chain.h"

#define DEFAULT_OUTPUT_NAME "a.out"

struct bcc_option {
    char *output;
    enum c_compil_stage last_stage;
   
    struct list *cpp_arg; 
    struct list *cc1_arg; 
    struct list *opt_arg; 
    struct list *llc_arg; 
    struct list *gas_arg;
};

void bopt_init(struct bcc_option *bopt);
int parse_options(int *argc, char ***argv, struct bcc_option *bopt);
void option_check(const struct bcc_option *bopt, int file_count);
int last_stage_by_option(const struct bcc_option *bopt);

#endif //OPTION_H
