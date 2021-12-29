#ifndef _USART_H
#define _USART_H

/*
  799 page
  Table 192. Error calculation for programmed baud rates

  Kbps          fPCLK = 36 MHz          fPCLK = 72 MHz
                BRR             ERROR   BRR             ERROR
  2400          938             0%      1875            0%
  9600          234.375         0%      468.75          0%
  19200         117.1875        0%      234.375         0%
  57600         39.0625         0%      78.125          0%
  115200        19.5            0.15%   39.0625         0%
  230400        9.75            0.16%   19.5            0.16%
  460800        4.875           0.16%   9.75            0.16%
  921600        2.5375          0.16%   4.875           0.16%
  2250000       1               0%      2               0%
  4500000       NA              NA      1               0%

*/

struct _USART {
  uint32_t SR;
  uint32_t DR;
  uint32_t BRR;
  uint32_t CR1;
  uint32_t CR2;
  uint32_t CR3;
  uint32_t GTPR;
};

volatile struct _USART *USART1 = (struct _USART*) 0x40013800;
volatile struct _USART *USART2 = (struct _USART*) 0x40004400;
volatile struct _USART *USART3 = (struct _USART*) 0x40004800;
volatile struct _USART *UART4 = (struct _USART*) 0x40004C00;
volatile struct _USART *UART5 = (struct _USART*) 0x40005000;

// SR   818 page
#define CTS     9
#define LBD     8
#define TXE     7
#define TC      6
#define RXEN    5
#define IDLE    4
#define ORE     3
#define NE      2
#define FE      1
#define PE      0

// DR   820 page

// BRR  820 page
#define DIV_Mantissa    4
#define DIV_Fraction    0

// CR1  821 page
#define UE      13
#define M       12
#define WAKE    11
#define PCE     10
#define PS      9
#define PEIE    8
#define TXEIE   7
#define TCIE    6
#define RXNEIE  5
#define IDLEIE  4
#define TE      3
#define RE      2
#define RWU     1
#define SBK     0

// CR2 823 page
#define LINEN   14
#define STOP    12
#define CLKEN   11
#define CPOL    10
#define CPHA    9
#define LBCL    8
#define LBDIE   6
#define LBDL    5
#define ADD     0

// CR3 824 page
#define CTSIE   10
#define CTSE    9
#define RTSE    8
#define DMAT    7
#define DMAR    6
#define SCEN    5
#define NACK    4
#define HDSEL   3
#define IRLP    2
#define IREN    1
#define EIE     0

// GTPR 823 page
#define GT      8
#define USART_PSC     0

#endif