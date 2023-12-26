#ifndef BUDP_SOCKETS_H
#define BUDP_SOCKETS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "budp/udp_socket.h"
#include "stdbool.h"

#define BUDP_MAX_PACKET_SIZE 1024

typedef struct {
    udp_socket socket;
    unsigned int connected_address;
    unsigned int outgoing_sequence;
    unsigned int incoming_sequence;
    unsigned int ack_bits;
    unsigned short connected_port;
    bool is_connected;
} budp_socket;

bool init_socket(budp_socket* socket, unsigned short port);
bool connect(budp_socket* socket, unsigned int address, unsigned short port);
bool send_message(budp_socket* socket, unsigned char* data, int data_size);
bool receive_message(budp_socket* socket, unsigned char* buffer,
                     unsigned int buffer_size);

#ifdef __cplusplus
extern
}
#endif
#endif  // BUDP_SOCKETS_H