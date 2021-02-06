#include "crypt.h"

static bool mx_check_prime_number(int number) {
    int count = 0;
    int divider = number;
    bool status = false;

    while(divider != 0) {
        if(number % divider == 0) {
            count++;
        }
        divider--;
    }
    if(count == 2) {
        status = true;
    }
    return status;
}

int mx_get_prime_number(int min, int max) {
    int num = (rand() % (max - min)) + min;

    while(!mx_check_prime_number(num)) {
        num = (rand() % (max - min)) + min;
    }
    return num;
}
