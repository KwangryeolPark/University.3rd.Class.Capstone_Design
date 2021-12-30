#include "ir_transmit_psy.h"

// =============================================================================

#define IR_TRANSMIT_RCC_ENABLE          RCC -> APB2ENR  |=      (1 << 3)
#define IR_TRANSMIT_CTRL_CLEAR          GPIOB -> CRH    &=      ~(0x000F << 12)
#define IR_TRANSMIT_CTRL_SET            GPIOB -> CRH    |=      (2 << 12)
#define IR_TRANSMIT_CLEAR               GPIOB -> ODR &= ~(1 << 11)
#define IR_TRANSMIT_SET                 GPIOB -> ODR |= (1 << 11)
#define IR_TRANSMIT_TOGGLE              GPIOB -> ODR ^= (1 << 11)

#define IR_TRANSMIT_CLEAR_FLAG          IR_TRANSMIT_TRANSMITTER_FLAG     =       0
#define IR_TRANSMIT_SET_FLAG            IR_TRANSMIT_TRANSMITTER_FLAG     =       1
#define IR_TRANSMIT_CLEAR_COUNTER       IR_TRANSMIT_TRANSMITTER_COUNTER  =       0
#define IR_TRANSMIT_SET_IDLE            IR_TRANSMIT_CLEAR
#define IR_TRANSMIT_TOGGLE_UNTIL_FLAG_SET        while (!IR_TRANSMIT_TRANSMITTER_FLAG) {        \
                                          if (IR_TRANSMIT_TRANSMITTER_COUNTER % 2 == 0) {       \
                                            IR_TRANSMIT_SET;                                    \
                                          } else {                                              \
                                            IR_TRANSMIT_CLEAR;                                  \
                                          }                                                     \
                                        }
#define IR_TRANSMIT_WAIT_UNTIL_FLAG_SET     while (!IR_TRANSMIT_TRANSMITTER_FLAG)

// =============================================================================

volatile unsigned int IR_TRANSMIT_TRANSMITTER_COUNTER    =       0;
volatile unsigned char IR_TRANSMIT_TRANSMITTER_FLAG      =       0;

// =============================================================================

extern "C" {    //      Notify that the below functions are unique in C++
  void TIM2_IRQHandler(void);
};

void TIM2_IRQHandler(void) {            //      A hanlder for TIM2
  TIM2 -> SR    =       0;              //      You need to reclear it manually and it should not be deleted. (important)

  IR_TRANSMIT_TRANSMITTER_COUNTER++;

  if (IR_TRANSMIT_TRANSMITTER_COUNTER == TIM2_500_US_COUNT) {
    IR_TRANSMIT_SET_FLAG;
  }
}

// =============================================================================

void IR_TRANSMIT_MODULATION_TIMER_INIT(void) {
  /*
    Intialize TIM2 and set its clock to 80 KHz
  */

  RCC ->        APB1ENR |=      (1 << 0);       //      Enable TIM2  

  TIM2 ->       PSC     =       (9 - 1);        //      72,000,000 / (18 - 1 + 1) ~= 4 MHz
  TIM2 ->       ARR     =       (100 - 1);      //      4 MHz / (100 - 1 + 1) = 80 KHz = 2 * 40 KHz
  TIM2 ->       CNT     =       0;              //      Initialize the TIM2 begin value
  TIM2 ->       SR      =       0;              //      Clear all status about TIM2  
}

void IR_TRANSMIT_MODULATION_TIMER_ENABLE(void) {
  /*
    Enable TIM2
  */
  
  NVIC_ISER0            |=      (1 << 28);      //      Connect TIM2 to NVIC
  
  TIM2 ->       DIER    =       (1 << 0);       //      Activate TIM2 interrupt
  TIM2 ->       EGR     =       (1 << 0);       //      Notify the the registers are updated
  TIM2 ->       CR1     =       (1 << 0);       //      Begin TIM2
}

