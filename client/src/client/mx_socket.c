#include "client.h"

// Socket TCP/IP4 
int mx_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Error while creating socket", sockfd);

    return sockfd;
}

