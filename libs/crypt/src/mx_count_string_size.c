#include "crypt.h"


int mx_count_string_size(char *str) {
    int counter = 0;

    for(int i = 0; str[i]; i++) {
        if(*(str + i) == '-') {
            counter++;
        }
    }
    counter--;
    return counter;
}
