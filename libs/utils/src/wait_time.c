#include "utils.h"

struct timeval wait_time(int sec, int msec) {
    struct timeval tv;
    tv.tv_sec  = sec; // Saniye.
    tv.tv_usec = msec; // mili Saniye.
    return tv;
}
