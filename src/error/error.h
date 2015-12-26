#ifndef ERROR_H
#define ERROR_H

#ifndef ERROR_OUTPUT
#define ERROR_OUTPUT stderr
#endif

#include "../function.h"
#include "../type/type.h"
#include "../symbol/symbol.h"
#include "../expression/expression.h"
#include "../statement/statement.h"
#include "../constant/constant.h"
#include "../util/string2.h"
    
#include "../grammar.tab.h"
#include "../module.h"
#include "../util/color.h"

void warning(const char *format, ...);
void error(const char *format, ...);
void fatal_error(const char *format, ...);

void internal_warning(const char *format, ...);
void internal_error(const char *format, ...);
void internal_fatal_error(const char *format, ...);

int error_count(void);
void error_set_program_name(const char *program_name_);
int yyerror(const char *s);
void debugi(const char *format, ...);

#ifndef NDEBUG
#define debug(x, ...) debugi(COLOR_DEBUG("DEBUG: %s: %d: ") x, __FILE__, \
                            __LINE__, ##__VA_ARGS__)
#else
#define debug
#endif

#endif	//ERROR_H
