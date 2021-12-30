#include "gpio.h"

volatile struct _GPIO *GPIOA = (struct _GPIO*) 0x40010800;
volatile struct _GPIO *GPIOB = (struct _GPIO*) 0x40010C00;
volatile struct _GPIO *GPIOC = (struct _GPIO*) 0x40011000;
volatile struct _GPIO *GPIOD = (struct _GPIO*) 0x40011400;
volatile struct _GPIO *GPIOE = (struct _GPIO*) 0x40011800;
volatile struct _GPIO *GPIOF = (struct _GPIO*) 0x40011C00;
volatile struct _GPIO *GPIOG = (struct _GPIO*) 0x40012000;

