#ifndef _PRINTF_H
#define _PRINTF_H

#define EOF	255
#define NULL    '\0'

char putc(char c);
char getc();
char getc_nb();
void puts(const char *string);
void putn(int64_t tim);

#endif

