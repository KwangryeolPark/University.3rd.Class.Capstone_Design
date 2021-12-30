/*
SYSCLK        :       72 MHz
APB1          :       36 MHz
APB2          :       72 MHz
ADC           :       12 MHz

TIM2          :       80 KHz = 2 * 40 KHz
TIM2 is for IR transmitter.
The IR transmitter works at 40KHz for modulation

TIM3          :       50 us
TIM3 is for IR receiver.

TIM7          :       100 KHZ
TIM7 is for delay_ms.

*/

#include "rcc.h"
#include "delay.h"
#include "ir_transmit_psy.h"
#include "ir_receive_psy.h"
#include "printf.h"
#include "usart.h"
#include "string.h"

void RCC_INIT(void);

int main(void) {
  RCC_INIT();
  DELAY_INIT();
  IR_TRANSMIT_INIT();
  IR_RECEIVE_INIT();
  USART2_INIT();
  
  struct IR_FRAME frame;
  strcpy((char *) frame.p_datagram, "aj");
  frame.size_datagram = 3;
  for (int j = 0; j < 1000; j) {
    IR_TRANSMIT_SEND_FRAME(&frame);
    
    
    
    delay_ms(1000);
  }
  
  while (1);
}













void RCC_INIT(void) {
  /*
  Initalize RCC
  SYSCLK      :       72 MHz
  APB1        :       36 MHz
  APB2        :       72 MHz
  ADC         :       12 MHz
  */ 
  
  (*(unsigned long *) 0x40022000)     &=      ~(0x07);          //      Clear the register
  (*(unsigned long *) 0x40022000)     |=      (0x02);           //      Set the flash latency to mode two -> without changing it, the mcu cannot run at 72MHz clock.
  
  RCC ->        CFGR    =       0;              //      Reset value
  RCC ->        CFGR    &=      ~(1 << 17);     //      PLLXTPRE
  RCC ->        CFGR    |=      (1 << 16);      //      PLLSRC
  RCC ->        CFGR    |=      (7 << 18);      //      PLLMUL
  
  RCC ->        CFGR    |=      (4 << 8);       //      PPRE1 (APB1)
  RCC ->        CFGR    |=      (2 << 14);      //      ADCPRE
  
  RCC ->        CR      &=      ~(0xFFFF00FF);  //      Clear
  RCC ->        CR      |=      (0x83);         //      Reset value
  
  RCC ->        CR      |=      (1 << 16);      //      HSEON
  while(!(RCC -> CR & (1 << 17)));   // waiting for HSE ready
  
  RCC ->        CR      |=      (1 << 24);      //      PLLON
  while(!(RCC -> CR & (1 << 25)));  // waiting for PLL ready
  
  RCC ->        CFGR    |=      (2 << 0);       //      SW
  while(((RCC -> CFGR >> 2) & 0x03) != (2 << 0));
}

