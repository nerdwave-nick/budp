#ifndef BUDP_MESSAGE_H
#define BUDP_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BUDP_MESSAGE_TYPE_CONN_REQ = 0,
    BUDP_MESSAGE_TYPE_CONN_REP = 1,
    BUDP_MESSAGE_TYPE_PING = 2,
    BUDP_MESSAGE_TYPE_PONG = 4,
    BUDP_MESSAGE_TYPE_DATA = 8,
    BUDP_MESSAGE_DISCONNECT = 16
} budp_message_type;

typedef struct {
    unsigned int header;
    budp_message_type type;
    int length;
    char data[];
} budp_message;

typedef struct {
    unsigned int header;
    budp_message_type type;
    int length;
    int id;
    char data[];
} budp_message_conn_req;

typedef struct {
    unsigned int header;
    budp_message_type type;
    int length;
    int id;
    char data[];
} budp_message_conn_rep;

typedef struct {
    unsigned int header;
    budp_message_type type;
    int length;
    int id;
    char data[];
} budp_message_ping;

typedef struct {
    unsigned int header;
    budp_message_type type;
    int length;
    int id;
    char data[];
} budp_message_pong;

typedef struct {
    unsigned int header;
    budp_message_type type;
    int length;
    int id;
    char data[];
} budp_message_data;

typedef struct {
    unsigned int header;
    budp_message_type type;
    int length;
    int id;
    char data[];
} budp_message_disconnect;

#ifdef __cplusplus
}
#endif
#endif