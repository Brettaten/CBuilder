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








int doublyLinkedListAdd(DoublyLinkedList *pList, void *value)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListAdd \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | doublyLinkedListAdd \n");
        return -1;
    }

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | doublyLinkedListAdd \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | doublyLinkedListAdd \n");
            return -1;
        }
    }

    DoublyLinkedListNode *pNodeNew = (DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
    if (pNodeNew == NULL)
    {
        if (pList->freeElement == NULL)
        {
            free(cp);
        }
        else
        {
            pList->freeElement(cp);
        }

        printf("[ERROR] : Memory allocation failed | doublyLinkedListAdd \n");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;
    pNodeNew->prev = NULL;

    if (pList->length == 0)
    {
        pList->head = pNodeNew;
        pList->tail = pNodeNew;
    }
    else
    {
        DoublyLinkedListNode *node = pList->tail;

        node->next = pNodeNew;
        pNodeNew->prev = node;

        pList->tail = pNodeNew;
    }

    pList->length++;

    return 0;
}
