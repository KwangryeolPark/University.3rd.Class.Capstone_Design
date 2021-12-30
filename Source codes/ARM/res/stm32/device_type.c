#include "device_type.h"

/*

  Check 1076 page in RM0008 Reference manual
  30 Memory size registers

*/

volatile struct _DEVICE_TYPE *DEVICE_TYPE = (struct _DEVICE_TYPE *) 0x1FFFF7E0;

char DEVICE_TYPE_GET_TYPE(void) {
  uint16_t storage = DEVICE_TYPE -> F_SIZE;
  
  if (16 <= storage && storage <= 32) {
    return 'L';
  } else if (64 <= storage && storage <= 128) {
    return 'M';
  } else if (256 <= storage && storage <= 512) {
    return 'H';
  } else if (768 <= storage && storage <= 1024) {
    return 'X';
  }
  
  return '?';
}

uint16_t DEVICE_TYPE_GET_FLASH_SIZE(void) {
  return DEVICE_TYPE -> F_SIZE;
}
