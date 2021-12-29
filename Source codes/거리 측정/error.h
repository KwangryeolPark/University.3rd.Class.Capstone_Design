/*

(Ko)    Copyright 2021. 박광렬 all rights reserved.
(En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    error.h
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:       
                A star 알고리즘에서 사용될 에러 관련 데이터 및 기능

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (error.h)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#ifndef _error_h
#define _error_h

#include <stdio.h>
#include <windows.h>
#include "type.h"

#define ERROR_NO 0

#define ERROR_MEMORY_NO (ERROR_NO + 1)
#define ERROR_MEMORY1 (ERROR_NO + 2)
#define ERROR_MEMORY2 (ERROR_NO + 3)
#define ERROR_MEMORY3 (ERROR_NO + 4)
#define ERROR_MEMORY4 (ERROR_NO + 5)
#define ERROR_MEMORY5 (ERROR_NO + 6)

#define ERROR_OBJECT_NO (ERROR_NO + 100 + 1)
#define ERROR_OBJECT_LIST_EXIST (ERROR_NO + 100 + 2)
#define ERROR_OBJECT_SEARCH (ERROR_NO + 100 + 3)
#define ERROR_OBJECT3 (ERROR_NO + 100 + 4)
#define ERROR_OBJECT4 (ERROR_NO + 100 + 5)
#define ERROR_OBJECT5 (ERROR_NO + 100 + 6)

#define ERROR_OVERFLOW_INT8 (ERROR_NO + 200 + 1)
#define ERROR_OVERFLOW_INT16 (ERROR_NO + 200 + 2)
#define ERROR_OVERFLOW_INT32 (ERROR_NO + 200 + 3)
#define ERROR_OVERFLOW_UINT8 (ERROR_NO + 200 + 4)
#define ERROR_OVERFLOW_UINT16 (ERROR_NO + 200 + 5)
#define ERROR_OVERFLOW_UINT32 (ERROR_NO + 200 + 6)
#define ERROR_UNDERFLOW_INT8 (ERROR_NO + 200 + 7)
#define ERROR_UNDERFLOW_INT16 (ERROR_NO + 200 + 8)
#define ERROR_UNDERFLOW_INT32 (ERROR_NO + 200 + 9)
#define ERROR_UNDERFLOW_UINT8 (ERROR_NO + 200 + 10)
#define ERROR_UNDERFLOW_UINT16 (ERROR_NO + 200 + 11)
#define ERROR_UNDERFLOW_UINT32 (ERROR_NO + 200 + 12)

#define ERROR_ROUTE_NO (ERROR_NO + 300 + 1)

#define ERROR_TYPE int16_t

#define ERROR_HIGHLIGHT true

#if ERROR_HIGHLIGHT == true //  Do not modify
#define ERROR_HIGHLIGHT_BLACK 0
#define ERROR_HIGHLIGHT_BLUE 1
#define ERROR_HIGHLIGHT_GREEN 2
#define ERROR_HIGHLIGHT_AQUA 3
#define ERROR_HIGHLIGHT_RED 4
#define ERROR_HIGHLIGHT_PURPLE 5
#define ERROR_HIGHLIGHT_YELLOW 6
#define ERROR_HIGHLIGHT_WHITE 7
#define ERROR_HIGHLIGHT_GRAY 8
#define ERROR_HIGHLIGHT_LIGHT_BLUE 9
#define ERROR_HIGHLIGHT_LIGHT_GREEN 0x0A
#define ERROR_HIGHLIGHT_LIGHT_AQUA 0x0B
#define ERROR_HIGHLIGHT_LIGHT_RED 0x0C
#define ERROR_HIGHLIGHT_LIGHT_PURPLE 0x0D
#define ERROR_HIGHLIGHT_LIGHT_YELLOW 0x0E
#define ERROR_HIGHLIGHT_BRIGHT_WHITE 0x0F
#endif

#define ERROR_HIGHLIGHT_COLOR             ERROR_HIGHLIGHT_LIGHT_RED
#define ERROR_HIGHLIGHT_CONTENTS_COLOR    ERROR_HIGHLIGHT_LIGHT_YELLOW
#define ERROR_HIGHLIGHT_SOLUTION_COLOR    ERROR_HIGHLIGHT_LIGHT_AQUA

//  Print the error
void printError(ERROR_TYPE error, char *location, char *message);
void printError(ERROR_TYPE error, char *location, char *message, char *solution);
void printError(ERROR_TYPE error, const char *location, const char *message);
void printError(ERROR_TYPE error, const char *location, const char *message, const char *solution);

#if ERROR_HIGHLIGHT == true
void printError(ERROR_TYPE error, char *location, char *message)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_COLOR);
    printf("% 4d ERROR\r\n", error);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_CONTENTS_COLOR);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_WHITE);
}
void printError(ERROR_TYPE error, char *location, char *message, char *solution)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_COLOR);
    printf("% 4d ERROR\r\n", error);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_CONTENTS_COLOR);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_SOLUTION_COLOR);
    printf("\tSolution:\t%s\r\n", solution);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_WHITE);
}
void printError(ERROR_TYPE error, const char *location, const char *message)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_COLOR);
    printf("% 4d ERROR\r\n", error);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_CONTENTS_COLOR);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_WHITE);
}
void printError(ERROR_TYPE error, const char *location, const char *message, const char *solution)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_COLOR);
    printf("% 4d ERROR\r\n", error);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_CONTENTS_COLOR);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_SOLUTION_COLOR);
    printf("\tSolution:\t%s\r\n", solution);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_HIGHLIGHT_WHITE);
}
#else
void printError(ERROR_TYPE error, char *location, char *message)
{
    printf("% 4d ERROR\r\n", error);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
}
void printError(ERROR_TYPE error, char *location, char *message, const char *solution)
{
    printf("% 4d ERROR\r\n", error);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
    printf("\tSolution:\t%s\r\n", solution);
}
void printError(ERROR_TYPE error, const char *location, const char *message)
{
    printf("% 4d ERROR\r\n", error);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
}
void printError(ERROR_TYPE error, const char *location, const char *message, const char *solution)
{
    printf("% 4d ERROR\r\n", error);
    printf("\tLocation:\t%s\r\n", location);
    printf("\tMessage :\t%s\r\n", message);
    printf("\tSolution:\t%s\r\n", solution);
}
#endif

#endif
