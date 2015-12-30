#ifndef COLOR_H
#define COLOR_H

extern int COLOR_LEN;

// Color macros
#define ERROR_COLOR "31;1"
#define WARN_COLOR "35;1"
#define RESET_COLOR "0"
#define BOLD_COLOR ""
#define PASSED_COLOR "32"
#define DEBUG_COLOR "7;33;40"


#ifndef NO_COLOR
# define COLOR(__c, __s) ESCAPE(__c) __s ESCAPE(RESET)
# define ESCAPE(__s) "\x1B[" __s##_COLOR "m"
#else
# define COLOR(__c, __s) __s
# define ESCAPE(__s)
#endif

const char *color(const char *col, const char *message);

#endif	//COLOR_H
