#ifndef _DEVICE_TYPE_H
#define _DEVICE_TYPE_H

#include "typedef.h"

struct _DEVICE_TYPE {
  uint16_t F_SIZE;
};

extern volatile struct _DEVICE_TYPE *DEVICE_TYPE;

char DEVICE_TYPE_GET_TYPE(void);
uint16_t DEVICE_TYPE_GET_FLASH_SIZE(void);

#endif