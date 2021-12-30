#include "ir_receive_psy.h"

// =============================================================================

// PB10
#define IR_RECEIVE_RCC_ENABLE   RCC -> APB2ENR  |=      (1 << 3)
#define IR_RECEIVE_CTRL_CLEAR   GPIOB -> CRH    &=      ~(0x000F << 8)
#define IR_RECEIVE_CTRL_SET     GPIOB -> CRH    |=      (4 << 8)
#define IR_RECEIVE_READ         (GPIOB -> IDR & (1 << 10))

// =============================================================================

volatile unsigned int IR_RECEIVE_COUNTER = 0;
volatile unsigned int index = 0;
volatile unsigned int msgs[1024] = {0, };

// =============================================================================

extern "C" {    //      Notify that the below functions are unique in C++
  void TIM3_IRQHandler(void);
  void EXTI15_10_IRQHandler(void);
};

void TIM3_IRQHandler(void) {            //      A hanlder for TIM3
  TIM3 -> SR    =       0;              //      You need to reclear it manually and it should not be deleted. (important)
  IR_RECEIVE_COUNTER++;
}

void EXTI15_10_IRQHandler(void) { // EXTI10이 발생되면 호출되는 Handler입니다. (정확히는 EXTI15 ~ 10 중 하나라도 발생한다면)
  //Handler이름은 startup_stm32f10x_hd_vl.s에 정의되어 있습니다. 
  if(EXTI -> PR & (1 << 10)) {   // EXTI15 ~ 10중에 EXTI10이 발생된 것인지 확인합니다.
    EXTI -> PR |= (1 << 10);     // EXTI10가 한 번 발생되었기 때문에 다시 0으로 만들어 줍니다. (1을 write하면 하드웨어적으로 0으로 초기화 됩니다.)
    if(index <= 1023) {
      msgs[index++] = IR_RECEIVE_COUNTER;
    }
    IR_RECEIVE_COUNTER = 0;
  }
}
// =============================================================================

void IR_RECEIVE_TIMER_INIT(void) {
  /*
    Intialize TIM3 and set its clock to 74 KHz
  */

  RCC ->        APB1ENR |=      (1 << 1);       //      Enable TIM3  

  TIM3 ->       PSC     =       (72 - 1);       //      72,000,000 / (72 - 1 + 1) = 1 MHz
  TIM3 ->       ARR     =       (50);           //      1 MHz / (50 - 1 + 1) = 20 KHz = 50 us
  TIM3 ->       CNT     =       0;              //      Initialize the TIM3 begin value
  TIM3 ->       SR      =       0;              //      Clear all status about TIM3
}

void IR_RECEIVE_TIMER_ENABLE(void) {
  /*
    Enable TIM3
  */
  
  NVIC_ISER0            |=      (1 << 29);      //      Connect TIM3 to NVIC
  
  TIM3 ->       DIER    =       (1 << 0);       //      Activate TIM3 interrupt
  TIM3 ->       EGR     =       (1 << 0);       //      Notify the the registers are updated
  TIM3 ->       CR1     =       (1 << 0);       //      Begin TIM2

}
void IR_RECEIVE_EXTI_INIT(void) {
  RCC ->        APB2ENR |=      (1 << AFIOEN);  //      Enable AFIO
  AFIO ->       EXTICR3 &=      ~(0xF << 8);    //      Select EXTI10 to PB10
  AFIO ->       EXTICR3 |=      (0x1 << 8);     //      Select EXTI10 to PB10
}

void IR_RECEIVE_EXTI_ENABLE(void) {
  NVIC_ISER1            |=      (1 << 8);       //      Connect EXTI10 to NVIC
  
  EXTI ->       FTSR    |=      (1 << 10);      //      Generate EXTI10 interrupt at falling edge
  EXTI ->       IMR     |=      (1 << 10);      //      Unmask the EXTI10 interrupt
}

void IR_RECEIVE_PORT_INIT(void) {
  IR_RECEIVE_RCC_ENABLE;
  IR_RECEIVE_CTRL_CLEAR;
  IR_RECEIVE_CTRL_SET;
}

void IR_RECEIVE_INIT(void) {
  IR_RECEIVE_TIMER_INIT();
  IR_RECEIVE_EXTI_INIT();
  IR_RECEIVE_PORT_INIT();
  IR_RECEIVE_TIMER_ENABLE();
  IR_RECEIVE_EXTI_ENABLE();
}

// =============================================================================
