#include "crypt.h"

//Sayının basamak sayısını hesaplama
int mx_count_amount_of_digits(long long int n) {
    int count = 0;

    while (n != 0) {
        n = n / 10;
        count++;
    }
    return count;
}
