#ifndef ERROR_H
#define ERROR_H

#ifndef ERROR_OUTPUT
#define ERROR_OUTPUT stderr
#endif

void error_set_program_name(const char *program_name_);
void internal_warning(const char *format, ...);
void internal_error(const char *format, ...);
void internal_fatal_error(const char *format, ...);
void debugi(const char *format, ...);

#ifndef NDEBUG
#define debug(x, ...) debugi(COLOR_DEBUG("DEBUG: %s: %d: ") x, __FILE__, \
                            __LINE__, ##__VA_ARGS__)
#else
#define debug
#endif

#endif	//ERROR_H