void IR_TRANSMIT_PORT_INIT(void) {
  /*
    Enable PB11
    Push-pull general output, 2 MHz mode
  */
  
  IR_TRANSMIT_RCC_ENABLE;       //      Enable GPIOB
  IR_TRANSMIT_CTRL_CLEAR;       //      Clear 11 settings
  IR_TRANSMIT_CTRL_SET;         //      General ourput push-pull, 2 MHz
  IR_TRANSMIT_CLEAR;            //      Clear port
}

void IR_TRANSMIT_INIT(void) {
  IR_TRANSMIT_MODULATION_TIMER_INIT();   //      Initialize TIM2
  IR_TRANSMIT_PORT_INIT();               //      Set IR port
  IR_TRANSMIT_MODULATION_TIMER_ENABLE(); //      Enable TIM2
}

void IR_TRANSMIT_SIGNAL_ONE(void) {
  /*
    Generate a 1 signal modulated to 38 KHz

    IDLE status     :       LOW

    1:
                500 us   500 us
      HIGH     ________
              |  |  |  |
              |  |  |  |       
      LOW     |  |  |  |_______
  */

  IR_TRANSMIT_CLEAR_FLAG;
  IR_TRANSMIT_CLEAR_COUNTER;
  IR_TRANSMIT_TOGGLE_UNTIL_FLAG_SET
  
  IR_TRANSMIT_CLEAR;     //      Off the IR port
  
  IR_TRANSMIT_CLEAR_FLAG;
  IR_TRANSMIT_CLEAR_COUNTER;
  IR_TRANSMIT_WAIT_UNTIL_FLAG_SET;       //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.
}

void IR_TRANSMIT_SIGNAL_ZERO(void) {
  /*
    Generate a 0 signal modulated to 38 KHz

    IDLE status     :       LOW

    0:
                500 us      1000 us
      HIGH     ________
              |  |  |  |
              |  |  |  |       
      LOW     |  |  |  |______________
  */

  IR_TRANSMIT_CLEAR_FLAG;
  IR_TRANSMIT_CLEAR_COUNTER;
  IR_TRANSMIT_TOGGLE_UNTIL_FLAG_SET
  
  IR_TRANSMIT_CLEAR_FLAG;
  IR_TRANSMIT_CLEAR_COUNTER;
  IR_TRANSMIT_WAIT_UNTIL_FLAG_SET;       //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.

  IR_TRANSMIT_CLEAR;     //      Off the IR port
  
  IR_TRANSMIT_CLEAR_FLAG;
  IR_TRANSMIT_CLEAR_COUNTER;
  IR_TRANSMIT_WAIT_UNTIL_FLAG_SET;       //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.
}

// =============================================================================

void IR_TRANSMIT_SEND_BYTE(uint8_t byte) {
  uint8_t bit;
  
  for (int i = 0; i < 8; i++) { //    Send MSB first
    bit = ((byte << i) & 0x80);
    
    if (bit) {
      IR_TRANSMIT_SIGNAL_ONE();
    } else {
      IR_TRANSMIT_SIGNAL_ZERO();
    }
  }
}

void IR_TRANSMIT_SEND_FRAME(struct IR_FRAME *frame) {
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
  
  const unsigned char *p_datagram       =       (unsigned char *)       frame -> p_datagram;
  const unsigned char size_datagram     =       frame -> size_datagram;
  unsigned char msg;
    
  delay_ms(10);                  //      Distinguish the new frame
  
  IR_TRANSMIT_SIGNAL_ONE();       //      Start bit

  IR_TRANSMIT_SEND_BYTE(size_datagram);  //      Send size data
  
  for (int i = 0; i < size_datagram; i++) {     //      Send datagram
    msg   =       *(p_datagram + i);
    IR_TRANSMIT_SEND_BYTE(msg);
  }

  IR_TRANSMIT_SIGNAL_ONE();       //      End bit  
}