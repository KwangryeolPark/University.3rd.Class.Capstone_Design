/*
 * 박광렬
 * pkr7098@gmail.com
 * 2021-12-31
 * ir_trs.c
 * IR의 데이터링크 계 층 

ADC           :       12 MHz
12bits
PA0 -> ADC_IN0
*/

#include "ir_trs.h"

// =============================================================================

// =============================================================================

#define IR_LEVEL_THRESHOLD      100
#define IR_LEVEL_HIGH                    true                   //      IR 값이 인식 되었을 때, 기준 값보다 높다는 것을 의미합니다. -> true

volatile struct IR_FRAME IR_RECEIVE_TEMP_DATAGRAM;
extern uint8_t uid8;

// =============================================================================

void IR_ANALOG_INIT(void) {

  //  GPIO-A clock enable and set PA0 to analog input mode
  RCC -> APB2ENR        |=      (1 << IOPAEN);  //      GPIO-A clock enable
  GPIOA -> CRL                  &=      ~(0x0F << 0);   //      Clear the PA0 section for safe mode setting
  GPIOA -> CRL                  &=      ~(0x0F << 0);   //      Set the PA0 mode to Analog input mode

  //  Initialize ADC1
  RCC -> APB2ENR      |=      (1 << ADC1EN);  //      Enable the ADC1 module
  //  xxxx, 16      MUALMOD to Independent mode.
  //  x, 5            EOCIE to disable the End of Conversion interrupt.
  // x, 8             SCAN to disable Scan mode.
  ADC1 -> CR1                 &=      ~((0x0F << 16) | (1 << 5) | (1 << 8));

  //  x, 1            CONT to Continuous conversion
  //  x, 20           EXTRRIG to convert ADC on external event (acutually SWSTART)
  // xxx. 17          EXTSEL for SWSTART
  ADC1 -> CR2                 |=      (1 << 1) | (1 << 20) | (0x07 << 17);

  //  Regular channel sequence length to 1 conversion
  ADC1 -> SQR1                &=      ~(0x0F << 20);
//    ADC1 -> SQR1                |=      0xFF0FFFFF;
  //    Make channel 0 sample time to 55.5 cycles
  ADC1 -> SMPR2                 |=      (5 << 0);
  //    Make channel 0 the first conversion in regular sequence.
  ADC1 -> SQR3                  &=         ~(0x0F << 0);
  ADC1 -> SQR3                  |=         (0 << 0);
  
  //    ADC on
  ADC1 -> CR2                   |=      (1 << 0);
  
  //    Calibrate ADC
  ADC1 -> CR2                   |=      (1 << 3);       //      Reset calibration
  while (ADC1 -> CR2 & (0x00000008));   //      Wait for reset
  ADC1 -> CR2                   |=      (1 << 2);       //      Commence A/D Calibration
  while (ADC1 -> CR2 & (0x00000004));   //      Wait for calibrating
  
  //    Embark on SoftwareStart
  ADC1 -> CR2                   |=      (1 << 22);
}

void IR_TRANSMIT_TRS_INIT(void) {
  IR_ANALOG_INIT();
  INIT_IR_DATAGRAM();
}

uint16_t IR_LEVEL_WAIT(void) {

  while (!(ADC1 -> SR & 0x02)); //      EOC = 1? Is the conversion finished?
  return ADC1 -> DR;
  
}

uint16_t IR_LEVEL(void) {
  return ADC1 -> DR;
}

uint16_t IR_LEVEL_AVG(void) {
  uint64_t avg;
  
  avg = IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  avg = IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  avg += IR_LEVEL_WAIT();
  
  avg /= 10;
  return (uint16_t) avg;
}
// =============================================================================

unsigned char GET_EVEN_PARITY(unsigned char C) {
  unsigned char i = 0;
  if (C & 0x01) i++;
  if (C & 0x02) i++;
  if (C & 0x04) i++;
  if (C & 0x08) i++;
  if (C & 0x10) i++;
  if (C & 0x20) i++;
  if (C & 0x40) i++;
  if (C & 0x80) i++;
  
  return i % 2;
}

unsigned char GET_ODD_PARITY(unsigned char c) {
  return !GET_EVEN_PARITY(c);
}

void IR_TRANSMIT_SEND_DATAGRAM(struct IR_DATAGRAM *datagram) {
#if IR_LEVEL_HIGH == true
  while(IR_LEVEL_AVG() > IR_LEVEL_THRESHOLD);  //      신호 준위가 내려갈 때까지 기다림
#else
  while(IR_LEVEL_AVG() < IR_LEVEL_THRESHOLD);  //      신호 준위가 내려갈 때까지 기다림
#endif
  
  struct IR_FRAME frame;
  const unsigned char *p_segment       =       datagram -> p_segment;            //      Datagram
  unsigned char parity     =       0;         //      The size of datagram
  const unsigned char size_segment     =       datagram -> size_segment;         //      The size of datagram

  for (register int i = 0; i < size_segment; i++) {
    parity += GET_EVEN_PARITY(p_segment[i]);
    frame.p_datagram[i] = p_segment[i];
  }
  
  frame.p_datagram[size_segment] = uid8;
  frame.p_datagram[size_segment + 1] = parity % 2;
  frame.p_datagram[size_segment + 2] = size_segment;
  
  IR_TRANSMIT_SEND_FRAME(&frame);
}

void IR_TRANSMIT_RECEIVE_DARAGRAM(void) {
  struct IR_DATAGRAM IR_RECEIVE_TEMP_DATAGRAM;
  struct IR_FRAME* frame = DEQUEUE_IR_FRAME();
  IR_RECEIVE_TEMP_DATAGRAM.mac= frame -> p_datagram[frame -> size_datagram];
  IR_RECEIVE_TEMP_DATAGRAM.size_segment = frame -> p_datagram[frame -> size_datagram + 2];
  IR_RECEIVE_TEMP_DATAGRAM.parity = frame -> p_datagram[frame -> size_datagram + 1];

  for (register int i = 0; i < IR_RECEIVE_TEMP_DATAGRAM.size_segment; i++) {
    IR_RECEIVE_TEMP_DATAGRAM.p_segment[i] = frame -> p_datagram[i];
  }
  
  ENQUEUE_SUITABLE_IR_DATAGRAM(&IR_RECEIVE_TEMP_DATAGRAM);
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    

