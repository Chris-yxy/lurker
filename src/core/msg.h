#ifndef _MSG_H_
#define _MSG_H_
#include <stdint.h>

#include "lurker.h"


int32_t lurker_serialize_msg(uint8_t *buf, lurker_object_t *objP);

int32_t lurker_msg_readobj(lurker_object_t *objP, void *data, uint16_t len);



#endif