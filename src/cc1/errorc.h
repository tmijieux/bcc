#ifndef BCC_COMPILE_ERROR_H
#define BCC_COMPILE_ERROR_H

#ifndef ERROR_OUTPUT
#define ERROR_OUTPUT stderr
#endif

int error_count(void);

void warning(const char *format, ...);
void error(const char *format, ...);
void fatal_error(const char *format, ...);

int yyerror(const char *s);

#endif // BCC_COMPILE_ERROR_H
