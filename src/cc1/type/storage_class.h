#ifndef BCC_STORAGE_CLASS_H
#define BCC_STORAGE_CLASS_H

struct storage_class {

    enum storage_class_type {
        STO_GLOBAL,
        STO_STATIC,
        STO_AUTO,
        STO_REGISTER,
    };
};


struct visibility {
    enum visibility_type {
        VIS_DEFAULT, // global
        VIS_HIDDEN,
        VIS_PROTECTED,
    };
};

struct linkage {
    enum linkage_type {
        LNK_PRIVATE,
        LNK_INTERNAL,
        LNK_AVAILABLE_EXTERNALLY,
        LNK_LINKONCE,
        LNK_WEAK,
        LNK_COMMON,
        LNK_APPENDING,
        LNK_EXTERN_WEAK,
        LNK_LINKONCE_ODR,
        LNK_WEAK_ODR,
        LNK_EXTERNAL
    };
};

#endif // BCC_STORAGE_CLASS_H
