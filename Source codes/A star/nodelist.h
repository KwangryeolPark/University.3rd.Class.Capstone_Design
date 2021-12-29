/*

(Ko)    Copyright 2021. 박광렬 all rights reserved.
(En)    Copyright 2021. Kwangryeol Park all rights reserved.


    파일 명:    nodelist.h
    작성자:     박광렬
    연락처:     pkr7098@gmail.com
    생성 날짜:  2021-09-24          (YYYY-MM-DD)

    설명:       
                Node 구조체를 담을 수 있는 연결 리스트 형태의 List와 관련된 기능들

    연락 방법:  pkr7098@gmail.com으로 메일 보내기

                제목:   (본인 이름), (목적), (소속), (nodelist.h)
                내용:   구체적인 사용 목적, 수정할 계획이 있는지, 어디에서 사용할 프로그램인지(ex ??? 전시회에서 ??? 로봇에 사용될 프로그램입니다.)
*/

#ifndef _nodelist_h
#define _nodelist_h

#define NODELIST_DEBUG true
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "location.h"
#include "node.h"
#include "type.h"

#ifndef EQUAL
#define EQUAL   1
#endif

#ifndef UNEQUAL
#define UNEQUAL 0
#endif

// ================================================================================

#define ITERATE_STATE_DONE 0
#define ITERATE_STATE_ONGOING 1

// ================================================================================

class NodeList
{
public:
    //  Identifier
    //  It create Null Node head and init all factors
    NodeList(ERROR_TYPE *error);

    //  Add a node to link.
    void add(Node *node, ERROR_TYPE *error);

    //  Remove the node from linked list.
    //  It remove the Node depends on its potiner.
    void remove(Node *node, ERROR_TYPE *error);

    //  Remove the node from linked list.
    //  It remove the Node depends on its location.
    void removeByLocation(Node *node, ERROR_TYPE *error);

    //  Pick the first node in linked list.
    void pickFront(Node **node, ERROR_TYPE *error);

    //  Make the iterate function done
    //  It makes iterateState ITERATE_STATE_DONE
    void iterateDone();

    //  Delete all pointers in the list
    void terminate();

    //  Print all Node's information/
    void print(ERROR_TYPE *error);

    //  Notify the current list is empty or not
    //  Return:
    //  1:  Empty
    //  0:  Not empty
    int8_t isEmpty();

    //  For the iteration (while, for etc.)
    //  Return:
    //  1:  The iteration is ongoing
    //  0:  The iteration is done   /   An error occured
    int8_t iterate(Node **node, ERROR_TYPE *error);

    //  For the iteration (while, for etc.)
    //  Return:
    //  1:  The iteration is ongoing
    //  0:  The iteration is done   /   An error occured
    int8_t iterate(ERROR_TYPE *error);

    //  Search the node in the list depending on pointer
    //  Return:
    //  1(EQUAL)    :  The iteration is ongoing
    //  0(UNEQUAL)  :  The iteration is done   /   An error occured
    int8_t search(Node **node, ERROR_TYPE *error);

    //  Search the node in the list depending on the location
    //  Return:
    //  1(EQUAL)    :  The iteration is ongoing
    //  0(UNEQUAL)  :  The iteration is done   /   An error occured
    int8_t searchByLocation(Node **node, ERROR_TYPE *error);

private:
    //  The head of the linked list.
    Node *head;

    //  An element which is used to iterate function
    Node *iterateHead;

    //  The size of the linked list.
    //  The number of elements in the list.
    uint16_t size;

    //  The state of iteration  (ITERATE_STATE_DONE / ITERATE_STATE_ONGOING)
    int8_t iterateState;
};

// ================================================================================

NodeList::NodeList(ERROR_TYPE *error)
{

    //  Allocate memory to head node.
    head = createNode(error);

    //  Error checking.
    //  If head has no memory
    if (*error != ERROR_NO)
    {
#if NODELIST_DEBUG == true
        printError(*error, "NodeList::NodeList(ERROR_TYPE *error)", "An error occured during create head node!!");
#endif
        return;
    }
    //

    //  Clear the next of head.
    head->next = (Node *)0;
    //  Reset the size.
    size = 0;
    //  Reset the iterateState variable
    iterateState = ITERATE_STATE_DONE;
    //  No error detection.
    *error = ERROR_NO;
}

