#ifndef _PRINTF_H
#define _PRINTF_H

#include "usart.h"
#include "gpio.h"
#include "afio.h"
#include "rcc.h"


// =============================================================================

#define PAD_RIGHT	1
#define PAD_ZERO	2
#define PRINT_BUF_LEN	12
#define MAX_UART_LINE	256

// =============================================================================

#define DEFAULT_USART   USART2

// =============================================================================

#define	ANSI_COLOR_BLACK	30
#define	ANSI_COLOR_RED		31
#define	ANSI_COLOR_GREEN	32
#define	ANSI_COLOR_YELLOW	33
#define	ANSI_COLOR_BLUE		34
#define	ANSI_COLOR_MAGENTA	35
#define	ANSI_COLOR_CYAN		36
#define	ANSI_COLOR_WHITE	37

// =============================================================================

void USART2_INIT(void);
int putc(struct _USART volatile *UART, int c);
int puts(struct _USART volatile *UART, const char *s);
void putclear(void);
void printchar(struct _USART volatile *UART, char **str, int c);
int prints(struct _USART volatile *UART, char **out, const char *string, int width, int pad);
int printi(struct _USART volatile *UART, char **out, int i, int b, int sg, int width, int pad, int letbase);
int print(struct _USART volatile *UART, char **out, int *varg);
int printf(struct _USART volatile *UART, const char *format, ...);
int printf(const char *format, ...);

// ======================================================================

#endif