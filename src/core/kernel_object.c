#include <stdlib.h>

#include "lurker.h"



static int32_t prv_kernel_read(uint32_t instanceId, tag_list_t tag_list, lurker_object_t *lurker_object)
{
    int ret = 0;

    out:
    return ret;
}

static int32_t prv_kernel_write(uint32_t instanceId, tag_list_t tag_list, lurker_object_t *lurker_object)
{
    int ret = 0;

    out:
    return ret;
}

lurker_object_t * get_kernel_object(int id)
{
    lurker_object_t *kernel_obj;

    kernel_obj = lurker_malloc(sizeof(lurker_object_t));

    if (kernel_obj == NULL) {
        goto out;
    }

    kernel_obj->read = prv_kernel_read;
    kernel_obj->write = prv_kernel_write;
out:
    return kernel_obj;
}