void NodeList::add(Node *node, ERROR_TYPE *error)
{

    //  Error checking.
    //  If head is empty.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::add(Node *node, ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }
    //  If the source node is empty.
    if (node == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::add(Node *node, ERROR_TYPE *error)", "The source node is Null");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }
    //  If the node has been linked.    ->  (It should call murge not add)
    if (node->next != (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_LIST_EXIST, "void NodeList::add(Node *node, ERROR_TYPE *error)", "The node has already linked to linked list", "Please unlink the node by calling remove() before call add() function");
#endif
        *error = ERROR_OBJECT_LIST_EXIST;
        return;
    }
    //  If the list exceed the max size
    if (size == MAX_UINT16)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OVERFLOW_INT16, "void NodeList::add(Node *node, ERROR_TYPE *error)", "The number of nodes in linked list exceeds the max size(int16) of the list");
#endif
        *error = ERROR_OVERFLOW_INT16;
        return;
    }
    //

    /*  Algorithm

        node -> null
        head -> ... -> node N -> null
        head -> node -> ... -> node N -> null
    */

    //  Link the node.
    node->next = head->next;
    head->next = node;

    //  Increase the size.
    size++;

    //  No error detection.
    *error = ERROR_NO;
}

void NodeList::remove(Node *node, ERROR_TYPE *error)
{

    //  Error checking
    //  If head has not memory allocation.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::remove(Node *node, ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }

    //  If the source node is null.
    if (node == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::remove(Node *node, ERROR_TYPE *error)", "The source node is Null");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }

    //	The object is empty
    if (size == 0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_LIST_EMPTY, "void NodeList::remove(Node *node, ERROR_TYPE *error)", "The list is empty");
#endif
        *error = ERROR_OBJECT_LIST_EMPTY;
        return;
    }

    /*  Algorithm

        node -> node M -> ...
        head -> ... -> node -> node M -> ...
        head -> ... -> node M -> ...
    */

    // Get first node.
    Node *preNode = head;
    Node *currentNode = head->next;

    while (currentNode != (Node *)0)
    {
        if (currentNode == node)
        {
            preNode->next = currentNode->next;
            currentNode->next = (Node *)0;
            size--;

            *error == ERROR_NO;
            return;
        }
        preNode = currentNode;
        currentNode = currentNode->next;
    }

    //  Error
    //  The source is not exist in the linked list.
#if NODELIST_DEBUG == true
    printError(ERROR_OBJECT_SEARCH, "void NodeList::remove(Node *node, ERROR_TYPE *error)", "The node is not in current list");
#endif
    *error = ERROR_OBJECT_SEARCH;
    return;
}

void NodeList::removeByLocation(Node *node, ERROR_TYPE *error)
{

    //  Error checking
    //  If head has not memory allocation.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::removeByLocation(Node *node, ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }

    //  If the source node is null.
    if (node == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::removeByLocation(Node *node, ERROR_TYPE *error)", "The source node is Null");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }
    //	The object is empty
    if (size == 0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_LIST_EMPTY, "void NodeList::removeByLocation(Node *node, ERROR_TYPE *error)", "The list is empty");
#endif
        *error = ERROR_OBJECT_LIST_EMPTY;
        return;
    }

    //

    /*  Algorithm

        node -> node M -> ...
        head -> ... -> node -> node M -> ...
        head -> ... -> node M -> ...
    */

    // Get first node.
    Node *preNode = head;
    Node *currentNode = head->next;

    while (currentNode != (Node *)0)
    {
        if (isEqual(currentNode->location, node->location))
        {
            preNode->next = currentNode->next;
            currentNode->next = (Node *)0;
            size--;
            
            *error == ERROR_NO;
            return;
        }
        preNode = currentNode;
        currentNode = currentNode->next;
    }

    //  Error
    //  The source is not exist in the linked list.
#if NODELIST_DEBUG == true
    printError(ERROR_OBJECT_SEARCH, "void NodeList::removeByLocation(Node *node, ERROR_TYPE *error)", "The node is not in current list");
#endif
    *error = ERROR_OBJECT_SEARCH;
    return;
}

void NodeList::pickFront(Node **node, ERROR_TYPE *error)
{
    //  Error checking
    //  If head has not memory allocation.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::removeByLocation(Node *node, ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }
    //

    /*  Algorithm

        head -> first node -> ...

        The first node could be a null node.
    */

    *node = head->next;

    *error = ERROR_NO;
}

int8_t NodeList::iterate(Node **node, ERROR_TYPE *error)
{
    //  Error checking
    //  If head has not memory allocation.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "int NodeList::iterate(Node **node, ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return 0;
    }
    //

    /*  Algorithm

        head -> node 1 -> node2 -> ....

        return node 1
        return node 2
        ...
        each time the function be called.

        Thanks to the head error checking, iterateHead
    */

    if (iterateState == ITERATE_STATE_DONE)
    {
        iterateState = ITERATE_STATE_ONGOING;
        iterateHead = head->next;
    }

    *node = iterateHead;

    if (iterateHead == (Node *)0)
    {
        iterateState = ITERATE_STATE_DONE;
        *error = ERROR_NO;
        return 0;
    }

    iterateHead = iterateHead->next;
    *error = ERROR_NO;
    return 1;
}

