#include <stdlib.h>

#include "msg.h"

int32_t lurker_serialize_msg(uint8_t *buf, msg_t *msg)
{
    int32_t ret = 0;

    if (NULL == buf || NULL == msg) {
        ret = -1;
        goto out;
    }

    ret = 0;
    buf[ret] = msg->instanceId;
    ret += 1;
    buf[ret] = msg->type;
    ret += 1;
    if (msg->len > 0 || NULL != msg->msg) {
        memcpy(buf+ret, msg->msg, msg->len);
        ret += msg->len;
    }

    out:
    return ret;
}

int32_t lurker_msg_readobj(uint8_t *buf, uint16_t len, msg_t *msg)
{
    int32_t ret = 0;

    if (NULL == buf || NULL == msg || len <= 1) {
        ret = -1;
        goto out;
    }

    msg->instanceId = buf[ret];
    ret += 1;
    msg->type = buf[ret];
    ret += 1;

    if (len-ret > 0) {
        msg->msg = buf+2;
        msg->len = len - 2;
    }

    out:
    return ret;
}