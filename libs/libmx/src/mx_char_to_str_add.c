#include "libmx.h"



char *mx_char_to_str_add(char *str, char c) {
    char *new_str = mx_strnew((int)strlen(str) + 1);
    int i = 0;

    for (; str[i]; ++i)
        new_str[i] = str[i];
    new_str[i] = c;

    return new_str;
}

