#ifndef ERROR_H
#define ERROR_H

#ifndef ERROR_OUTPUT
#define ERROR_OUTPUT stderr
#endif

void warning(const char *format, ...);
void error(const char *format, ...);
void fatal_error(const char *format, ...);
void internal_error(const char *format, ...);
int error_count(void);
int yyerror(const char *s);

#endif	//ERROR_H
