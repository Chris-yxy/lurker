#include <stdint.h>
#include <stdlib.h>

#include "msg.h"
#include "lurker.h"

int32_t lurker_handle_request(lurker_object_t *objP,uint8_t *raw, uint16_t len)
{
    int32_t ret = 0;
    msg_t msg;
    tag_list_t tag_list;

    if (raw == NULL || len <1 || NULL == objP) {
        ret = -1;
        goto out;
    }

    ret = lurker_msg_readobj(raw, len, &msg);

    if (ret != 0) {
        goto out;
    }

    tag_list.list = msg.msg;
    tag_list.len = msg.len;

    switch (msg.type)
    {
        case OP_READ:
            objP->read(msg.instanceId,tag_list, objP);
            break;
        case OP_WRITE:
            objP->write(msg.instanceId, tag_list, objP);
            break;
        default:
            ret = LURKER_ERR_902;
            break;
    }

    out:
    return ret;
}
