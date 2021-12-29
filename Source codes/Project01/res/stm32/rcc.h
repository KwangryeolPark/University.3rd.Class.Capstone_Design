#ifndef _RCC_H
#define _RCC_H

#include "typedef.h"

struct _RCC {
  uint32_t        CR;
  uint32_t        CFGR;
  uint32_t        CIR;
  uint32_t        APB2RSTR;
  uint32_t        APB1RSTR;
  uint32_t        AHBENR;
  uint32_t        APB2ENR;
  uint32_t        APB1ENR;
  uint32_t        BDCR;
  uint32_t        CSR;
  uint32_t        AHBSTR;
  uint32_t        CFGR2;
};

volatile struct _RCC *RCC = (struct _RCC*) 0x40021000;

////////////////////////////////////////////////////////////////////////////////////////

#define TIM11EN 21
#define TIM10EN 20
#define TIM9EN  19
#define ADC3EN  15
#define USART1EN        14
#define TIM8EN  13
#define SPI1EN  12
#define TIM1EN  11
#define ADC2EN  10
#define ADC1EN  9
#define IOPGEN  8
#define IOPFEN  7
#define IOPEEN  6
#define IOPDEN  5
#define IOPCEN  4
#define IOPBEN  3
#define IOPAEN  2
#define AFIOEN  0

#define MCO     24
#define USBPRE  22
#define PLLMUL  18
#define PLLXTPRE        17
#define PLLSRC  16
#define ADCPRE  14
#define PPRE2   11
#define PPRE1   8
#define HPRE    4
#define SWS     2
#define SW      0

#define PLLRDY  25
#define PLLON   24
#define CSSON   19
#define HSEBYP  18
#define HSERDY  17
#define HSEON   16
#define HSICAL  8
#define HSITRIM 3
#define HSIRDY  1
#define HSION   0

#define DACEN   29
#define PWREN   28
#define BKPEN   27
#define CANEN   25
#define USBEN   23
#define I2C2EN  22
#define I2C1EN  21
#define UART5EN 20
#define UART4EN 19
#define USART3EN        18
#define USART2EN        17
#define SPI3EN  15
#define SPI2EN  14
#define WWDGEN  11
#define TIM14EN 8
#define TIM13EN 7
#define TIM12EN 6
#define TIM7EN 5
#define TIM6EN 4
#define TIM5EN 3
#define TIM4EN 2
#define TIM3EN 1
#define TIM2EN 0
  
#define I2S3SRC 18
#define I2S2SRC 17
#define PREDIV1SRC      16
#define PLL3MUL 12
#define PLL2MUL 8
#define PREDIV2 4
#define PREDIV1 0


#endif