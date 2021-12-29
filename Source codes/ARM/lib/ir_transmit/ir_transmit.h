#ifndef _IR_TRANSMIT_H
#define _IR_TRANSMIT_H

// All the settings are suit to 72 MHz

#include "rcc.h"
#include "tim.h"
#include "nvic.h"
#include "delay.h"

#define TIM2_500_us_count       37
#define SEND_BROADCAST          0
#define RECV_BROADCAST          0

volatile unsigned int IR_transmitter_counter;
volatile unsigned int IR_transmitter_flag;

struct IR_data_frame {
  unsigned char send_id;        //      The source node ID
  unsigned char recv_id;        //      The destination node ID
  unsigned char size;           //      The size should be less than or equal to 255
  char *p_msg;                  //      The pointer of string message
};


extern "C" {    //      Notify that the below functions are unique in C++
  void TIM2_IRQHandler(void);
}

void TIM2_IRQHandler(void) {    //      A hanlder for TIM2
  TIM2 ->        SR      =       0;      //      You need to reclear it manually and it should not be deleted. (important)

  IR_transmitter_counter++;
  
  if (IR_transmitter_counter == TIM2_500_us_count) {
    IR_transmitter_flag = 1;
  }
}

// ==================================================================================================================================

void initTIM2(void);
void enableTIM2(void);
void IR_transmit_signal(uint8_t _mode);
void IR_send_frame(struct IR_data_frame data);
void initIRTransmitter(void);

void initTIM2(void) {
  /*
    Intialize TIM2 and set its clock to 74 KHz
  */

  RCC ->        APB1ENR |=      (1 << 0);       //      Enable Timer2
  
  TIM2 ->       PSC     =       (973 - 1);      //      72,000,000 / (973 - 1) ~= 74kHz = 37 * 2 KHz
  TIM2 ->       ARR     =       1 - 1;          //      74 KHz / (1 - 1 + 1) = 74 KHz
  TIM2 ->       CNT     =       0;              //      Initialize the TIM2 begin value
  TIM2 ->       SR      =       0;              //      Clear all status about TIM2
}

void enableTIM2(void) {
  /*
    Enable TIM2
  */
  TIM2 ->       DIER    =       (1 << 0);       //      Activate TIM2 interrupt
  NVIC_ISER0            =       (1 << 28);      //      Connect TIM2 to NVIC
  
  TIM2 ->       EGR     =       (1 << 0);       //      Notify the the registers are updated
  TIM2 ->       CR1     =       (1 << 0);       //      Begin TIM2
}

void IR_transmit_signal(uint8_t _mode) {
  /*
    Make a 1 or 0 signal
    The signal 1 consists of 500 us on and off.
    The signal 0 consists of 500 us on and twice of it off.

IDLE status     :       LOW

1:
            500 us  500 us
  HIGH     _______
          |       |
          |       |       
  LOW     |       |_______

0:
            500 us     1000 us
  HIGH     _______
          |       |
          |       |       
  LOW     |       |______________

  */
  IR_transmitter_flag = 0;
  IR_transmitter_counter = 0;
  while (!IR_transmitter_flag) {
//#error  You have to indicate the IR transmit port
    // Toggling the IR port (or just on and off the port)
  }
  
//#error  You have to indicate the IR transmit port
  // off the IR port

  IR_transmitter_flag = 0;
  IR_transmitter_counter = 0;
  
  while (!IR_transmitter_flag) ; //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.
  
  if (_mode == 0) {
    IR_transmitter_flag = 0;
    IR_transmitter_counter = 0;
  
    while (!IR_transmitter_flag) ; //      Wait for 500 us because the 'one' signal on and off have to wait for 500 us.
  }    
}

void IR_send_frame(struct IR_data_frame data) {
  /*
    Send string IR_data_frame type data

    struct IR_data_frame {
      unsigned char send_id;        //      The source node ID
      unsigned char recv_id;        //      The destination node ID
      unsigned char size;           //      The size should be less than or equal to 255
      char *p_msg;                  //      The pointer of string message
    };

IDLE status     :       LOW
start bit       :       1
end bit         :       1

Protocol
    <IDLE>  <start bit>     <send_id>       <recv_id>       <size>      <msg>           <end bit>       <IDLE>
bits        1               8               8               8           size * 8        1
  */
  
  unsigned char i       =       0;
  unsigned char j       =       0;
  unsigned char send_id =       data.send_id;
  unsigned char recv_id =       data.recv_id;
  unsigned char size    =       data.size;
  char          *p_msg  =       data.p_msg;
  
  delay_ms(5);                 //      distinguish the new frame
  
  IR_transmit_signal(1);        //      start bit

  //    Send MSB first  
  for (; i < 8; i++) {
    IR_transmit_signal((size << i) & 0x80);     //      Send the length of data
  }
  
  for (i = 0; i < 8; i++) {
    IR_transmit_signal((send_id << i) & 0x80);  //      The source ID
  }
  
  for (i = 0; i < 8; i++) {
    IR_transmit_signal((recv_id << i) & 0x80);  //      The destination ID
  }
  
  for (; j < size; j++) {
    char msg    =       *(p_msg + j);           //      Extract the message
    for (i = 0; i < 8; i++) {
      IR_transmit_signal((msg << i) & 0x80);    //      Send the message
    }
  }
  
  IR_transmit_signal(1);        //      end bit
}

void initIRTransmitter(void) {
  initTIM2();
  enableTIM2();
}

#endif