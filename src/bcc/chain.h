#ifndef CHAIN_H
#define CHAIN_H


enum c_compil_stage {
    ccs_preprocessor,     // cpp
    ccs_compilation,      // cc1
    ccs_llvm_opt,         // opt
    ccs_llvm_compilation, // llc
    ccs_assembly,         // as
    ccs_linking,          // ld
    
    ccs_numstage,   // must be last
};


int first_stage_by_extension(const char *ext);
void split_extension(const char *filename__, char *file_extension[2]);
int compile_chain(const char *filename, const char *output_name,
                  int fstage, int lstage);
const char * extension_by_stage(unsigned int stage);

#endif //CHAIN_H
