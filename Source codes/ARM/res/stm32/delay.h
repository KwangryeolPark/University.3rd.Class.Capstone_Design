/*
 * ?ڱ???
 * pkr7098@gmail.com
 * 2021-12-29
 * delay.h
 * delay ???? 
 
*/

#ifndef _DELAY_H
#define _DELAY_H

// =============================================================================

#include "rcc.h"
#include "tim.h"
#include "nvic.h"

// =============================================================================

void DELAY_TIMER_INIT(void);
void DELAY_TIMER_ENABLE(void);
void delay_ms(unsigned int delay);
void DELAY_INIT(void);

// =============================================================================

#endif
