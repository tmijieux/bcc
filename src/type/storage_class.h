#ifndef STORAGE_CLASS_H
#define STORAGE_CLASS_H

struct storage_class {
    
    enum storage_class_type {
        sto_global,
        sto_static,
        sto_auto,
        sto_register,

    };

};


struct visibility {
    enum visibility_type {
        vis_default, // global
        vis_hidden,
        vis_protected,
        

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

#endif //STORAGE_CLASS_H
