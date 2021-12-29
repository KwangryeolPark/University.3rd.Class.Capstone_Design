/*

(Ko)    Copyright 2021. 박광렬 all rights reserved.
(En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    node.h
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:       
                A star 알고리즘에서 사용될 Node 구조체 선언 및 관련 기능들

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (node.h)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#ifndef _node_h
#define _node_h

#define NODE_DEBUG true
#if NODE_DEBUG == true
#include <stdio.h>
#endif

#include "error.h"
#include "location.h"
#include "type.h"

typedef struct _Node
{
    Location location;
    uint16_t f, g, h;

    struct _Node *parent;
    struct _Node *next;

    char dir;
} Node;

// ================================================================================

//  Create a node and initiate it.
Node *createNode(ERROR_TYPE *error);

//  Initiate the correspond node.
Node *init(Node *node, ERROR_TYPE *error);

//  Delete the current node.
void terminate(Node *node, ERROR_TYPE *error);

// ================================================================================

Node *createNode(ERROR_TYPE *error)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == (Node *)0)
    {
#if NODE_DEBUG == true
        printError(ERROR_MEMORY_NO, "Node *createNode(ERROR_TYPE *error)", "There is no memory in heap section!!");
#endif
        *error = ERROR_MEMORY_NO;
        return (Node *)0;
    }
    *error = ERROR_NO;
    return init(newNode, error);
}

Node *init(Node *node, ERROR_TYPE *error)
{
    if (node == (Node *)0)
    {
#if NODE_DEBUG == true
        printError(ERROR_MEMORY_NO, "Node *init(Node *node, ERROR_TYPE *error)", "The node is Null!!");
#endif
        *error = ERROR_OBJECT_NO;
        return (Node *)0;
    }

    init(&(node->location), error);
    node->f = 0;
    node->g = 0;
    node->h = 0;
    node->parent = (Node *)0;
    node->next = (Node *)0;
    node->dir = 'X';

    *error = ERROR_NO;
    return node;
};

void terminate(Node *node, ERROR_TYPE *error)
{
    if (node == (Node *)0)
    {
#if NODE_DEBUG == true
        printError(ERROR_OBJECT_NO, "void terminate(Node *node, ERROR_TYPE *error)", "The node is Null!!");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }

    *error = ERROR_NO;
    free(node);
}

#endif
