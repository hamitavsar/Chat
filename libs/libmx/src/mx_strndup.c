#include "libmx.h"

char *mx_strndup(char *s1, size_t n){
    char *memory = mx_strnew(n);
    int i = 0;

    while(i <= (int)n){
        memory[i] = s1[i];
        i++;
    }
    return memory;
}
