#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "color.h"
#include "hash_table.h"

static struct hash_table *colors;

int COLOR_LEN;

#define ADD_COLOR(x, y)				\
    ht_add_entry(colors, x , y) 

__attribute__ ((constructor))
static void clr_init(void)
{
    colors = ht_create(100, NULL);

    ADD_COLOR("RESET", COLOR_RESET);
    ADD_COLOR("red", "\e[91m");
    ADD_COLOR("light blue", "\e[96m");
    ADD_COLOR("fushia", "\e[95m");
    ADD_COLOR("green", "\e[92m");
    ADD_COLOR("yellow", "\e[93m");
    
    COLOR_LEN = strlen(color("green", ""));
}

const char *color(const char *clr, const char *message)
{
    char *clr_code = "";
    if (ht_get_entry(colors, clr, &clr_code) != 0) {
	fprintf(stderr, "Color Error: color %s doesn't exist\n", clr);
	return message;
    }

    char *clr_message;
    asprintf(&clr_message, "%s%s" COLOR_RESET, clr_code, message);
    return clr_message;
}
