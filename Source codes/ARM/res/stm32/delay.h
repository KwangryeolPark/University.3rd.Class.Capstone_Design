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