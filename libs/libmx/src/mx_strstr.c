#include "libmx.h"

char *mx_strstr(char *haystack, char *needle) {
    int len_needle = mx_strlen(needle);
    int i = 0;

    while(haystack[i]) {
        if (haystack[i] == needle[0]) {
            int j = 0;
            int tmp = i;
            while (haystack[tmp] == needle[j]){
                if (j == len_needle - 1) {
                    char *p = (char *)&haystack[i];
                    return p;
                }
                j++;
                tmp++;
            }
        }
        i++;
    }
    return NULL;
}
