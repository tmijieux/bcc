#include <stdio.h>

char *strescp(char *s)
{
	char *ret = s, *dest = s;

	do {
		if (*s == '\\') {
			switch (*++s) {
			case 'a': *dest = '\a'; break;
			case 'b': *dest = '\b'; break;
			case 'f': *dest = '\f'; break;
			case 'n': *dest = '\n'; break;
			case 'r': *dest = '\r'; break;
			case 't': *dest = '\t'; break;
			case 'v': *dest = '\v'; break;
			default: *dest = *s;
			}
		} else {
			*dest = *s;
		}
		s++;
	} while (*dest++);

	return ret;
}

int main(void)
{
	char str[] = "this\\n\\tis\\na\\ntest\\n";

	printf("%s", strescp(str));

	return 0;;
}

