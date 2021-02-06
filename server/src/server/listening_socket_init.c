#include "server.h"


static struct sockaddr_in serv_address_description(int port) {
    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_addr.sin_port        = htons(port);     
    return serv_addr;
}
int mx_listening_socket_init(int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Creating socket error", sockfd);
    struct sockaddr_in serv_addr = serv_address_description(port);
    int bind_status = bind(sockfd, (struct  sockaddr *)&serv_addr, sizeof(serv_addr));
    error("Bind error", bind_status);
    return sockfd;
}

