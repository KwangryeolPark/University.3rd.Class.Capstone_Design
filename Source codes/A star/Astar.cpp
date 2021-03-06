/*

(Ko)    Copyright 2021. 박광렬 all rights reserved.
(En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    Astar.cpp
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:       
                A star 알고리즘

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (Astar.cpp)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "error.h"
#include "astar.h"

// ============================================================================================================

// ============================================================================================================

char map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

/*int map[MAP_HEIGHT][MAP_WIDTH] = {
	{' ', ' ', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '},
	{'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', 'O', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' '},
	{' ', 'O', 'O', ' ', ' ', 'O', ' ', ' ', ' ', ' '},
	{' ', ' ', 'O', 'O', ' ', ' ', 'O', ' ', ' ', ' '},
	{'O', ' ', 'O', ' ', 'O', ' ', ' ', 'O', 'O', ' '},
	{' ', ' ', 'O', 'O', 'O', 'O', ' ', ' ', ' ', 'O'},
	{' ', 'O', 'O', 'O', 'O', 'O', 'O', 'O', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'G'}};*/

void printMap(Maze maze);

// ============================================================================================================
// ============================================================================================================
// ============================================================================================================
// ============================================================================================================

int main(void)
{

	ERROR_TYPE error;
	Maze maze;
	maze.player = '*';
	maze.obstacle = 1;
	maze.field = map;

	Location start, end;
//	init(&start, 10, 10, &error);
	init(&start, 1, 0, &error);
	init(&end, 18, 2, &error);

	//	printMap(maze);

	astar(&maze, start, end, &error);
	if (error == ERROR_NO)
	{
		printMap(maze);
	}
	else
	{
		printf("The route is not found\n");
	}

	//	printMap(maze);
	return 0;
}

// ============================================================================================================
// ============================================================================================================
// ============================================================================================================
// ============================================================================================================

void printMap(Maze maze)
{
	printf(" ");
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		printf("--");
	}
	printf("\n");

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		printf("|");
		for (int ii = 0; ii < MAP_WIDTH; ii++)
		{
			if (maze.field[i][ii] == maze.player)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
				printf("%c ", maze.field[i][ii]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
			{
				printf("%c ", maze.field[i][ii]);
			}
		}
		printf("|\n");
	}

	printf(" ");
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		printf("--");
	}
	printf("\n");
}
