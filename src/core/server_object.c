#include <stdlib.h>

#include "lurker.h"


static int32_t prv_server_read(uint32_t instanceId, tag_list_t tag_list, lurker_object_t *lurker_object)
{
    int ret = 0;

    out:
    return ret;
}

static int32_t prv_server_write(uint32_t instanceId, tag_list_t tag_list, lurker_object_t *lurker_object)
{
    int ret = 0;

    out:
    return ret;
}

lurker_object_t * get_server_object(int id)
{
    lurker_object_t *server_obj;

    server_obj = lurker_malloc(sizeof(lurker_object_t));

    if (server_obj == NULL) {
        goto out;
    }

    server_obj->read = prv_server_read;
    server_obj->write = prv_server_write;
out:
    return server_obj;
}