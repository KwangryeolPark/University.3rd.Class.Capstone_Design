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

// =============================================================================

void IR_ANALOG_INIT(void) {

  //  GPIO-A clock enable and set PA0 to analog input mode
  RCC -> APB2ENR        |=      (1 << IOPAEN);  //      GPIO-A clock enable
  RCC -> CRL                    &=      ~(0x0F << 0);   //      Clear the PA0 section for safe mode setting
  RCC -> CRL                    &=      ~(0x0F << 0);   //      Set the PA0 mode to Analog input mode

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

uint16_t IR_LEVEL_WAIT(void) {

  while (!(ADC1 -> SR & 0x02)); //      EOC = 1? Is the conversion finished?
  return ADC1 -> DR;
  
}

uint16_t IR_LEVEL(void) {
  return ADC1 -> DR;
}

// =============================================================================





  
