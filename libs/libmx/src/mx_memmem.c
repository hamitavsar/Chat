#include "libmx.h"


void *mx_memmem(void *big, size_t big_len, void *little, size_t little_len) {
    unsigned long blen = (unsigned long)big_len;
    unsigned long llen = (unsigned long)little_len;
    char *b = (char *)big;
    char *l = (char *)little;

    if (blen < llen || llen == 0 || blen == 0)
        return NULL;

    unsigned long i = 0;
    while(i < blen){
        if (b[i] == l[0]){
            unsigned long j = 0;
            unsigned long tmp = i;
            while (b[tmp] == l[j]){
                if (j == llen - 1)
                    return &b[i];
                j++;
                tmp++;
            }
        }
        i++;
    }
    return NULL;
}
