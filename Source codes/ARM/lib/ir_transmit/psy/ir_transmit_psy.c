/*
 * 박광렬
 * pkr7098@gmail.com
 * 2021-12-29
 * ir_transmit_psy.c
 * IR 송신기의 물리 계층



IR 송신기는 GPIOB 11번을 사용하며, 40 KHz로 신호가 변조됩니다.
40 KHz 변조를 위해 80 KHz로 동작하는 TIM2를 사용합니다.

FLAG를 0하고, 1이 될 때까지 while문으로 기다리면 500 us 동안 기다린 것과 동일한 효과를 얻습니다.

*/

#include "ir_transmit_psy.h"

// =============================================================================

#define IR_TRANSMIT_RCC_ENABLE          RCC -> APB2ENR  |=      (1 << 3)                                //      IR 송신기에 클럭을 인가합니다.
#define IR_TRANSMIT_CTRL_CLEAR          GPIOB -> CRH    &=      ~(0x000F << 12)                         //      IR 송신기의 IO 방향 설정을 초기화합니다.
#define IR_TRANSMIT_CTRL_SET            GPIOB -> CRH    |=      (2 << 12)                               //      IR 송신기의 IO 방향을 Output, Push-pull 2 MHz로 설정합니다.
#define IR_TRANSMIT_CLEAR               GPIOB -> ODR &= ~(1 << 11)                                      //      IR 송신기를 off합니다.
#define IR_TRANSMIT_SET                 GPIOB -> ODR |= (1 << 11)                                       //      IR 송신기를 on합니다.
#define IR_TRANSMIT_TOGGLE              GPIOB -> ODR ^= (1 << 11)                                       //      IR 송신시를 toggle합니다.

#define IR_TRANSMIT_CLEAR_FLAG          IR_TRANSMIT_TRANSMITTER_FLAG     =       0                      //      FLAG를 0으로 설정합니다.
#define IR_TRANSMIT_SET_FLAG            IR_TRANSMIT_TRANSMITTER_FLAG     =       1                      //      FLAG를 1로 설정합니다.
#define IR_TRANSMIT_CLEAR_COUNTER       IR_TRANSMIT_TRANSMITTER_COUNTER  =       0                      //      COUNTER를 0으로 설정합니다.
#define IR_TRANSMIT_SET_IDLE            IR_TRANSMIT_CLEAR                                               //      IDLE 상태를 위한 설정으로 IR_TRANSMIT_CLEAR 또는 IR_TRANSMIT_SET 둘 중 하나가 될 수 있습니다.
#define IR_TRANSMIT_TOGGLE_UNTIL_FLAG_SET        while (!IR_TRANSMIT_TRANSMITTER_FLAG) {        \
                                          if (IR_TRANSMIT_TRANSMITTER_COUNTER % 2 == 0) {       \
                                            IR_TRANSMIT_SET;                                    \
                                          } else {                                              \
                                            IR_TRANSMIT_CLEAR;                                  \
                                          }                                                     \
                                        }                                                               //      500 us를 기다리기 위해 FLAG가 1이 될 때까지 IR을 toggle합니다.
#define IR_TRANSMIT_WAIT_UNTIL_FLAG_SET     while (!IR_TRANSMIT_TRANSMITTER_FLAG)                       //      500 us를 기다리기 위해 FLAG가 1이 될 때까지 기다립니다. 

// =============================================================================

volatile unsigned int IR_TRANSMIT_TRANSMITTER_COUNTER    =       0;             //      TIM2가 실행된 횟수를 기록하며, 임의로 0으로 초기화할 수 있습니다.
volatile unsigned char IR_TRANSMIT_TRANSMITTER_FLAG      =       0;             //      500 us를 측정하기 위해 사용되며, FLAG를 0으로 초기화한 후, while문으로 1이 될 때까지 기다립니다.

// =============================================================================

extern "C" {                                                                    //      Notify that the below functions are unique in C++
  void TIM2_IRQHandler(void);                                                   //      TIM2_IRQHandler가 유일하다는 것을 알려줍니다.
};

