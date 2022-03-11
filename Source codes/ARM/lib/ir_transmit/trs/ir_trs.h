/*
 * 박광렬
 * pkr7098@gmail.com
 * 2021-12-31
 * ir_trs.h
 * IR의 데이터링크 계 층 

ADC           :       12 MHz
12bits

*/

#ifndef _IR_TRS_H
#define _IR_TRS_H

// =============================================================================

#include "typedef.h"
#include "ir_transmit_psy.h"
#include "ir_receive_psy.h"
#include "ir_structs.h"
#include "uid.h"
#include "rcc.h"
#include "adc.h"

// =============================================================================
void IR_ANALOG_INIT(void);
void IR_TRANSMIT_TRS_INIT(void);
uint16_t IR_LEVEL_WAIT(void);
uint16_t IR_LEVEL(void);
uint16_t IR_LEVEL_AVG(void);
unsigned char GET_EVEN_PARITY(unsigned char c);
unsigned char GET_ODD_PARITY(unsigned char c);
void IR_TRANSMIT_SEND_DATAGRAM(struct IR_DATAGRAM *datagram);
void IR_TRANSMIT_RECEIVE_DARAGRAM(void);

// =============================================================================

// =============================================================================

// =============================================================================

extern uint8_t uid8;

// =============================================================================

#endif
