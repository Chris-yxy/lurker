#ifndef _MSG_H_
#define _MSG_H_
#include <stdint.h>

typedef struct _msg_t{
    uint8_t instanceId;
    uint8_t type;
    void *msg;
    uint16_t len;
}msg_t;

int32_t lurker_serialize_msg(uint8_t *buf, msg_t *msg);

int32_t lurker_msg_readobj(uint8_t *buf, uint16_t len, msg_t *msg);

typedef enum _operation_t{
    OP_READ,
    OP_WRITE,
}operation_t;

#endif