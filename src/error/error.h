#ifndef ERROR_H
#define ERROR_H

#ifndef ERROR_OUTPUT
#define ERROR_OUTPUT stderr
#endif
#include "color.h"

void warning(const char *format, ...);
void error(const char *format, ...);
void fatal_error(const char *format, ...);
void internal_error(const char *format, ...);
int error_count(void);
int yyerror(const char *s);
void debugi(const char *format, ...);

#ifndef NDEBUG
#define debug(x, ...) debugi(COLOR_DEBUG("DEBUG: %s: %d: ") x, __FILE__, \
                            __LINE__, ##__VA_ARGS__)
#else
#define debug
#endif

#endif	//ERROR_H
