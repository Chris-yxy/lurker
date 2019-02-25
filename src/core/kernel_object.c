#include <stdlib.h>

#include "lurker.h"
#include "tlv.h"
#include "Emvtransflow.h"

int32_t on_read_obj(uint32_t tag, uint16_t len, uint8_t *v, void *argv)
{
    int ret = 0;
    tlv_list_t *list = (tlv_list_t *)argv;
    tlv_list_t *node = NULL;

    node = (tlv_list_t *)lurker_malloc(sizeof(tlv_list_t));

    if (NULL == list) {
        ret = LURKER_ERR_901;
        goto out;
    }

    node->tlv.tag = tag;
    node->tlv.len = len;
    node->tlv.value = v;
    ADD_TO_LIST(list, node);

    out:
    return ret;
}

static int32_t prv_kernel_read(uint32_t instanceId, tag_list_t *tag_list, lurker_object_t *lurker_object)
{
    int ret = 0;
    tlv_list_t *list = NULL;
    TlvObj *tlv_obj = NULL;
    int offset = 0;

    if (NULL == lurker_object || NULL == lurker_object->user_data) {
        ret = LURKER_ERR_900;
        goto out;
    }

    ret = tlv_read_data(list, tag_list->list, tag_list->len, on_read_obj);

    if (0!=ret) {
        ret = LURKER_ERR_903;
        goto out;
    }

    lurker_object->user_data_len = 0;
    while(list != NULL){
        tlv_obj = getTlvObjRef(list->tlv.tag);
        if (tlv_obj != NULL && tlv_obj->length > 0) {
            list->tlv.len = tlv_obj->length;
            list->tlv.value = tlv_obj->value;
            ret = tlv_write_obj(lurker_object->user_data+offset, &list->tlv);
            offset += ret;
        }
        list = list->next;
    }

    out:
    return ret;
}

// int32_t on_write_obj(uint32_t tag, uint16_t len, uint8_t *v, void *argv)
// {
//     int ret = 0;
//     tlv_list_t *list = (tlv_list_t *)argv;
//     tlv_list_t *node = NULL;

//     node = (tlv_list_t *)lurker_malloc(sizeof(tlv_list_t));

//     if (NULL == list) {
//         ret = LURKER_ERR_901;
//         goto out;
//     }

//     node->tlv.tag = tag;
//     node->tlv.len = len;
//     node->tlv.value = v;
//     ADD_TO_LIST(list, node);

//     out:
//     return ret;
// }

static int32_t prv_kernel_write(uint32_t instanceId, tag_list_t *tag_list, lurker_object_t *lurker_object)
{
    int ret = 0;
    tlv_list_t *list = NULL;
    TlvObj tlv_obj;
    int offset = 0;

    if (NULL == lurker_object || NULL == lurker_object->user_data) {
        ret = LURKER_ERR_900;
        goto out;
    }

    ret = tlv_read_data(list, tag_list->list, tag_list->len, on_read_obj);

    if (0!=ret) {
        ret = LURKER_ERR_903;
        goto out;
    }

    lurker_object->user_data_len = 0;
    while(list != NULL){
        // tlv_obj.tag = list->tlv.tag;
        // tlv_obj.length = list->tlv.len;
        // tlv_obj.value = list->tlv.value;
        ret = saveTermTlvObjEx(list->tlv.tag, list->tlv.len, list->tlv.value, NULL);
        if (ret != NULL) {
            ret = LURKER_ERR_904;
            goto out;
        }

        list = list->next;
    }

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