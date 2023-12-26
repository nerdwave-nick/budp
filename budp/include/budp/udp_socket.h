#ifndef BUDP_UDP_SOCKETS_H
#define BUDP_UDP_SOCKETS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"

typedef int udp_socket;

bool open_socket(udp_socket* socket_out, bool nonblocking, unsigned short port);
bool close_socket(udp_socket* socket);

unsigned int make_address(unsigned char a, unsigned char b, unsigned char c,
                          unsigned char d);

bool send_packet(udp_socket socket, unsigned char* data, int data_size,
                 unsigned int address, unsigned short port);
int receive_packet(udp_socket socket, unsigned char* buffer, int buffer_size,
                   unsigned int* address, unsigned short* port);

#ifdef __cplusplus
}
#endif
#endif  // BUDP_UDP_SOCKETS_H
