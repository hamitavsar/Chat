#include "utils.h" 

static int packet_length_determine(int socket) {
    char buf[8];
    bzero(buf, 8);
    recv(socket, buf, 8, 0);
    int packet_len = atoi(buf);

    return packet_len;
}

char *packet_receive(int socket) {
    int  packet_len = packet_length_determine(socket);
    int  index      = 0;
    char *packet    = mx_strnew(packet_len);
    char *encrypted_packet;

    while(index < packet_len) {
        recv(socket, &packet[index], 1, 0);
        index++;
    }

    return packet;
}

