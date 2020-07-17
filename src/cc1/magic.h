#ifndef BCC_MAGIC_H
#define BCC_MAGIC_H

typedef enum magic {
    MAGIC_STATEMENT = 117,
    MAGIC_EXPRESSION = 118,
    MAGIC_SYMBOL = 119,
    MAGIC_TYPE = 120,
    MAGIC_DECLARATOR = 121,
    MAGIC_LIST = 122,
} magic_t;

#define ASSERT_MAGIC(Elem_, Magic_) do {        \
        assert((Elem_)->magic == (Magic_));     \
    } while(0)                                  \


#endif // BCC_MAGIC_H
