#ifndef STRING_LITERAL_H
#define STRING_LITERAL_H


struct literal {
    char *reg;
    char *value;
    size_t length;
};

struct literal *string_get_or_create_literal(const char *literal);
struct list *string_get_literals_list(void);

#endif //STRING_LITERAL_H
