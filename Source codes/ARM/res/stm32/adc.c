#include "adc.h"

volatile struct _ADC *ADC1 = (struct _ADC*) 0x40012400;
volatile struct _ADC *ADC2 = (struct _ADC*) 0x40012800;
volatile struct _ADC *ADC3 = (struct _ADC*) 0x40013C00;

