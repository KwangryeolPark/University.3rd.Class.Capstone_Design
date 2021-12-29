#ifndef _DELAY_H
#define _DELAY_H

#include "rcc.h"
#include "tim.h"
#include "nvic.h"

volatile unsigned int DELAY_COUNT = 0;

extern "C" {    //      Notify that the below functions are unique in C++
  void TIM7_IRQHandler(void);
}

void TIM7_IRQHandler(void) {
  TIM7 ->        SR      =       0;      //      You need to reclear it manually and it should not be deleted. (important)

  if (DELAY_COUNT) {
    DELAY_COUNT--;
  }
}

// ==================================================================================================================================

void initTIM7(void);
void enableTIM7(void);
void delay_ms(unsigned int delay);
void initDelay(void);

void initTIM7(void) {
  /*
    Intialize TIM7 and set its clock to 100 KHz
  */

  RCC ->        APB1ENR |=      (1 << 8);       //      Enable Timer2
  
  TIM7 ->       PSC     =       (73 - 1);       //      72,000,000 / (73 - 1) = 1 MHz
  TIM7 ->       ARR     =       100 - 1;        //      1 MHz / (1000 - 1 + 1) = 100 KHz
  TIM7 ->       CNT     =       0;              //      Initialize the TIM2 begin value
  TIM7 ->       SR      =       0;              //      Clear all status about TIM2
}

void enableTIM7(void) {
  /*
    Enable TIM7
  */
  TIM7 ->       DIER    =       (1 << 0);       //      Activate TIM7 interrupt
  NVIC_ISER1            =       (1 << 24);      //      Connect TIM7 to NVIC
  
  TIM7 ->       EGR     =       (1 << 0);       //      Notify the the registers are updated
  TIM7 ->       CR1     =       (1 << 0);       //      Begin TIM7
}

void delay_ms(unsigned int delay) {
  /*
    Delay program flow for delay msecs
  */
  
  DELAY_COUNT = delay * 100;
  while (DELAY_COUNT > 0);
}

void initDelay(void) {
  initTIM7();
  enableTIM7();
}

#endif