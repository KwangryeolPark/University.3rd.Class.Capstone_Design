/*

(Ko)    Copyright 2021. 박광렬 all rights reserved.
(En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    atar.h
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:       
                A star 알고리즘

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (astar.h)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#ifndef _astar_h
#define _astar_h

#include <stdio.h>
#include "location.h"
#include "node.h"
#include "nodelist.h"
#include "maze.h"
#include "error.h"
#include "type.h"

#define DIR_FOUR true       //  It can be false or true
#define DIR_EIGHT !DIR_FOUR //  Do not modify

#define ERROR_ASTAR_CHECKING_ENABLE true //  It can be false or true

#if ERROR_ASTAR_CHECKING_ENABLE == true //  Do not modify
#define ERROR_CHECKING      \
    if (*error != ERROR_NO) \
    {                       \
        return;             \
    }
#endif

// ================================================================================

void astar(Maze *maze, Location start, Location end, ERROR_TYPE *error);

// ================================================================================
#if ERROR_ASTAR_CHECKING_ENABLE == false
void astar(Maze *maze, Location start, Location end, ERROR_TYPE *error)
{
    Location childRelativeLocations[8];
    init(&(childRelativeLocations[0]), 0, -1); //  Up
    init(&(childRelativeLocations[1]), 0, 1);  //  Down
    init(&(childRelativeLocations[2]), -1, 0); //  Left
    init(&(childRelativeLocations[3]), 1, 0);  //  Right
#if DIR_EIGHT == true
    init(&(childRelativeLocations[4]), 1, -1);  //  Up Right
    init(&(childRelativeLocations[5]), -1, -1); //  Up Left
    init(&(childRelativeLocations[6]), 1, 1);   //  Down Right
    init(&(childRelativeLocations[7]), -1, 1);  //  Down Left
#endif

    Node *startNode = createNode(error);
    Node *endNode = createNode(error);
    init(startNode, error);
    init(endNode, error);

    startNode->location = start;
    endNode->location = end;

    NodeList openList = NodeList(error);
    NodeList closeList = NodeList(error);

    openList.add(startNode, error);

    while (!(openList.isEmpty()))
    {
        //  This is the currentNode
        Node *currentNode;
        //  Pick the front node from the openList.
        openList.pickFront(&currentNode, error);

        for (Node *node; openList.iterate(&node, error);)
        {
            if ((currentNode->f) > (node->f))
            {
                currentNode = node;
            }
        }
        //        openList.iterateDone();

        openList.remove(currentNode, error);
        closeList.add(currentNode, error);

        //  Check destination
        if (isEqual(currentNode->location, endNode->location))
        {
            while (currentNode->parent != (Node *)0)
            {
                int x = currentNode->location.x;
                int y = currentNode->location.y;
                maze->field[y][x] = maze->player;

                currentNode = currentNode->parent;
            }
            break;
        }

        //  Nearest node check
        NodeList childrenList = NodeList(error);

#if DIR_FOUR == true
        for (int i = 0; i < 4; i++)
        {
            int x = currentNode->location.x + childRelativeLocations[i].x;
            int y = currentNode->location.y + childRelativeLocations[i].y;

            if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
            {
                continue;
            }

            if (maze->field[y][x] == maze->obstacle)
            {
                continue;
            }
            Node *childNode = createNode(error);
            init(childNode, error);
            childNode->parent = currentNode;
            childNode->location.x = x;
            childNode->location.y = y;
            childNode->dir = i;

            childrenList.add(childNode, error);
        }
#else
        for (int i = 0; i < 8; i++)
        {
            int x = currentNode->location.x + childRelativeLocations[i].x;
            int y = currentNode->location.y + childRelativeLocations[i].y;

            if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
            {
                continue;
            }

            if (maze->field[y][x] == maze->obstacle)
            {
                continue;
            }
            Node *childNode = createNode(error);
            init(childNode, error);
            childNode->parent = currentNode;
            childNode->location.x = x;
            childNode->location.y = y;
            childNode->dir = i;

            childrenList.add(childNode, error);
        }
#endif
        //	Check if the children nodes is in openList or closeList
        for (Node *childNode; childrenList.iterate(&childNode, error);)
        {

            int flag = 0;
            for (Node *iterate; closeList.iterate(&iterate, error);)
            {
                if (isEqual(iterate->location, childNode->location))
                {
                    flag = 1;
                    childrenList.removeByLocation(childNode, error);
                    terminate(childNode, error); //
                    break;
                }
            }
            //            closeList.iterateDone();

            if (flag == 1)
            {
                continue;
            }

            int add = 0;
            switch (childNode->dir)
            {
            case DIR_U:
            case DIR_D:
            case DIR_L:
            case DIR_R:
                add = 2;
                break;
            case DIR_UR:
            case DIR_UL:
            case DIR_DR:
            case DIR_DL:
                add = 3;
                break;
            }

            childNode->g = (currentNode->g) + add;
            childNode->h = (heuristic(childNode->location, endNode->location));
            childNode->f = childNode->g + childNode->h;

            flag = 0;
            Node *iterate;
            for (iterate; openList.iterate(&iterate, error);)
            {
                if (isEqual(iterate->location, childNode->location) == EQUAL)
                {
                    flag = 1;
                    childrenList.removeByLocation(childNode, error);
                    terminate(childNode, error); //
                    break;
                }
            }
            //            openList.iterateDone();

            if (flag == 1)
            {
                continue;
            }

            childrenList.removeByLocation(childNode, error);
            openList.add(childNode, error);
        }
        childrenList.terminate();
    }

    openList.terminate();
    closeList.terminate();
}

#else
void astar(Maze *maze, Location start, Location end, ERROR_TYPE *error)
{
    Location childRelativeLocations[8];
    init(&(childRelativeLocations[0]), 0, -1, error);  //  Up
    init(&(childRelativeLocations[1]), 0, 1, error);   //  Down
    init(&(childRelativeLocations[2]), -1, 0, error);  //  Left
    init(&(childRelativeLocations[3]), 1, 0, error);   //  Right
#if DIR_EIGHT == true
    init(&(childRelativeLocations[4]), 1, -1, error);  //  Up Right
    init(&(childRelativeLocations[5]), -1, -1, error); //  Up Left
    init(&(childRelativeLocations[6]), 1, 1, error);   //  Down Right
    init(&(childRelativeLocations[7]), -1, 1, error);  //  Down Left
#endif

    Node *startNode = createNode(error);
    ERROR_CHECKING
    Node *endNode = createNode(error);
    ERROR_CHECKING

    init(startNode, error);
    init(endNode, error);

    startNode->location = start;
    endNode->location = end;

    NodeList openList = NodeList(error);
    ERROR_CHECKING

    NodeList closeList = NodeList(error);
    ERROR_CHECKING

    openList.add(startNode, error);

    while (!(openList.isEmpty()))
    {
        //  This is the currentNode
        Node *currentNode;
        //  Pick the front node from the openList.
        openList.pickFront(&currentNode, error);

        for (Node *node; openList.iterate(&node, error);)
        {
            if ((currentNode->f) > (node->f))
            {
                currentNode = node;
            }
        }
        //        openList.iterateDone();

        openList.remove(currentNode, error);
        closeList.add(currentNode, error);

        //  Check destination
        if (isEqual(currentNode->location, endNode->location))
        {
            while (currentNode->parent != (Node *)0)
            {
                int x = currentNode->location.x;
                int y = currentNode->location.y;
                maze->field[y][x] = '*';

                currentNode = currentNode->parent;
            }

            *error = ERROR_NO;
            return;
        }

        //  Nearest node check
        NodeList childrenList = NodeList(error);
        ERROR_CHECKING

#if DIR_FOUR == true
        for (int i = 0; i < 4; i++)
        {
            int x = currentNode->location.x + childRelativeLocations[i].x;
            int y = currentNode->location.y + childRelativeLocations[i].y;

            if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
            {
                continue;
            }

            if (maze->field[y][x] == maze->obstacle)
            {
                continue;
            }
            Node *childNode = createNode(error);
            ERROR_CHECKING

            init(childNode, error);
            childNode->parent = currentNode;
            childNode->location.x = x;
            childNode->location.y = y;
            childNode->dir = i;

            childrenList.add(childNode, error);
        }
#else
        for (int i = 0; i < 8; i++)
        {
            int x = currentNode->location.x + childRelativeLocations[i].x;
            int y = currentNode->location.y + childRelativeLocations[i].y;

            if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
            {
                continue;
            }

            if (maze->field[y][x] == maze->obstacle)
            {
                continue;
            }
            Node *childNode = createNode(error);
            init(childNode, error);
            childNode->parent = currentNode;
            childNode->location.x = x;
            childNode->location.y = y;
            childNode->dir = i;

            childrenList.add(childNode, error);
        }
#endif
        //	Check if the children nodes is in openList or closeList
        for (Node *childNode; childrenList.iterate(&childNode, error);)
        {

            int flag = 0;
            for (Node *iterate; closeList.iterate(&iterate, error);)
            {
                if (isEqual(iterate->location, childNode->location))
                {
                    flag = 1;
                    childrenList.removeByLocation(childNode, error);
                    terminate(childNode, error); //
                    break;
                }
            }
            //            closeList.iterateDone();

            if (flag == 1)
            {
                continue;
            }

            int add = 0;
            switch (childNode->dir)
            {
            case DIR_U:
            case DIR_D:
            case DIR_L:
            case DIR_R:
                add = 2;
                break;
            case DIR_UR:
            case DIR_UL:
            case DIR_DR:
            case DIR_DL:
                add = 3;
                break;
            }

            childNode->g = (currentNode->g) + add;
            childNode->h = (heuristic(childNode->location, endNode->location));
            childNode->f = childNode->g + childNode->h;

            flag = 0;
            Node *iterate;
            for (iterate; openList.iterate(&iterate, error);)
            {
                if (isEqual(iterate->location, childNode->location) == EQUAL)
                {
                    flag = 1;
                    childrenList.removeByLocation(childNode, error);
                    terminate(childNode, error); //
                    break;
                }
            }
            //            openList.iterateDone();

            if (flag == 1)
            {
                continue;
            }

            childrenList.removeByLocation(childNode, error);
            openList.add(childNode, error);
        }
        childrenList.terminate();
    }

    openList.terminate();
    closeList.terminate();

    *error = ERROR_ROUTE_NO;
}

#endif
#endif
