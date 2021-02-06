#include "libmx.h"

void mx_printint(int n) {
    long a = n;

    if(a == 0) 
        mx_printchar('0');
    if(a < 0) {
        a *= -1;
        mx_printchar('-');
    }
    long num = 1;
    while((a / num) > 0)
        num *= 10;

    long tmp;
    num /= 10;
    while(num >= 1) {
        mx_printchar((a / num) + 48);
        tmp = a / num;
        a -= tmp * num;
        num /= 10;        
    }
}
