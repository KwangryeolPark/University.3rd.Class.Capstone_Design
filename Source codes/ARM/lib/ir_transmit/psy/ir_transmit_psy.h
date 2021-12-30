/*
  IR 네트워크의 물리계층에 관한 파일입니다.
*/

#ifndef _IR_TRANSMIT_H
#define _IR_TRANSMIT_H

// =============================================================================

#include "rcc.h"
#include "tim.h"
#include "nvic.h"
#include "delay.h"
#include "gpio.h"
#include "typedef.h"
#include "ir_structs.h"

// =============================================================================

#define TIM2_500_US_COUNT       40                              //      The count of TIM2 to be 500 us

// =============================================================================

void IR_TRANSMIT_MODULATION_TIMER_INIT(void);
void IR_TRANSMIT_MODULATION_TIMER_ENABLE(void);
void IR_TRANSMIT_PORT_INIT(void);
void IR_TRANSMIT_INIT(void);

// =============================================================================

void IR_TRANSMIT_SIGNAL_ONE(void);
void IR_TRANSMIT_SIGNAL_ZERO(void);
void IR_TRANSMIT_SEND_BYTE(uint8_t byte);
void IR_TRANSMIT_SEND_FRAME(struct IR_FRAME *frame);

#endif