/*
  IR 네트워크의 물리계층에 관한 파일입니다.
*/

#ifndef _IR_RECEIVE_H
#define _IR_RECEIVE_H

// =============================================================================

#include "rcc.h"
#include "tim.h"
#include "nvic.h"
#include "gpio.h"
#include "typedef.h"
#include "ir_structs.h"
#include "afio.h"
#include "exti.h"

extern volatile unsigned int IR_RECEIVE_COUNTER;
extern volatile unsigned int msgs[1024];

// =============================================================================

void IR_RECEIVE_TIMER_INIT(void);
void IR_RECEIVE_TIMER_ENABLE(void);
void IR_RECEIVE_EXTI_INIT(void);
void IR_RECEIVE_EXTI_ENABLE(void);
void IR_RECEIVE_PORT_INIT(void);
void IR_RECEIVE_INIT(void);

// =============================================================================

#endif