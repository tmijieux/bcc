#ifndef BCC_UTIL_STRING_2_H
#define BCC_UTIL_STRING_2_H

/*
 * remove trailing linefeed and tabulation at any place
 */
char *strstrip(const char *str);

/*
 * remove trailing quote:  '"'
 */
char *strstrip2(const char *str);

#endif // BCC_UTIL_STRING_2_H
