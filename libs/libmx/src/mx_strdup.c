#include "libmx.h"

char *mx_strdup(char *str) {
    int length = mx_strlen(str);
    char *memory = mx_strnew(length);
    char *p = mx_strcpy(memory, str);
    return p;
}
