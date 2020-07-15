#ifndef BCC_CHAIN_H
#define BCC_CHAIN_H

enum c_compil_stage
{
    CCS_PREPROCESSOR,     // cpp
    CCS_COMPILATION,      // cc1
    CCS_LLVM_OPT,         // opt
    CCS_LLVM_COMPILATION, // llc
    CCS_ASSEMBLY,         // as
    CCS_LINKING,          // ld

    CCS_NUMSTAGE,   // must be last
};

#include "option.h"

int first_stage_by_extension(const char *ext);
void split_extension(const char *filename__, char *file_extension[2]);
int compile_chain(const char *filename, const struct bcc_option *bopt);
const char * extension_by_stage(unsigned int stage);

#endif // BCC_CHAIN_H
