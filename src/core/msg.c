#include <stdlib.h>
#include <stdint.h>

#include "lurker.h"
#include "msg.h"

int32_t lurker_serialize_obj(uint8_t *buf, lurker_object_t *objP)
{
    int32_t ret = 0;

    if (NULL == buf || NULL == objP ) {
        ret = -1;
        goto out;
    }

    ret = 0;
    buf[ret] = objP->code;
    ret += 1;
    buf[ret] = objP->uri.object;
    ret += 1;
    buf[ret] = objP->uri.instance;
    ret += 1;
    buf[ret] = objP->uri.resource;
    ret += 1;

    if (objP->user_data_len > 0 || NULL != objP->user_data) {
        memcpy(buf+ret, objP->user_data, objP->user_data_len);
        ret += objP->user_data_len;
    }

    out:
    return ret;
}

int32_t lurker_msg_readobj(lurker_object_t *objP, void *data, uint16_t len)
{
    int32_t ret = 0;
    uint8_t *p_data = (uint8_t *)data;
    uint16_t offset = 0;

    if (NULL == objP || NULL == data || 3 > len) {
        ret = -1;
        goto out;
    }

    objP->user_data == NULL;
    objP->user_data_len = 0;
    objP->code = p_data[offset];
    offset += 1;
    objP->uri.object = p_data[offset];
    offset += 1；
    objP->uri.instance = p_data[offset];
    offset += 1；
    objP->uri.resource = p_data[offset];
    offset += 1；

    if (len - offset > 0) {
        objP->user_data = buf+offset;
        msg->user_data_len = len - offset;
    }

    out:
    return ret;
}