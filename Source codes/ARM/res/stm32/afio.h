#ifndef _AFIO_H
#define _AFIO_H

#include "typedef.h"

struct _AFIO {
  uint32_t        EVCR;
  uint32_t        MAPR;
  uint32_t        EXTICR1;
  uint32_t        EXTICR2;
  uint32_t        EXTICR3;
  uint32_t        EXTICR4;
  uint32_t        MAPR2;
};

volatile struct _AFIO *AFIO = (struct _AFIO*) 0x40010000;

#endif