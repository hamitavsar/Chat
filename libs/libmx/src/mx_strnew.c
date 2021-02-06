#include "libmx.h"

char *mx_strnew(int size) {
    char *memory = malloc(size + 1);

    if (memory == NULL)
        return NULL;
    for (int i = 0; i < size + 1; i++)
        memory[i] = '\0';
    return memory;
}
