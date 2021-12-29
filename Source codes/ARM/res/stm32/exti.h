#ifndef _EXTI_H
#define _EXTI_H

#include "typedef.h"

struct _EXTI {
  uint32_t        IMR;
  uint32_t        EMR;
  uint32_t        RTSR;
  uint32_t        FTSR;
  uint32_t        SWIER;
  uint32_t        PR;
};

volatile struct _EXTI *EXTI = (struct _EXTI*) 0x40010400;

#endif