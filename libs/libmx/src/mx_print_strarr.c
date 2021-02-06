#include "libmx.h"

void mx_print_strarr(char **arr, char *delim){
    if (arr == NULL || delim == NULL)
        return;

    int i = 0;
    while(arr[i]){
        mx_printstr(arr[i]);
        if (arr[i + 1])
            mx_printstr(delim);
        i++;
    }
    mx_printchar('\n');
}