int8_t NodeList::iterate(ERROR_TYPE *error)
{
    //  Error checking
    //  If head has not memory allocation.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "int NodeList::iterate(ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return 0;
    }
    //

    /*  Algorithm

        head -> node 1 -> node2 -> ....

        return node 1
        return node 2
        ...
        each time the function be called.

        Thanks to the head error checking, iterateHead
    */

    if (iterateState == ITERATE_STATE_DONE)
    {
        iterateState = ITERATE_STATE_ONGOING;
        iterateHead = head->next;
    }
    if (iterateHead == (Node *)0)
    {
        iterateState = ITERATE_STATE_DONE;
        *error = ERROR_NO;
        return 0;
    }

    iterateHead = iterateHead->next;
    *error = ERROR_NO;
    return 1;
}

void NodeList::iterateDone()
{
    iterateState = ITERATE_STATE_DONE;
}

int8_t NodeList::isEmpty()
{
    if (size == 0)
    {
        return 1;
    }
    return 0;
}

void NodeList::terminate()
{
    if (head == (Node *)0)
    {
        return;
    }

    while (head->next != (Node *)0)
    {
        Node *currentNode = head->next;
        head->next = currentNode->next;
        free(currentNode);
    }

    free(head);
}

void NodeList::print(ERROR_TYPE *error)
{
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "void NodeList::print(ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return;
    }

    Node *currentNode = head->next;
    while (currentNode != (Node *)0)
    {
        printf("Pointer:(0x%8x), Location(%2d, %2d), Dir:%c, Next:(0x%8x)\n",
               currentNode,
               currentNode->location.x,
               currentNode->location.y,
               currentNode->dir,
               currentNode->next);

        currentNode = currentNode->next;
    }
    *error = ERROR_NO;
}

int8_t NodeList::search(Node **node, ERROR_TYPE *error)
{

    //  Error checking
    //  If head has not memory allocation.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "int NodeList::search(Node **node, ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return UNEQUAL;
    }

    //  If the source node is null.
    if (*node == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "int NodeList::search(Node **node, ERROR_TYPE *error)", "The source node is Null");
#endif
        *error = ERROR_OBJECT_NO;
        return UNEQUAL;
    }

    //	The object is empty
    if (size == 0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_LIST_EMPTY, "int NodeList::search(Node **node, ERROR_TYPE *error)", "The list is empty");
#endif
        *error = ERROR_OBJECT_LIST_EMPTY;
        return UNEQUAL;
    }

    /*  Algorithm

        node -> node M -> ...
        head -> ... -> node -> node M -> ...
        head -> ... -> node M -> ...
    */

    // Get first node.
    Node *currentNode = head->next;

    while (currentNode != (Node *)0)
    {
        if (currentNode == *node)
        {
            *error = ERROR_NO;
            return EQUAL;
        }
        currentNode = currentNode->next;
    }

    //  Error
    //  The source is not exist in the linked list.
#if NODELIST_DEBUG == true
    printError(ERROR_OBJECT_SEARCH, "int NodeList::search(Node **node, ERROR_TYPE *error)", "The node is not in current list");
#endif
    *error = ERROR_OBJECT_SEARCH;
    return UNEQUAL;
}

int8_t NodeList::searchByLocation(Node **node, ERROR_TYPE *error)
{

    //  Error checking
    //  If head has not memory allocation.
    if (head == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "int NodeList::searchByLocation(Node **node, ERROR_TYPE *error)", "The head node is Null", "Please call NodeList() when creating the list");
#endif
        *error = ERROR_OBJECT_NO;
        return UNEQUAL;
    }

    //  If the source node is null.
    if (*node == (Node *)0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "int NodeList::searchByLocation(Node **node, ERROR_TYPE *error)", "The source node is Null");
#endif
        *error = ERROR_OBJECT_NO;
        return UNEQUAL;
    }

    //	The object is empty
    if (size == 0)
    {
#if NODELIST_DEBUG == true
        printError(ERROR_OBJECT_NO, "int NodeList::searchByLocation(Node **node, ERROR_TYPE *error)", "The list is empty");
#endif
        *error = ERROR_OBJECT_NO;
        return UNEQUAL;
    }

    /*  Algorithm

        node -> node M -> ...
        head -> ... -> node -> node M -> ...
        head -> ... -> node M -> ...
    */

    // Get first node.
    Node *currentNode = head->next;

    while (currentNode != (Node *)0)
    {
        if (isEqual(currentNode->location, (*node)->location))
        {
            *error = ERROR_NO;
            return EQUAL;
        }
        currentNode = currentNode->next;
    }

    //  Error
    //  The source is not exist in the linked list.
#if NODELIST_DEBUG == true
    printError(ERROR_OBJECT_SEARCH, "int NodeList::searchByLocation(Node **node, ERROR_TYPE *error)", "The node is not in current list");
#endif
    *error = ERROR_OBJECT_SEARCH;
    return UNEQUAL;
}
#endif
