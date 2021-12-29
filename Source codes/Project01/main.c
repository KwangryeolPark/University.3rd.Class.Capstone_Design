#include "rcc.h"

void initRCC(void);

int main(void) {
  
  initRCC();
  return 0;
}

void initRCC(void) {
  /*
    RCC 초기화입니다.
    SYSCLK      :       72MHz
    APB1        :       36MHz
    APB2        :       72MHz
    ADC         :       12MHz
  */ 
    (*(unsigned long *) 0x40022000)     &=      ~(0x07);        //      Clear the register
    (*(unsigned long *) 0x40022000)     |=      (0x02); //      Set the flash latency to mode two -> without changing it, the mcu cannot run at 72MHz clock.
    
    RCC ->      CFGR    =       0;              //      Reset value
    RCC ->      CFGR    |=      (1 << 17);      //      PLLXTPRE
    RCC ->      CFGR    |=      (1 << 16);      //      PLLSRC
    RCC ->      CFGR    |=      (7 << 18);      //      PLLMUL
    
    RCC ->      CFGR    |=      (4 << 8);       //      PPRE1 (APB1)
    RCC ->      CFGR    |=      (2 << 14);      //      ADCPRE
      
    RCC ->      CFGR    |=      (2 << 0);       //      SW
    
    RCC ->      CR      &=      ~(0xFFFF00FF);  //      Clear
    RCC ->      CR      |=      (0x83);         //      Reset value
    RCC ->      CR      |=      (1 << 16);      //      HSEON
    RCC ->      CR      |=      (1 << 24);      //      PLLON
}
