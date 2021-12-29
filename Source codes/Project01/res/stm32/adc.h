#ifndef _ADC_H
#define _ADC_H

#include "typedef.h"

struct _ADC {
  uint32_t        SR;
  uint32_t        CR1;
  uint32_t        CR2;
  uint32_t        SMPR1;
  uint32_t        SMPR2;
  uint32_t        JOFR1;
  uint32_t        JOFR2;
  uint32_t        JOFR3;
  uint32_t        JOFR4;
  uint32_t        HTR;
  uint32_t        LTR;
  uint32_t        SQR1;
  uint32_t        SQR2;
  uint32_t        SQR3;
  uint32_t        JSQR;
  uint32_t        JDR1;
  uint32_t        JDR2;
  uint32_t        JDR3;
  uint32_t        JDR4;
  uint32_t        DR;
};

volatile struct _ADC *ADC1 = (struct _ADC*) 0x40012400;
volatile struct _ADC *ADC2 = (struct _ADC*) 0x40012800;
volatile struct _ADC *ADC3 = (struct _ADC*) 0x40013C00;

#endif