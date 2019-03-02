#include <stdlib.h>

#include "lurker.h"
#include "tlv.h"
#include "Emvtransflow.h"
#include "tag.h"
#include "hal.h"
#include "msg.h"

#define OBJ_HIGHER_APP          1
#define INSTANCE_APP            0


typedef enum _lurker_kernel_res_t{
    KERNEL_RES_TRANSACTION,
    KERNEL_RES_CANCEL,
}lurker_kernel_res_t;

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

static int32_t prv_kernel_write(lurker_object_t *objP)
{
    int ret = 0;
    tlv_list_t *list = NULL;
    TlvObj *tlv_obj = NULL;
    int offset = 0;

    if (NULL == objP || NULL == objP->user_data || 0 > objP->user_data_len) {
        ret = LURKER_ERR_900;
        goto out;
    }

    ret = tlv_read_data(list, objP->user_data, objP->user_data_len, on_read_obj);

    if (0!=ret) {
        ret = LURKER_ERR_903;
        goto out;
    }

    objP->user_data_len = 0;

    while(list != NULL){
        tlv_obj = getTlvObjRef(list->tlv.tag);
        if (tlv_obj != NULL && tlv_obj->length > 0) {
            list->tlv.len = tlv_obj->length;
            list->tlv.value = tlv_obj->value;
            ret = tlv_write_obj(objP->user_data+offset, &list->tlv);
            offset += ret;
        }
        list = list->next;
    }

    out:
    return ret;
}

static int32_t prv_kernel_read(lurker_object_t *objP,tlv_list_t *list)
{
    int ret = 0;
    TlvObj tlv_obj;
    int offset = 0;
    #define MAX_BUF_SIZE        512
    uint8_t buf[MAX_BUF_SIZE];
    uint16_t len = MAX_BUF_SIZE;
    tlv_list_t *exp_list = NULL;

    if (NULL == objP || NULL == objP->user_data || 0 >= objP->user_data_len) {
        ret = LURKER_ERR_900;
        goto out;
    }

    ret = 0;
    offset = 0;
    objP->code = OP_READ;
    objP->uri.object = OBJ_HIGHER_APP;
    objP->uri.instance = INSTANCE_APP;
    objP->uri.resource = KERNEL_RES_TRANSACTION;
    ret = LURKER_ERR_900;

    while(NULL != list){
        len = tlv_write_obj(objP->user_data+offset, &list->tlv);
        CHECK_LEN();
        offset +=  len;
    }

    len = lurker_serialize_msg(buf, objP);
    CHECK_LEN();
    ret = hal_connection_send(buf,len);
    CHECK_RET_EN(LURKER_ERR_907);

    ret = LURKER_ERR_906;
    len = hal_connection_recv(buf, len, objP->timeout);
    CHECK_LEN();

    ret = lurker_msg_readobj(objP, buf, len);
    CHECK_RET_EN(LURKER_ERR_903);

    ret = tlv_read_data(exp_list, objP->user_data, objP->user_data_len, on_read_obj);
    CHECK_RET_EN(LURKER_ERR_903);

    while(list != NULL){
        ret = saveTermTlvObjEx(list->tlv.tag, list->tlv.len, list->tlv.value, NULL);
        CHECK_RET_EN(LURKER_ERR_905);
        list = list->next;
    }

    out:
    return ret;
}

static int32_t _kernel_launch_transaction(tlv_list_t *tlv_list)
{
    int32_t ret = 0;
    char *date = 0;
    uint32_t seq_no = 0;
    tlv_t *pTlv = NULL;
    uint32_t slot = 0;

    if (NULL == tlv_list) {
        ret = LURKER_ERR_903;
        goto out;
    }

    if (!CHECK_OBJ(TAG_TRANSACTION_DATE, tlv_list) || !CHECK_OBJ(TAG_TRANS_SEQ_COUNTER, tlv_list) ||
     !CHECK_OBJ(TAG_SLOT, tlv_list)) {
        ret = LURKER_ERR_903;
        goto out;
    }

    pTlv = tlv_list_get_obj(TAG_TRANSACTION_DATE, tlv_list);
    date = tlv_read_as_string(pTlv);
    pTlv = tlv_list_get_obj(TAG_TRANS_SEQ_COUNTER, tlv_list);
    seq_no = tlv_read_as_int(pTlv);
    pTlv = tlv_list_get_obj(TAG_SLOT, tlv_list);
    slot = tlv_read_as_int(pTlv);

    ret = TransFlow_InitTransaction(seq_no, date, slot);
    out:
    return ret;
}

static int32_t _kernel_execute_transaction(lurker_object_t *objP, tlv_list_t *l)
{
    int32_t ret = 0;
    tlv_list_t *list = NULL;
    tlv_list_t *node = NULL;
    uint32_t index = 0;
    uint32_t amount = 0;
    uint32_t other_amount = 0;
    tlv_t *pTlv = NULL;

    ret = _kernel_launch_transaction(l);
    CHECK_RET();

    node = (tlv_list_t *)lurker_malloc(sizeof(tlv_list_t));
    CHECK_MEM(node);
    node->tlv.tag = TAG_INDEX;
    node->next = NULL;
    ADD_TO_LIST(list, node);

    node = (tlv_list_t *)lurker_malloc(sizeof(tlv_list_t));
    CHECK_MEM(node);
    node->tlv.tag = TAG_AMOUNT;
    node->next = NULL;
    ADD_TO_LIST(list, node);

    node = (tlv_list_t *)lurker_malloc(sizeof(tlv_list_t));
    CHECK_MEM(node);
    node->tlv.tag = TAG_AMOUNT_OTHER;
    node->next = NULL;
    ADD_TO_LIST(list, node);

    ret = prv_kernel_read(objP,list);
    CHECK_RET();

    if (!CHECK_OBJ(TAG_INDEX, tlv_list) || !CHECK_OBJ(TAG_AMOUNT, tlv_list) ||
     !CHECK_OBJ(TAG_AMOUNT_OTHER, tlv_list)) {
        ret = LURKER_ERR_903;
        goto out;
    }

    pTlv = tlv_list_get_obj(TAG_INDEX, list);
    index = tlv_read_as_int(pTlv);
    pTlv = tlv_list_get_obj(TAG_AMOUNT, list);
    amount = tlv_read_as_int(pTlv);
    pTlv = tlv_list_get_obj(TAG_AMOUNT_OTHER, list);
    other_amount = tlv_read_as_int(pTlv);

    ret = TransFlow_StartTransaction(index, amount, other_amount);
    out:
    lurker_free_list(list, tlv_list_t *);
    return ret;
}

static int32_t prv_kernel_excute(lurker_object_t *objP)
{
    int ret = 0;
    tlv_list_t *list = NULL;
    TlvObj tlv_obj;
    int offset = 0;

    if (NULL == objP || NULL == objP->user_data || 0 >= objP->user_data_len) {
        ret = LURKER_ERR_900;
        goto out;
    }

    ret = tlv_read_data(list, objP->user_data, objP->user_data_len, on_read_obj);

    if (0!=ret) {
        ret = LURKER_ERR_903;
        goto out;
    }

    switch (objP->uri.resource)
    {
        case KERNEL_RES_TRANSACTION:

            ret = _kernel_execute_transaction(objP, list);

            break;
        case KERNEL_RES_CANCEL:
            break;

        default:
            break;
    }

    out:
    lurker_free_list(list, tlv_list_t *);
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
    kernel_obj->execute = prv_kernel_excute;

out:
    return kernel_obj;
}