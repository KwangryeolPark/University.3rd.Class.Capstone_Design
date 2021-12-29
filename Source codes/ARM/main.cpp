/*
  SYSCLK        :       72 MHz
  APB1          :       36 MHz
  APB2          :       72 MHz
  ADC           :       12 MHz

  TIM2          :       ~74 KHz  (=72 MHz / 972 = 74,074.074 = 13.5 us) 
TIM2 is for IR transmitter.
The IR transmitter works at 37KHz for modulation

  TIM7          :       100 KHZ
TIM7 is for delay_ms.

*/

#include "rcc.h"
#include "delay.h"
#include "ir_transmit.h"
#include "printf.h"


void initRCC(void);














int main(void) {
  
  initRCC();
  initIRTransmitter();
//  initDelay();
//  initUART2();
  
  return 0;
}













void initRCC(void) {
  /*
    Initalize RCC
    SYSCLK      :       72 MHz
    APB1        :       36 MHz
    APB2        :       72 MHz
    ADC         :       12 MHz
  */ 
  (*(unsigned long *) 0x40022000)     &=      ~(0x07);        //      Clear the register
  (*(unsigned long *) 0x40022000)     |=      (0x02); //      Set the flash latency to mode two -> without changing it, the mcu cannot run at 72MHz clock.

  RCC ->        CFGR    =       0;              //      Reset value
  RCC ->        CFGR    |=      (1 << 17);      //      PLLXTPRE
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

