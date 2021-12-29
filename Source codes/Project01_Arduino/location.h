/*

(Ko)    Copyright 2021. 박광렬 all rights reserved.
(En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    location.h
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:       
                A star 알고리즘에서 사용될 좌표 구조체 선언 밑 관련 기능

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (location.h)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#ifndef _location_h
#define _location_h

#define LOCATION_DEBUG false
#if LOCATION_DEBUG == true
#include <stdio.h>
#endif

#include "error.h"
//#include "type.h"

#ifndef EQUAL
#define EQUAL 1
#endif

#ifndef UNEQUAL
#define UNEQUAL 0
#endif

#define DIR_U 0
#define DIR_D 1
#define DIR_L 2
#define DIR_R 3
#define DIR_UR 4
#define DIR_UL 5
#define DIR_DR 6
#define DIR_DL 7

// ================================================================================

typedef struct _Location
{
    int8_t x, y;
} Location;

// ================================================================================

//  Initiate the location variable by x and y
void init(Location *location, int8_t x, int8_t y, ERROR_TYPE *error);

//  Initiate the location variable to x = 0 and y = 0
void init(Location *location, ERROR_TYPE *error);

//  Judge the two locations are directing same coordinate
ERROR_TYPE isEqual(Location location1, Location location2);
ERROR_TYPE isEqual(Location *location1, Location *location2);

//  Calculate the heuristic
int32_t heuristic(Location location1, Location location2);
int32_t heuristic(Location *location1, Location *location2, ERROR_TYPE *error);

// ================================================================================

void init(Location *location, int8_t x, int8_t y, ERROR_TYPE *error)
{
    if (location == (Location *)0)
    {
#if LOCATION_DEBUG == true
        printError(ERROR_OBJECT_NO, "void init(Location *location, int8_t x, int8_t y, ERROR_TYPE *error)", "location is Null!!");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }
    location->x = x;
    location->y = y;
}

void init(Location *location, ERROR_TYPE *error)
{
    if (location == (Location *)0)
    {
#if LOCATION_DEBUG == true
        printError(ERROR_OBJECT_NO, "void init(Location *location)", "location is Null!!");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }
    init(location, 0, 0, error);
};

ERROR_TYPE isEqual(Location location1, Location location2)
{
    if (location1.x == location2.x && location1.y == location2.y)
    {
        return EQUAL;
    }

    return UNEQUAL;
}

ERROR_TYPE isEqual(Location *location1, Location *location2)
{
    if (location1->x == location2->x && location1->y == location2->y)
    {
        return EQUAL;
    }

    return UNEQUAL;
}

int32_t heuristic(Location location1, Location location2)
{
    int16_t dx = location1.x - location2.x;
    int16_t dy = location1.y - location2.y;

    dx = (dx < 0) ? -dx : dx;
    dy = (dy < 0) ? -dy : dy;

    int32_t dM = (dx < dy) ? dy : dx;
    int32_t dm = (dx > dy) ? dy : dx;

    dM = dM - dm;

    return dm * 3 + dM * 2;
}

int32_t heuristic(Location *location1, Location *location2, ERROR_TYPE *error)
{
    if (location1 == (Location *)0 || location2 == (Location *)0)
    {
#if LOCATION_DEBUG == true
        printError(ERROR_OBJECT_NO, "int32_t heuristic(Location *location1, Location *location2, ERROR_TYPE *error)", "location1 or location2 is Null!!");
#endif
        *error = ERROR_OBJECT_NO;
        return -1;
    }
    int16_t dx = location1->x - location2->x;
    int16_t dy = location1->y - location2->y;

    dx = (dx < 0) ? -dx : dx;
    dy = (dy < 0) ? -dy : dy;

    int32_t dM = (dx < dy) ? dy : dx;
    int32_t dm = (dx > dy) ? dy : dx;

    *error = ERROR_NO;
    return dm * 3 + dM * 2;
}

#endif
