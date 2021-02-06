#include "libmx.h"

int mx_symbols_in_str(char *str, char *symbols) {
    for (int i = 0; i < (int)strlen(str); i++) {
        for (int j = 0; j < (int)strlen(symbols); j++) {
            if (str[i] == symbols[j]) {
                return 1;
            }
        }
    }
    return 0;
}
