#include "budp/sockets.h"

#include "debug.h"
#include "platform.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <winsock2.h>
#pragma comment(lib, "wsock32.lib")  //  windows being windows
// reference count for windows sockets, as they need to be initialized and
// shutdown
static int socket_references = 0;
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#endif

bool init_socket_layer() {
#if PLATFORM == PLATFORM_WINDOWS
    if (socket_references > 0) {
        socket_references++;
        return true;
    }
    WSADATA WsaData;
    return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#else
    return true;
#endif
}

void shutdown_socket_layer() {
#if PLATFORM == PLATFORM_WINDOWS
    if (socket_references > 0) {
        socket_references--;
        if (socket_references > 0) {
            return;
        }
    }
    WSACleanup();
#endif
}

bool open_socket(udp_socket* socket_out, bool nonblocking,
                 unsigned short port) {
    if (socket_out == 0) {
        BUNNY_DEBUG_PRINT("socket_out is null\n");
        return false;
    }
    if (!init_socket_layer()) {
        BUNNY_DEBUG_PRINT("failed to initialize socket layer\n");
        return false;
    }

    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (handle <= 0) {
        BUNNY_DEBUG_PRINT("failed to create socket\n");
        return false;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short)port);

    if (bind(handle, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) <
        0) {
        BUNNY_DEBUG_PRINT("failed to bind socket\n");
        return false;
    }

#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    if (nonblocking) {
        if (fcntl(handle, F_SETFL, O_NONBLOCK, true) == -1) {
            BUNNY_DEBUG_PRINT("failed to set non-blocking\n");
            return false;
        }
    }
#elif PLATFORM == PLATFORM_WINDOWS
    if (nonblocking) {
        DWORD nonBlocking = 1;
        if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0) {
            BUNNY_DEBUG_PRINT("failed to set non-blocking\n");
            return false;
        }
    }
#endif
    socket_out->socket = handle;
    return true;
}

bool close_socket(udp_socket* socket) {
    if (socket == 0) {
        BUNNY_DEBUG_PRINT("socket is null\n");
        return false;
    }
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    close(socket->socket);
#elif PLATFORM == PLATFORM_WINDOWS
    closesocket(socket->socket);
#endif
    socket->socket = 0;
    return true;
}

unsigned int make_address(unsigned char a, unsigned char b, unsigned char c,
                          unsigned char d) {
    return (a << 24) | (b << 16) | (c << 8) | d;
}

bool send_packet(udp_socket* socket, unsigned char* data, int data_size,
                 unsigned int address, unsigned short port) {
    if (socket == 0) {
        BUNNY_DEBUG_PRINT("socket is null\n");
        return false;
    }
    if (data == 0) {
        BUNNY_DEBUG_PRINT("data is null\n");
        return false;
    }
    if (data_size <= 0) {
        BUNNY_DEBUG_PRINT("data_size is <= 0\n");
        return false;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(address);
    addr.sin_port = htons(port);

    int sent_bytes =
        sendto(socket->socket, (const char*)data, data_size, 0,
               (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

    if (sent_bytes != data_size) {
        BUNNY_DEBUG_PRINT("failed to send packet\n");
        return false;
    }
    return true;
}

#if PLATFORM == PLATFORM_WINDOWS
typedef int socklen_t;
#endif

int receive_packet(udp_socket* socket, unsigned char* buffer, int buffer_size,
                   unsigned int* address, unsigned short* port) {
    if (socket == 0) {
        BUNNY_DEBUG_PRINT("socket is null\n");
        return false;
    }
    if (buffer == 0) {
        BUNNY_DEBUG_PRINT("buffer is null\n");
        return false;
    }
    if (buffer_size <= 0) {
        BUNNY_DEBUG_PRINT("buffer_size is <= 0\n");
        return false;
    }
    struct sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int bytes = recvfrom(socket->socket, (char*)buffer, buffer_size, 0,
                         (struct sockaddr*)&from, &fromLength);

    if (bytes <= 0) {
        BUNNY_DEBUG_PRINT("failed to receive packet\n");
        return bytes;
    }

    unsigned int from_address = ntohl(from.sin_addr.s_addr);
    unsigned int from_port = ntohs(from.sin_port);
    return bytes;
}