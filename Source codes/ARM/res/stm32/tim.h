#ifndef _TIM_H
#define _TIM_H

// =============================================================================

#include "typedef.h"

// =============================================================================

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

// =============================================================================

extern volatile struct _TIM *TIM1;
extern volatile struct _TIM *TIM2;
extern volatile struct _TIM *TIM3;
extern volatile struct _TIM *TIM4;
extern volatile struct _TIM *TIM5;
extern volatile struct _TIM *TIM6;
extern volatile struct _TIM *TIM7;
extern volatile struct _TIM *TIM8;
extern volatile struct _TIM *TIM9;
extern volatile struct _TIM *TIM10;
extern volatile struct _TIM *TIM11;
extern volatile struct _TIM *TIM12;
extern volatile struct _TIM *TIM13;
extern volatile struct _TIM *TIM14;

#endif