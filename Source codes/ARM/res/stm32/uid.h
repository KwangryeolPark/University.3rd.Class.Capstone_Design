#ifndef _UID_H
#define _UID_H

// =============================================================================

#include "typedef.h"

// =============================================================================

struct _UID {
  uint32_t      U_ID0;
  uint32_t      U_ID1;
  uint32_t      U_ID2;
};

// =============================================================================

extern volatile struct _UID *UID;

// =============================================================================

uint8_t UID_GET_BYTE(uint8_t UID_STEP);
uint16_t UID_GET_HALF_WORD(uint8_t UID_STEP);
uint32_t UID_GET_WORD(uint8_t UID_STEP);

#endif