#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "doublyLinkedList.h"

/**
 * Function used to get a node at the passed index
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return Success: pointer to a node | Failure: NULL
 */

DoublyLinkedListNode *doublyLinkedListGetNode(DoublyLinkedList *pList, int index);


/**
 * Function used determine whether an index is in bounds
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return true or false
 */

bool isIndexInBoundsDoubly(DoublyLinkedList *pList, int index);


/**
 * Function used to create a deep copy of a node
 *
 * @param pList the pointer to the list
 * @param pNode the pointer to the node
 *
 * @return Success: the copy of the node | Failure: NULL
 *
 * @note The value is deep copied while next is set to null
 */

DoublyLinkedListNode *doublyLinkedListNodeCopy(DoublyLinkedList *pList, DoublyLinkedListNode *pNode);


/**
 * Function used to free a node
 *
 * @param pNode pointer to the node
 *
 * @return NULL
 */

void freeNode(DoublyLinkedList *pList, DoublyLinkedListNode *pNode);


typedef struct DoublyLinkedList
{
    DoublyLinkedListNode *head;
    DoublyLinkedListNode *tail;
    int length;
    int size;
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
} DoublyLinkedList;


typedef struct DoublyLinkedListNode
{
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
    void *value;
} DoublyLinkedListNode;








































DoublyLinkedListNode *doublyLinkedListNodeCopy(DoublyLinkedList *pList, DoublyLinkedListNode *pNode)
{
    if (pList == NULL)
    {
        printf("[ERROR] : List is null | doublyLinkedListNodeCopy \n");
        return NULL;
    }

    if (pNode == NULL)
    {
        printf("[ERROR] : Node is null | doublyLinkedListNodeCopy \n");
        return NULL;
    }

    if(pNode->value == NULL){
        printf("[ERROR] : Value is null | doublyLinkedListNodeCopy \n");
        return NULL;
    }

    DoublyLinkedListNode *copy = (DoublyLinkedListNode *) malloc(sizeof(DoublyLinkedListNode));

    if(copy == NULL){
        printf("[ERROR] : Memory allocation failed | doublyLinkedListNodeCopy \n");
        return NULL;
    }

    copy->next = NULL;
    copy->prev = NULL;

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | doublyLinkedListNodeCopy \n");
            return NULL;
        }

        memcpy(cp, pNode->value, pList->size);
    }
    else
    {
        cp = pList->copyElement(pNode->value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | doublyLinkedListNodeCopy \n");
            return NULL;
        }
    }

    copy->value = cp;

    return copy;
}