void TIM2_IRQHandler(void) {                                                    //      A hanlder for TIM2
  /*
    Handle the TIM2 interrupt
  */
  TIM2 -> SR    =       0;                                                      //      You need to reclear it manually and it should not be deleted. (important)

  IR_TRANSMIT_TRANSMITTER_COUNTER++;                                            //      It is the count that the TIM2 interrupt is executed.

  if (IR_TRANSMIT_TRANSMITTER_COUNTER == TIM2_500_US_COUNT) {
    //  Check that the counter reaches to TIM2_500_US_COUNT
    //  It is used for watiting 500 us
    IR_TRANSMIT_SET_FLAG;                                                       //      Notify that 500 us has passed.
  }
}

// =============================================================================

void IR_TRANSMIT_MODULATION_TIMER_INIT(void) {                                  //      Initialize the TIM2 settings
  /*
    Intialize TIM2 and set its clock to 80 KHz
  */

  RCC ->        APB1ENR |=      (1 << 0);                                       //      Enable TIM2  

  TIM2 ->       PSC     =       (9 - 1);
  //    Make the prescaler to 9 to generate 80 KHz ultimately
  //    72,000,000 / (9 - 1 + 1) ~= 8 MHz
  TIM2 ->       ARR     =       (100 - 1);
  //    When the counter(CNT) reaches ARR, it would be back to 0 count.
  //    4 MHz / (100 - 1 + 1) = 80 KHz = 2 * 40 KHz
  TIM2 ->       CNT     =       0;                                              //      Initialize the TIM2 begin value
  TIM2 ->       SR      =       0;                                              //      Clear all status about TIM2  
}

void IR_TRANSMIT_MODULATION_TIMER_ENABLE(void) {                                //      Enable TIM2
  /*
    Enable TIM2
  */
  
  NVIC_ISER0            |=      (1 << 28);
  //    Connect TIM2 to NVIC
  //    28 means the position of TIM2 in the interrupt vector table
  
  TIM2 ->       DIER    =       (1 << 0);                                       //      Activate TIM2 interrupt
  TIM2 ->       EGR     =       (1 << 0);
  //    Notify the the registers are updated
  //    After this setting, the TIM2 interrupt should occure, if TIM2 was correctly setted.
  //    If not happend, something was wrong and the interrupt will not be pended
  TIM2 ->       CR1     =       (1 << 0);                                       //      Begin TIM2
}

void IR_TRANSMIT_PORT_INIT(void) {                                              //      Initialize all about IR transmitter port
  /*
    Enable PB11
    Push-pull general output, 2 MHz mode
  */
  
  IR_TRANSMIT_RCC_ENABLE;                                                       //      Enable GPIOB
  IR_TRANSMIT_CTRL_CLEAR;
  //    Clear IO direction settings
  //    Without this code, the IR setting potentially occures some runtime error
  //    Maybe the IR action would be wrong.
  IR_TRANSMIT_CTRL_SET;                                                         //      General ourput push-pull, 2 MHz
  IR_TRANSMIT_CLEAR;                                                            //      Clear port
}

void IR_TRANSMIT_INIT(void) {                                                   //      Initialize all about IR transmitter
  /*
    Intiailize all IR transmitter settings, including TIM2 and initiate
  */
  IR_TRANSMIT_MODULATION_TIMER_INIT();                                          //      Initialize TIM2
  IR_TRANSMIT_PORT_INIT();                                                      //      Set IR port
  IR_TRANSMIT_CLEAR;                                                            //      Off the IR port for LOW state
  IR_TRANSMIT_MODULATION_TIMER_ENABLE();                                        //      Enable TIM2
}

// =============================================================================

void IR_TRANSMIT_SIGNAL_ONE(void) {                                             //      Generate a 1 signal modulated to 40 KHz
  /*
    Generate a 1 signal modulated to 40 KHz

    IDLE status     :       LOW

    1:
                500 us   500 us
      HIGH     ________
              |  |  |  |
              |  |  |  |       
      LOW     |  |  |  |_______
  */

  //    Stay TOGGLING state for 500 us
  IR_TRANSMIT_CLEAR_FLAG;                                                       //      Clear flag for waiting 500 us
  IR_TRANSMIT_CLEAR_COUNTER;                                                    //      Clear counter for correct action, waiting 500 us
  IR_TRANSMIT_TOGGLE_UNTIL_FLAG_SET                                             //      Wait 500 us
  
  //    Stay LOW state for 500 us
  IR_TRANSMIT_CLEAR;                                                            //      Off the IR port for LOW state
  IR_TRANSMIT_CLEAR_FLAG;                                                       //      Clear flag for waiting 500 us
  IR_TRANSMIT_CLEAR_COUNTER;                                                    //      Clear counter for correct action, waiting 500 us
  IR_TRANSMIT_WAIT_UNTIL_FLAG_SET;                                              //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.
}

