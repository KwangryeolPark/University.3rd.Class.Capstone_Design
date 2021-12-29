#include "usart.h"
#include "print.h"

char putc(char c) {
  
  if((c == '\n') || (c == '\r')) {
    while(!(USART1 -> SR & (1 << TXE))); // 전송 가능해질 때까지 기다립니다.
    USART1 -> DR = '\n';

    while(!(USART1 -> SR & (1 << TXE))); // 전송 가능해질 때까지 기다립니다.
    USART1 -> DR = '\r';
  } else {
      while(!(USART1 -> SR & (1 << TXE))); // 전송 가능해질 때까지 기다립니다.
      USART1 -> DR = c;    
  }
    

  return c;
}

char getc() {
    while(!(USART1 -> SR & (1 << RXEN))); // 
    
    char c = (USART1 -> DR);
    
    return c;
}

char getc_nb() {
	char c;
	if((USART1 -> SR & (1 << RXEN))) {
		c = (USART1 -> DR);
		putc(c);
		return c;
	}
	
	putc(0);
	return 0;
}

void puts(const char *string) {
  char c;
  for(uint32_t p = 0; (c = *(string + p)) != NULL; p++) {
    putc(c);
  }
}

void putn(int64_t tim) {
  char buf[10] = {0};
  int i = 0;
  if(tim < 0) {
    putc('-');
    tim = -tim;
  } else if(tim == 0) {
    putc('0');
    return;
  }
    
  for(; tim != 0; i++) {
    buf[i] = tim % 10;
    tim /= 10;
  }

  for(--i; i >= 0; i--) {
    putc(buf[i] + '0');
  }
}
