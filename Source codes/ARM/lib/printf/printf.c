#include "printf.h"

// =============================================================================

void USART2_INIT(void) {
  RCC -> APB2ENR        |=      (1 << AFIOEN) | (1 << IOPAEN);
  GPIOA -> CRL          &=      ~((0xF << MODE2) | (0xF << MODE3));
  GPIOA -> CRL          |=      (11 << MODE2) | (4 << MODE3);
  RCC -> APB1ENR        |=      (1 << USART2EN);

  USART2 -> BRR = (19 << 4) | 8;
  USART2 -> CR1 = (1 << UE) | (1 << TE);    // USART enable, Transmit & Receive enable
}

int putc(struct _USART volatile *UART, int c) {
  unsigned char data = (unsigned char) c;
  
  if ((data == '\n') || (data == '\r')) {
    while (!((UART -> SR) >> TC & 0x01));
    UART -> DR  =       '\n';
    while (!((UART -> SR) >> TC & 0x01));
    UART -> DR  =       '\r';
  } else {
    while (!((UART -> SR) >> TC & 0x01));
    UART -> DR  =       data;    
  }
  
  return c;
}

int puts(struct _USART volatile *UART, const char *s) {
  unsigned int i = 0;
  
  while(1) {
    if ((char) *(s + i) == 0) {
      break;
    }
    
    putc(UART, (int) *(s + i));
    i++;
  }
  
  return 1;
}

void putclear(void) {
  puts(USART2, "\033[2J");
  puts(USART2, "\033[H");
}

void printchar(struct _USART volatile *UART, char **str, int c) {
  if (str) {
    **str = c;
    ++(*str);
  } else
    (void) putc(UART, c);
}

int prints(struct _USART volatile *UART, char **out, const char *string, int width, int pad) {
  register int pc = 0, padchar = ' ';

  if (width > 0) {
    register int len = 0;
    register const char *ptr;
    for (ptr = string; *ptr; ++ptr)
      ++len;
    if (len >= width)
      width = 0;
    else
      width -= len;
    if (pad & PAD_ZERO)
      padchar = '0';
  }
  if (!(pad & PAD_RIGHT)) {
    for (; width > 0; --width) {
      printchar(UART, out, padchar);
      ++pc;
    }
  }
  for (; *string; ++string) {
    printchar(UART, out, *string);
    ++pc;
  }
  for (; width > 0; --width) {
    printchar(UART, out, padchar);
    ++pc;
  }

  return pc;
}

// ======================================================================

int printi(struct _USART volatile *UART, char **out, int i, int b, int sg, int width, int pad, int letbase) {
  char print_buf[PRINT_BUF_LEN];
  register char *s;
  register int t, neg = 0, pc = 0;
  register unsigned int u = i;

  if (i == 0) {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    return prints(UART, out, print_buf, width, pad);
  }

  if (sg && b == 10 && i < 0) {
    neg = 1;
    u = -i;
  }

  s = print_buf + PRINT_BUF_LEN - 1;
  *s = '\0';

  while (u) {
    t = u % b;
    if (t >= 10)
      t += letbase - '0' - 10;
    *--s = t + '0';
    u /= b;
  }

  if (neg) {
    if (width && (pad & PAD_ZERO)) {
      printchar(UART, out, '-');
      ++pc;
      --width;
    } else {
      *--s = '-';
    }
  }

  return pc + prints(UART, out, s, width, pad);
}

int print(struct _USART volatile *UART, char **out, int *varg) {
  register int width, pad;
  register int pc = 0;
  register char *format = (char *) (*varg++);
  char scr[2];

  for (; *format != 0; ++format) {
    if (*format == '%') {
      ++format;
      width = pad = 0;
      if (*format == '\0')
	break;
      if (*format == '%')
	goto out;
      if (*format == '-') {
	++format;
	pad = PAD_RIGHT;
      }
      while (*format == '0') {
	++format;
	pad |= PAD_ZERO;
      }
      for (; *format >= '0' && *format <= '9'; ++format) {
	width *= 10;
	width += *format - '0';
      }
      if (*format == 's') {
	register char *s = *((char **) varg++);
	pc += prints(UART, out, s ? s : "(null)", width, pad);
	continue;
      }
      if (*format == 'd') {
	pc += printi(UART, out, *varg++, 10, 1, width, pad, 'a');
	continue;
      }
      if (*format == 'x') {
	pc += printi(UART, out, *varg++, 16, 0, width, pad, 'a');
	continue;
      }
      if (*format == 'X') {
	pc += printi(UART, out, *varg++, 16, 0, width, pad, 'A');
	continue;
      }
      if (*format == 'u') {
	pc += printi(UART, out, *varg++, 10, 0, width, pad, 'a');
	continue;
      }
      if (*format == 'c') {
	/* char are converted to int then pushed on the stack */
	scr[0] = *varg++;
	scr[1] = '\0';
	pc += prints(UART, out, scr, width, pad);
	continue;
      }
    } else {
    out:
      printchar(UART, out, *format);
      ++pc;
    }
  }
  if (out)
    **out = '\0';
  return pc;
}

int printf(struct _USART volatile *UART, const char *format, ...) {
  char line[MAX_UART_LINE];
  char *out = line;

  register int *varg = (int *) (&format);
  print(UART, &out, varg);
  return puts(UART, line);
}

int printf(const char *format, ...) {
  char line[MAX_UART_LINE];
  char *out = line;

  register int *varg = (int *) (&format);
  print(DEFAULT_USART, &out, varg);
  return puts(DEFAULT_USART, line);
}