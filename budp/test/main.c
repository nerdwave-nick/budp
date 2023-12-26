#include <stdio.h>

#include "budp/udp_socket.h"

int main(char** argv, int argc) {
    udp_socket socket;
    int own_port, port;
    char message[6];
    if (argc > 1) {
        port = 3092;
        own_port = 4092;
        message[0] = 'h';
        message[1] = 'e';
        message[2] = 'l';
        message[3] = 'l';
        message[4] = 'o';
        message[5] = '\0';
        if (!open_socket(&socket, false, own_port)) {
            printf("failed to open socket\n");
            return 1;
        }

        if (!send_packet(socket, message, 5, make_address(127, 0, 0, 1),
                         port)) {
            printf("failed to send\n");
            close_socket(&socket);
            return 1;
        }
        printf("sent\n");
        unsigned char buffer[256];
        int address;
        if (receive_packet(socket, buffer, 256, &address,
                           (short unsigned int*)&port) <= 0) {
            printf("failed to receive\n");
            close_socket(&socket);
            return 1;
        }
        printf("%s\n", buffer);
        close_socket(&socket);
    } else {
        port = 4092;
        own_port = 3092;
        message[0] = 'b';
        message[1] = 'y';
        message[2] = 'e';
        message[3] = '!';
        message[4] = '!';
        message[5] = '\0';
        if (!open_socket(&socket, false, own_port)) {
            printf("failed to open socket\n");
            return 1;
        }

        unsigned char buffer[256];
        int address;
        if (receive_packet(socket, buffer, 256, &address,
                           (short unsigned int*)&port) <= 0) {
            printf("failed to receive\n");
            close_socket(&socket);
            return 1;
        }
        printf("%s\n", buffer);

        if (!send_packet(socket, message, 5, make_address(127, 0, 0, 1),
                         port)) {
            printf("failed to send\n");
            close_socket(&socket);
            return 1;
        }
        printf("sent\n");
        close_socket(&socket);
    }
    return 0;
}

int do_stuff() {
    int* a = malloc(sizeof(int) * 500);
    // do stuff with a
    free(a);

    int b[500];

    // a = [0] * 500;
    return 0;
}

int* create_array(int size) {
    int* a = malloc(sizeof(int) * size);
    return a;
}
int* create_array_stack(int size) {
    int a[size];
    return a;
}

// stack

// stack vs heap

// stack is faster              || heap is slower               //
// stack is limited in size     || heap is limited by memory    //
// stack is automatic           || heap is manual               //
// stack is local               || heap is global               //
// stack is temporary           || heap is permanent            //
// stack is fast to allocate    || heap is slow to allocate     //
// stack is fast to deallocate  || heap is slow to deallocate   //
// stack is not thread safe     || heap is thread safe          //
// stack is not persistent      || heap is persistent           //
// stack is not dynamic         || heap is dynamic              //
// stack is not resizable       || heap is resizable            //
// stack is not flexible        || heap is flexible             //
