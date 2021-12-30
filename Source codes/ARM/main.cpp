/*
 * ¹Ú±¤·Ä
 * pkr7098@gmail.com
 * 2021-12-28
 * main.cpp


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
#include "uid.h"
#include "device_type.h"

void RCC_INIT(void);
void SystemInit(void);

uint8_t uid;                                                                    //      System Unique Indentifier

int main(void) {
  SystemInit();
  putclear();
  putclear();
  putclear();
  printf("Density      \t: %c\n", DEVICE_TYPE_GET_TYPE());
  printf("Flash size   \t: %dK\n", DEVICE_TYPE_GET_FLASH_SIZE());
  printf("Serial number\t: %x-%x-%x\n", UID_GET_WORD(2), UID_GET_WORD(1), UID_GET_WORD(0));
  printf("=====================================\n");
  
  uid = UID_GET_BYTE(0);
  
  struct IR_FRAME send_frame;
  struct IR_FRAME *recv_frame;
  strcpy((char *) send_frame.p_datagram, "Hello_World0");
  send_frame.size_datagram = 13;

  
  for (int i = 0; i < 40; i++) {
    send_frame.p_datagram[11] = 'a' + i;
    IR_TRANSMIT_SEND_FRAME(&send_frame);
  }
  
  for (int i = 0; i < 8; i++) {
    recv_frame = DEQUEUE_IR_FRAME();
    printf("Data size: %3d, msg: %s\n", recv_frame -> size_datagram, recv_frame -> p_datagram);
  }
  
  return 0;
}






void SystemInit(void) {
  RCC_INIT();
  USART2_INIT();
  DELAY_INIT();
  IR_TRANSMIT_INIT();
  IR_RECEIVE_INIT();
}






void RCC_INIT(void) {                                                           //      Initialize RCC settings
  /*
    Initalize RCC
    SYSCLK      :       72 MHz
    APB1        :       36 MHz
    APB2        :       72 MHz
    ADC         :       12 MHz
  */ 
  
  (*(unsigned long *) 0x40022000)     &=      ~(0x07);                          //      Clear the register
  (*(unsigned long *) 0x40022000)     |=      (0x02);                           //      Set the flash latency to mode two -> without changing it, the mcu cannot run at 72MHz clock.
  
  RCC ->        CFGR    =       0;                                              //      Reset value
  RCC ->        CFGR    &=      ~(1 << 17);                                     //      PLLXTPRE
  RCC ->        CFGR    |=      (1 << 16);                                      //      PLLSRC
  RCC ->        CFGR    |=      (7 << 18);                                      //      PLLMUL
  
  RCC ->        CFGR    |=      (4 << 8);                                       //      PPRE1 (APB1)
  RCC ->        CFGR    |=      (2 << 14);                                      //      ADCPRE
  
  RCC ->        CR      &=      ~(0xFFFF00FF);                                  //      Clear
  RCC ->        CR      |=      (0x83);                                         //      Reset value
  
  RCC ->        CR      |=      (1 << 16);                                      //      HSEON
//  while(!(RCC -> CR & (1 << 17)));                                              //      Waiting for HSE ready
  
  RCC ->        CR      |=      (1 << 24);                                      //      PLLON
//  while(!(RCC -> CR & (1 << 25)));                                              //      Waiting for PLL ready
  
  RCC ->        CFGR    |=      (2 << 0);                                       //      SW
//  while(((RCC -> CFGR >> 2) & 0x03) != (2 << 0));                               //      waiting for SW ready
}

