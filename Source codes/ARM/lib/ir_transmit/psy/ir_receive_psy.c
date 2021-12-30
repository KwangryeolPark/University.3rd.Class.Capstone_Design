#include "ir_receive_psy.h"

// =============================================================================

// PB10
#define IR_RECEIVE_RCC_ENABLE   RCC -> APB2ENR  |=      (1 << 3)
#define IR_RECEIVE_CTRL_CLEAR   GPIOB -> CRH    &=      ~(0x000F << 8)
#define IR_RECEIVE_CTRL_SET     GPIOB -> CRH    |=      (4 << 8)
#define IR_RECEIVE_READ         (GPIOB -> IDR & (1 << 10))


// =============================================================================

volatile unsigned int IR_RECEIVE_COUNTER = 0;
volatile unsigned int IR_RECEIVE_READ_STEP = 0;
volatile unsigned char IR_RECEIVE_TEMP_DATA_SIZE = 0;
volatile unsigned char IR_RECEIVE_TEMP_DATA_BUFFER = 0;
volatile unsigned int IR_RECEIVE_BIT_INDEX = 0;
volatile unsigned int IR_RECEIVE_DATA_INDEX = 0;
volatile struct IR_FRAME IR_RECEIVE_TEMP_FRAME;

#define IR_RECEIVE_ISIDLE       (IR_RECEIVE_COUNTER > IR_RECEIVE_THRESHOLD_IDLE)
#define IR_RECEIVE_ISONE        (IR_RECEIVE_COUNTER < IR_RECEIVE_THRESHOLD_ONE)
#define IR_RECEIVE_ISZERO       (IR_RECEIVE_COUNTER > IR_RECEIVE_THRESHOLD_ZERO)

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


    msgs[index++] = IR_RECEIVE_READ_STEP;

    
    switch (IR_RECEIVE_READ_STEP) {
    case IR_RECEIVE_STEP_IDLE:
      if(IR_RECEIVE_ISIDLE) {
        IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_START;
      }
      break;
      
    case IR_RECEIVE_STEP_START:
      if(IR_RECEIVE_ISIDLE) {
        IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_START;
      } else if(IR_RECEIVE_ISONE) {
        IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_GET_SIZE;
        IR_RECEIVE_TEMP_DATA_SIZE = 0;
        IR_RECEIVE_BIT_INDEX = 0;
      } else {
        IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_IDLE;
      }
      break;
      
    case IR_RECEIVE_STEP_GET_SIZE:
      if(IR_RECEIVE_ISIDLE) {
        IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_START;
      }
      IR_RECEIVE_TEMP_DATA_SIZE <<= 1;
      if(IR_RECEIVE_ISONE) {
        IR_RECEIVE_TEMP_DATA_SIZE += 1;
      }
      IR_RECEIVE_BIT_INDEX++;
      
      if(IR_RECEIVE_BIT_INDEX == 8) {
        IR_RECEIVE_BIT_INDEX = 0;
        IR_RECEIVE_DATA_INDEX = 0;
        IR_RECEIVE_TEMP_DATA_BUFFER = 0;
        IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_GET_DATA;
      }
      break;
      
    case IR_RECEIVE_STEP_GET_DATA:
      if(IR_RECEIVE_ISIDLE) {
        IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_START;
      }
        
      IR_RECEIVE_TEMP_DATA_BUFFER <<= 1;
      if(IR_RECEIVE_ISONE) {
        IR_RECEIVE_TEMP_DATA_BUFFER += 1;
      }
      IR_RECEIVE_BIT_INDEX++;
      
      if (IR_RECEIVE_BIT_INDEX == 8) {
        IR_RECEIVE_BIT_INDEX = 0;
        IR_RECEIVE_TEMP_FRAME.p_datagram[IR_RECEIVE_DATA_INDEX++] = IR_RECEIVE_TEMP_DATA_BUFFER;
        
        if(IR_RECEIVE_DATA_INDEX == IR_RECEIVE_TEMP_DATA_SIZE) {
          //
          // DATA 넣는 코드
          IR_RECEIVE_TEMP_FRAME.size_datagram = IR_RECEIVE_TEMP_DATA_SIZE;
          ENQUEUE_IR_FRAME(IR_RECEIVE_TEMP_FRAME);
          // DATA 넣는 코드
          //
          
          IR_RECEIVE_READ_STEP = IR_RECEIVE_STEP_IDLE;
        }
      }
      break;
      
      
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
  TIM3 ->       ARR     =       (25 - 1);       //      1 MHz / (25 - 1 + 1) = 40 KHz = 25 us
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
  INIT_IR_FRAME();
  IR_RECEIVE_TEMP_FRAME.size_datagram = 0;
}

uint8_t IR_RECEIVE_DECODER(uint8_t *buf) {
  uint8_t data;
  data = buf[0] << 7;
  data |= buf[1] << 6;
  data |= buf[2] << 5;
  data |= buf[3] << 4;
  data |= buf[4] << 3;
  data |= buf[5] << 2;
  data |= buf[6] << 1;
  data |= buf[7];
  
  return data;
}

// =============================================================================
