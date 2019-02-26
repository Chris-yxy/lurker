#ifndef _LURKER_H_
#define _LURKER_H_
#include <stdint.h>

typedef struct _lurker_object_t lurker_object_t;

typedef struct _tag_list_t{
    void *list;
    uint16_t len;
}tag_list_t;

typedef int (*lurker_read_callback_t)(uint32_t instanceId, tag_list_t tag_list, lurker_object_t *lurker_object);
typedef int (*lurker_write_callback_t)(uint32_t instanceId, tag_list_t tag_list, lurker_object_t *lurker_object);

struct _lurker_object_t
{
    struct _lurker_object_t *next;
    uint16_t obj_id;

    lurker_read_callback_t read;
    lurker_write_callback_t write;

    uint8_t *user_data;
    uint16_t user_data_len;
};

#define lurker_malloc malloc
#define lurker_free(p) do{\
                            if (NULL != (p)) {\
                                free((p));\
                            }\
                        } while (0)

typedef enum _lurker_error_t{
    LURKER_ERR_900 = 900, //invalid parameters
    LURKER_ERR_901 = 901, //oom
    LURKER_ERR_902 = 902, //operation unsupported
    LURKER_ERR_903 = 903, //parse user data failed
    LURKER_ERR_904 = 904, //write data failed
}lurker_error_t;
#endif