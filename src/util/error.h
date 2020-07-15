#ifndef BCC_ERROR_H
#define BCC_ERROR_H

#ifndef ERROR_OUTPUT
#define ERROR_OUTPUT stderr
#endif

void error_set_program_name(const char *program_name_);
void internal_warning(const char *format, ...);
void internal_error(const char *format, ...);
void internal_fatal_error(const char *format, ...);
void debugi(const char *format, ...);


#ifndef NDEBUG
#include "color.h"
#define debug(x, ...) debugi(COLOR(DEBUG, "DEBUG: %s: %d: ") x "\n", __FILE__, \
                            __LINE__, ##__VA_ARGS__)
#else
#define debug
#endif

#endif	// BCC_ERROR_H
