/*
 * ¹Ú±¤·Ä
 * pkr7098@gmail.com
 * 2021-12-29
 * delay.c
 * delay °ü·Ã 
 
*/

#include "delay.h"

// =============================================================================

volatile unsigned int DELAY_COUNT = 0;

// =============================================================================

extern "C" {    //      Notify that the below functions are unique in C++
  void TIM4_IRQHandler(void);
};

void TIM4_IRQHandler(void) {
  TIM4 ->        SR      =       0;      //      You need to reclear it manually and it should not be deleted. (important)
  
  if (DELAY_COUNT > 0) {
    DELAY_COUNT--;
  } else {
    DELAY_COUNT = 0;
  }
}

// =============================================================================

void DELAY_TIMER_INIT(void) {
  /*
    Intialize TIM4 and set its clock to 100 KHz
  */

  RCC ->        APB1ENR |=      (1 << 2);       //      Enable TIM4
  
  TIM4 ->       PSC     =       (72 - 1);       //      72,000,000 / (72 - 1 + 1) = 1 MHz
  TIM4 ->       ARR     =       (10 - 1);       //      1 MHz / (10 - 1 + 1) = 100 KHz
  TIM4 ->       CNT     =       0;              //      Initialize the TIM4 begin value
  TIM4 ->       SR      =       0;              //      Clear all status about TIM2
}

void DELAY_TIMER_ENABLE(void) {
  /*
    Enable TIM4
  */
  
  NVIC_ISER0            |=      (1 << 30);      //      Connect TIM4 to NVIC

  TIM4 ->       DIER    =       (1 << 0);       //      Activate TIM4 interrupt
  TIM4 ->       EGR     =       (1 << 0);       //      Notify the the registers are updated
  TIM4 ->       CR1     =       (1 << 0);       //      Begin TIM4	
}

void delay_ms(unsigned int delay) {
  /*
    Delay program flow for delay msecs
  */
  
  DELAY_COUNT = delay * 100;
  while (DELAY_COUNT > 0);
}

void DELAY_INIT(void) {
  DELAY_TIMER_INIT();
  DELAY_TIMER_ENABLE();
}

