#include "libmx.h"


char *mx_file_to_str(char *file) {
    char buff[1];
    int data_len;
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return NULL;
    data_len = 0;
    while (read(fd, buff, 1))
        data_len++;
    lseek(fd, 0L, 0);
    char *str = mx_strnew(data_len);
    int index = 0;
    while(data_len){
        read(fd, buff, 1);
        str[index] = buff[0];
        index++;
        data_len--;
    }
    close(fd);
    return str;
}

