#ifndef _GPIO_H
#define _GPIO_H

#include "typedef.h"

struct _GPIO {
  uint32_t        CRL;
  uint32_t        CRH;
  uint32_t        IDR;
  uint32_t        ODR;
  uint32_t        BSRR;
  uint32_t        BRR;
  uint32_t        LCKR;
};

volatile struct _GPIO *GPIOA = (struct _GPIO*) 0x40010800;
volatile struct _GPIO *GPIOB = (struct _GPIO*) 0x40010C00;
volatile struct _GPIO *GPIOC = (struct _GPIO*) 0x40011000;
volatile struct _GPIO *GPIOD = (struct _GPIO*) 0x40011400;
volatile struct _GPIO *GPIOE = (struct _GPIO*) 0x40011800;
volatile struct _GPIO *GPIOF = (struct _GPIO*) 0x40011C00;
volatile struct _GPIO *GPIOG = (struct _GPIO*) 0x40012000;

////////////////////////////////////////////////////////////////////////////////////////

#define CNF15   30
#define CNF14   26
#define CNF13   22
#define CNF12   18
#define CNF11   14
#define CNF10   10
#define CNF9    6
#define CNF8    2
#define CNF7    30
#define CNF6    26
#define CNF5    22
#define CNF4    18
#define CNF3    14
#define CNF2    10
#define CNF1    6
#define CNF0    2

#define MODE15   28   
#define MODE14   24
#define MODE13   20
#define MODE12   16
#define MODE11   12
#define MODE10   8
#define MODE9    4
#define MODE8    0
#define MODE7    28   
#define MODE6    24
#define MODE5    20
#define MODE4    16
#define MODE3    12
#define MODE2    8
#define MODE1    4
#define MODE0    0


#endif