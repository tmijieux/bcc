#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdint.h>
#include <stdbool.h>

enum constant_type {
    CONSTANT_CHAR,
    CONSTANT_SHORT,
    CONSTANT_INT,
    CONSTANT_LONG,
    CONSTANT_FLOAT,
    CONSTANT_DOUBLE,
    CONSTANT_STRING,
};

struct constant {
    enum constant_type constant_type;
    const struct type *type;

    union {
        union {
            char undef_;
            int8_t signed_;
            uint8_t unsigned_;
        } charv;
        
        union {
            int16_t _signed;
            uint16_t _unsigned;
        } shortv;

        union {
            int32_t signed_;
            uint32_t unsigned_;
        } intv;
    
        union {
            int64_t signed_;
            uint64_t unsigned_;
        } longv;
    } integer;
    
    float floatv;
    double doublev;
    
    char *stringv;
    
};

struct constant *constant_hex_integer(const char *string);
struct constant *constant_oct_integer(const char *string);
struct constant *constant_dec_integer(const char *string);
struct constant *constant_string_literal(const char *string);
struct constant *constant_integer_long(long integer);
struct constant *constant_integer_int(int integer);
bool constant_is_zero(const struct constant *);

#endif //CONSTANT_H
