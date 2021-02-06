#include "utils.h"



void mx_send(int socket, char *packet) {
    char *encrypted_packet = mx_rsa_encrypt(packet);
    char *prefixed_packet  = packet_len_prefix_adder(encrypted_packet);

    send(socket, prefixed_packet, (int)strlen(prefixed_packet), 0);

    free(encrypted_packet);
    free(prefixed_packet);
 }