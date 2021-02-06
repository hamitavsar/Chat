#include "libmx.h"


int mx_count_substr(char *str, char *sub) {
    if (str == NULL || sub == NULL)
        return -1;

    int len_sub = mx_strlen(sub);
    int i = 0;
    int counter = 0;
    
    while(str[i]){

        if (str[i] == sub[0]) {
            int j = 0;
            int tmp = i;
            while (str[tmp] && sub[j] && str[tmp] == sub[j]) {
                if (j == len_sub - 1){
                    counter++;
                    break;
                }
                j++;
                tmp++;
            }
        }
        i++;
    }
    return counter;
}
