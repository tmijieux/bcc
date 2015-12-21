#ifndef COLOR_H
#define COLOR_H

extern int COLOR_LEN;

#define COLOR_START "\e["
#define COLOR_RESET "\e[0m"
#define COLOR_DEBUG(x) COLOR_START "7;33;40m" x COLOR_RESET

const char *color(const char *col, const char *message);



#endif	//COLOR_H
