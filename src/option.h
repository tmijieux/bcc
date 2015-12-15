#ifndef OPTION_H
#define OPTION_H

struct bcc_option {};

int parse_options(int *argc, char *argv[], struct bcc_option *bopt);

#endif //OPTION_H
