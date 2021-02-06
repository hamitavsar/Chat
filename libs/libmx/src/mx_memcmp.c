#include "libmx.h"


int mx_memcmp(void *s1, void *s2, size_t n) {
    unsigned long len =(unsigned long)n;
    unsigned char *a = (unsigned char *)s1;
    unsigned char *b = (unsigned char *)s2;

    unsigned long i = 0;
    for (; i < len; ++i) {
        if(a[i] != b[i]) 
            return a[i] - b[i];
    }
    return 0;
}
