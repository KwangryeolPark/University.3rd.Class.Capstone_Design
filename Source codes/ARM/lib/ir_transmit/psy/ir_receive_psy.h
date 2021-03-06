/*
 * 박광렬
 * pkr7098@gmail.com
 * 2021-12-30
 * ir_receive_psy.h
 * IR의 물리 계 층 
 
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

// =============================================================================

#define IR_RECEIVE_THRESHOLD_IDLE       70
#define IR_RECEIVE_THRESHOLD_ONE        50
#define IR_RECEIVE_THRESHOLD_ZERO       IR_RECEIVE_THRESHOLD_ONE

#define IR_RECEIVE_STEP_IDLE    0
#define IR_RECEIVE_STEP_START   1
#define IR_RECEIVE_STEP_GET_SIZE        2
#define IR_RECEIVE_STEP_GET_DATA        3

// =============================================================================

// =============================================================================

void IR_RECEIVE_TIMER_INIT(void);
void IR_RECEIVE_TIMER_ENABLE(void);
void IR_RECEIVE_EXTI_INIT(void);
void IR_RECEIVE_EXTI_ENABLE(void);
void IR_RECEIVE_PORT_INIT(void);
void IR_RECEIVE_INIT(void);

// =============================================================================

uint8_t IR_RECEIVE_DECODER(uint8_t *buf);

// =============================================================================

#endif
