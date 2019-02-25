

#ifndef _TLV_H_
#define _TLV_H_

#include <stdint.h>

typedef struct _tlv_t{
    uint32_t tag;
    uint16_t len;
    void *value;
}tlv_t;

typedef tlv_t*  tlv_pt;

typedef struct _tlv_list_t{
    tlv_pt *next;
    tlv_t tlv;
}tlv_list_t;

typedef struct _tlv_repo_t{
    tlv_pt repo;
    uint16_t capicity;
    uint16_t size;
}tlv_repo_t;

typedef tlv_repo_t* tlv_repo_pt;

typedef enum _tlv_attr_type_t{
    TLV_ATTR_TYPE_N,
    TLV_ATTR_TYPE_B,
    TLV_ATTR_TYPE_ANS,
}tlv_attr_type_t;

typedef enum _tlv_attr_len_type_t{
    TLV_ATTR_LEN_TYPE_FIX,
    TLV_ATTR_TYPE_VAR,
}tlv_attr_len_type_t;

typedef enum _tlv_attr_update_src_t{
    TLV_ATTR_UPDATE_SRC_K,
    TLV_ATTR_UPDATE_SRC_RA,
    TLV_ATTR_UPDATE_SRC_ACT,
    TLV_ATTR_UPDATE_SRC_DET,
}tlv_attr_update_src_t;

typedef struct _tlv_attr_t{
    tlv_attr_type_t type;
    tlv_attr_len_type_t len_type;
    tlv_attr_update_src_t update_src;
    uint16_t len;
}tlv_attr_t;

typedef struct _tlv_dict_item_t{
    uint32_t tag;
    tlv_attr_t attr;
}tlv_item_t;

typedef tlv_item_t* tlv_item_pt;

typedef struct _tlv_dict_t{
    tlv_item_pt items;
    int16_t size;
}tlv_dict_t;

typedef tlv_dict_t* tlv_dict_pt;

typedef struct _tlv_context_t{
    tlv_repo_pt tlv_repo;
    tlv_dict_pt tlv_dict;
}tlv_context_t;

typedef tlv_context_t* tlv_context_pt;

typedef int32_t (*onReadData)(uint32_t tag, uint16_t len, uint8_t *v, void *argv);

#define LYDIA_TLV_MORE_TAG(tag) (tag & 0x80)?LYDIA_TRUE:LYDIA_FALSE

#define LYDIA_TLV_SEE_CONTINUE(tag) ((tag & 0x1F) == 0x1F)?LYDIA_TRUE:LYDIA_FALSE

#define LYDIA_TLV_LEN_SIZE(len) (len & 0x80)?(len&0x7F):1

int32_t tlv_read_data(void *argv, uint8_t *data, uint16_t len,onReadData on_read_data);

int32_t tlv_write_obj(uint8_t *stream, tlv_t *tlv);

#define ADD_TO_LIST(list, node) do{\
                                        node->next = NULL; \
                                        if (NULL == list) {\
                                            list = node;\
                                        }else\
                                        {\
                                            list->next = node;\
                                        }\
                                } while (0)


#endif