#ifndef _TIM_H
#define _TIM_H

#include "typedef.h"

struct _TIM {
  uint32_t      CR1;
  uint32_t      CR2;
  uint32_t      SMCR;
  uint32_t      DIER;
  uint32_t      SR;
  uint32_t      EGR;
  uint32_t      CCMR1;
  uint32_t      CCMR2;
  uint32_t      CCER;
  uint32_t      CNT;
  uint32_t      PSC;
  uint32_t      ARR;
  uint32_t      RCR;
  uint32_t      CCR1;
  uint32_t      CCR2;
  uint32_t      CCR3;
  uint32_t      CCR4;
  uint32_t      BDTR;
  uint32_t      DCR;
  uint32_t      DMAR;
};

volatile struct _TIM *TIM1      = (struct _TIM*) 0x40012C00;
volatile struct _TIM *TIM2      = (struct _TIM*) 0x40000000;
volatile struct _TIM *TIM3      = (struct _TIM*) 0x40000400;
volatile struct _TIM *TIM4      = (struct _TIM*) 0x40000800;
volatile struct _TIM *TIM5      = (struct _TIM*) 0x40000C00;
volatile struct _TIM *TIM6      = (struct _TIM*) 0x40001000;
volatile struct _TIM *TIM7      = (struct _TIM*) 0x40001400;
volatile struct _TIM *TIM8      = (struct _TIM*) 0x40013400;
volatile struct _TIM *TIM9      = (struct _TIM*) 0x40014C00;
volatile struct _TIM *TIM10     = (struct _TIM*) 0x40015000;
volatile struct _TIM *TIM11     = (struct _TIM*) 0x40015400;
volatile struct _TIM *TIM12     = (struct _TIM*) 0x40001800;
volatile struct _TIM *TIM13     = (struct _TIM*) 0x40001C00;
volatile struct _TIM *TIM14     = (struct _TIM*) 0x40002000;

#endif