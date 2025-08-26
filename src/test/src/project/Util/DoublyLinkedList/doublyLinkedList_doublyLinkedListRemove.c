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













int doublyLinkedListRemove(DoublyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListRemove \n");
        return -1;
    }

    if (pList->length == 0)
    {
        printf("[INFO] : List is empty | doublyLinkedListRemove \n");
        return -1;
    }

    if (!isIndexInBoundsDoubly(pList, index))
    {
        printf("[INFO] : Index out of bounds | doublyLinkedListRemove \n");
        return -1;
    }

    DoublyLinkedListNode *pNodeP;
    DoublyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head->next;

        freeNode(pList, pList->head);
        pList->head = pNodeC;

        if (pNodeC == NULL)
        {
            pList->tail = NULL;
        }
        else
        {
            pNodeC->prev = NULL;
        }
    }
    else
    {
        pNodeP = doublyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            printf("[ERROR] : Function doublyLinkedListGetNode failed | doublyLinkedListRemove \n");
            return -1;
        }

        pNodeC = pNodeP->next->next;

        freeNode(pList, pNodeP->next);
        pNodeP->next = NULL;
        pNodeP->next = pNodeC;

        if (pNodeC == NULL)
        {
            pList->tail = pNodeP;
        }
        else
        {
            pNodeC->prev = pNodeP;
        }
    }

    pList->length--;

    return 0;
}