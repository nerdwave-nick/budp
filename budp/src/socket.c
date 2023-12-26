#include "budp/socket.h"

#include "./debug.h"
#include "budp/message.h"
#include "budp/udp_socket.h"

bool init_socket(budp_socket* socket, unsigned short port) {
    if (socket == 0) {
        BUNNY_DEBUG_PRINT("socket is null\n");
        return false;
    }
    if (!open_socket(&socket->socket, true, port)) {
        BUNNY_DEBUG_PRINT("failed to open socket\n");
        return false;
    }
    socket->connected_address = 0;
    socket->connected_port = 0;
    socket->outgoing_sequence = 0;
    socket->incoming_sequence = 0;
    socket->ack_bits = 0;
    socket->is_connected = false;
    return true;
}
bool connect(budp_socket* socket, unsigned int address, unsigned short port) {
    if (socket == 0) {
        BUNNY_DEBUG_PRINT("socket is null\n");
        return false;
    }
    socket->connected_address = address;
    socket->connected_port = port;
    socket->outgoing_sequence = 0;
    socket->incoming_sequence = 0;
    socket->ack_bits = 0;
    socket->is_connected = true;
    return true;
}