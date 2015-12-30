#ifndef OPTION_H
#define OPTION_H

#include "chain.h"

struct bcc_option {
    char *output;
    enum c_compil_stage last_stage;
    
};

int parse_options(int *argc, char ***argv, struct bcc_option *bopt);
int last_stage_by_option(const struct bcc_option *bopt);

#endif //OPTION_H
