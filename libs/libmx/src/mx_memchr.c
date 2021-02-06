#include "libmx.h"


void *mx_memchr(void *s, int c, size_t n) {
    unsigned long len = (unsigned long)n;
    unsigned char *s1 = (unsigned char *)s;

    for (unsigned long i = 0; i < len; ++i) {
        if (s1[i] == c)
            return &s1[i];
    }
    return NULL;
}