void IR_TRANSMIT_SIGNAL_ZERO(void) {                                            //      Generate a 0 signal modulated to 40 KHz
  /*
    Generate a 0 signal modulated to 40 KHz

    IDLE status     :       LOW

    0:
                500 us      1000 us
      HIGH     ________
              |  |  |  |
              |  |  |  |       
      LOW     |  |  |  |______________
  */

  //    Stay TOGGLING state for 500 us
  IR_TRANSMIT_CLEAR_FLAG;                                                       //      Clear flag for waiting 500 us
  IR_TRANSMIT_CLEAR_COUNTER;                                                    //      Clear counter for correct action, waiting 500 us
  IR_TRANSMIT_TOGGLE_UNTIL_FLAG_SET;                                            //      Wait 500 us
  
  //    Stay LOW state for 1000 us
  IR_TRANSMIT_CLEAR;                                                            //      Off the IR port for LOW state
  IR_TRANSMIT_CLEAR_FLAG;                                                       //      Clear flag for waiting 500 us
  IR_TRANSMIT_CLEAR_COUNTER;                                                    //      Clear counter for correct action, waiting 500 us
  IR_TRANSMIT_WAIT_UNTIL_FLAG_SET;                                              //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.
  //    Repeat again
  IR_TRANSMIT_CLEAR_FLAG;                                                       //      Clear flag for waiting 500 us
  IR_TRANSMIT_CLEAR_COUNTER;                                                    //      Clear counter for correct action, waiting 500 us
  IR_TRANSMIT_WAIT_UNTIL_FLAG_SET;                                              //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.
}

void IR_TRANSMIT_SEND_BYTE(uint8_t byte) {                                      //      Send 1 byte data
  /*
    Send a byte orderd by MSB
  */
  uint8_t bit;                                                                  //      A bit extracted from the byte variable

  //    Send MSB to LSB data
  for (int i = 0; i < 8; i++) {                                                 //      Loop 8 times to send 8 bits (=byte)
    bit = ((byte << i) & 0x80);                                                 //      Get MSB first bit from the byte variable

    if (bit) {                                                                  //      If the bit is 1
      IR_TRANSMIT_SIGNAL_ONE();                                                 //      Send 1 data
    } else {                                                                    //      If the bit is 0
      IR_TRANSMIT_SIGNAL_ZERO();                                                //      Send 0 data
    }
  }
}

void IR_TRANSMIT_SEND_FRAME(struct IR_FRAME *frame) {                           //      Send IR FRAME data
  /*
    Send string IR_TRANSMIT_FRAME type data

    struct IR_TRANSMIT_FRAME {
      void *p_datagram;                 //      datagram
      unsigned char size_datagram;      //      datagram size
    };


    IDLE status     :       LOW
    start bit       :       1
    end bit         :       1

    Protocol
        <IDLE>  <start bit>     <size>  <datagram>      <end bit>       <IDLE>
    bits        1               8       size * 8        1
  */
  
  const unsigned char *p_datagram       =       frame -> p_datagram;            //      Datagram
  const unsigned char size_datagram     =       frame -> size_datagram;         //      The size of datagram
  unsigned char msg;                                                            //      Message value which is extraced from datagram
    
  delay_ms(5);                                                                 //      Distinguish the new frame
  
  //    Start transmitting
  IR_TRANSMIT_SIGNAL_ONE();                                                     //      Send start bit (1)

  IR_TRANSMIT_SEND_BYTE(size_datagram);                                         //      Send size data
  
  //    Send datagram
  for (int i = 0; i < size_datagram; i++) {                                     //      Send datagram
    msg   =       *(p_datagram + i);                                            //      Get the value of message (1 byte)
    IR_TRANSMIT_SEND_BYTE(msg);                                                 //      Send the message value
  }

  IR_TRANSMIT_SIGNAL_ONE();                                                     //      End bit  
}