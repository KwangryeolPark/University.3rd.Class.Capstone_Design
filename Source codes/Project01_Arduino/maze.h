/*

  (Ko)    Copyright 2021. 박광렬 all rights reserved.
  (En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    maze.h
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:
                A star 알고리즘에서 사용될 Maze 구조체 선언

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (maze.h)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#ifndef _maze_h
#define _maze_h

//#include "type.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

typedef struct
{
  char (*field)[MAP_WIDTH];
  char obstacle;
  char player;
} Maze;

#endif
