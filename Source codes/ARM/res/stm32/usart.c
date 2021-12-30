#include "usart.h"

volatile struct _USART *USART1 = (struct _USART*) 0x40013800;
volatile struct _USART *USART2 = (struct _USART*) 0x40004400;
volatile struct _USART *USART3 = (struct _USART*) 0x40004800;
volatile struct _USART *UART4 = (struct _USART*) 0x40004C00;
volatile struct _USART *UART5 = (struct _USART*) 0x40005000;
