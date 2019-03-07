#include <stdint.h>
#include <stdlib.h>

#include "msg.h"
#include "lurker.h"

int32_t lurker_handle_request(lurker_object_t *objP, uint8_t *msg, uint16_t len)
{
    int32_t ret = 0;
    tag_list_t tag_list;

    if (msg == NULL || len < 3 || NULL == objP) {
        ret = -1;
        goto out;
    }

    ret = lurker_msg_readobj(objP, msg, len);

    if (ret != 0) {
        goto out;
    }

    switch (objP->code)
    {
        case OP_READ:
            objP->read(objP);
            break;
        case OP_WRITE:
            objP->write(objP);
            break;
        case OP_EXECUTE:
            objP->execute(objP);
            break;
        default:
            ret = LURKER_ERR_902;
            break;
    }

    out:
    return ret;
}
