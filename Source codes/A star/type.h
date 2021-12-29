/*

(Ko)    Copyright 2021. 박광렬 all rights reserved.
(En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    type.h
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:       
                프로그램에서 사용될 자료형, 데이터 밑 관련 기능

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (type.h)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#ifndef _type_h
#define _type_h

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;

#define MAX_INT8 255
#define MIN_INT8 0
#define MAX_UINT8 127
#define MIN_UINT8 -128
#define MAX_INT16 65535
#define MIN_INT16 0
#define MAX_UINT16 32767
#define MIN_UINT16 -32768
#define MAX_INT32 4294967295
#define MIN_INT32 0
#define MAX_UINT32 2147483647
#define MIN_UINT32 -2147483648

#endif