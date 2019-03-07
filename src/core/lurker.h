#ifndef _LURKER_H_
#define _LURKER_H_
#include <stdint.h>

typedef struct _lurker_object_t lurker_object_t;

typedef struct _tag_list_t{
    void *list;
    uint16_t len;
}tag_list_t;

typedef struct _lurker_uri
{
    uint8_t object;
    uint8_t instance;
    uint8_t resource;
}lurker_t;

typedef enum _operation_t{
    OP_READ,
    OP_WRITE,
    OP_EXECUTE,
}operation_t;

typedef int (*lurker_read_callback_t)(lurker_object_t *lurker_object);
typedef int (*lurker_write_callback_t)(lurker_object_t *lurker_object);
typedef int (*lurker_execute_callback_t)(lurker_object_t *lurker_object);

struct _lurker_object_t
{
    struct _lurker_object_t *next;
    uint16_t obj_id;

    lurker_read_callback_t read;
    lurker_write_callback_t write;
    lurker_execute_callback_t execute;
    uint8_t code;
    lurker_t uri;
    uint8_t *user_data;
    uint16_t user_data_len;
    uint16_t timeout;
};

#define lurker_malloc malloc
#define lurker_free(p) do{\
                            if (NULL != (p)) {\
                                free((p));\
                            }\
                        } while (0)

#define lurker_free_list(l, T) do{\
                            (T) p = (T)(l);\
                            while (NULL != (p)) {\
                                free(p);\
                                p = p->next;\
                            }\
                        } while (0)


typedef enum _lurker_error_t{
    LURKER_ERR_900 = 900, //invalid parameters
    LURKER_ERR_901 = 901, //oom
    LURKER_ERR_902 = 902, //operation unsupported
    LURKER_ERR_903 = 903, //parse user data failed
    LURKER_ERR_904 = 904, //resource not found
    LURKER_ERR_905 = 905, //resource access failed
    LURKER_ERR_906 = 906, //timeout
    LURKER_ERR_907 = 907, //send failed
}lurker_error_t;

#define CHECK_RET() do\
                            {\
                                if (ret != 0) {\
                                    goto out;\
                                }\
                            } while (0)

#define CHECK_RET_EN(err_no) do\
                            {\
                                if (ret != 0) {\
                                    ret = (err_no);\
                                    goto out;\
                                }\
                            } while (0)

#define CHECK_LEN() do\
                            {\
                                if ( len <= 0) {\
                                    goto out;\
                                }\
                            } while (0)

#define CHECK_MEM(m) do\
                            {\
                                if ( (m)) == NULL) {\
                                    ret = LURKER_ERR_901;\
                                    goto out;\
                                }\
                            } while (0)


#endif