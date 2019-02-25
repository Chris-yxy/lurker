#ifndef _HAL_H_
#define _HAL_H_

#include <stdint.h>

int32_t connection_send(void *buf, uint16_t len);

int32_t connection_recv(void *buf, uint16_t len, uint16_t timeout_ms);

#endif