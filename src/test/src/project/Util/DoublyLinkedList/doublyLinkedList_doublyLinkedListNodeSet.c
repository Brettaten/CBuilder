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
































int doublyLinkedListNodeSet(DoublyLinkedList *pList, DoublyLinkedListNode *pNode, void *value)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListNodeSet \n");
        return -1;
    }

    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | doublyLinkedListNodeSet \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | doublyLinkedListNodeSet \n");
        return -1;
    }

    if (pList->freeElement == NULL)
    {
        free(pNode->value);
    }
    else
    {
        pList->freeElement(pNode->value);
    }

    pNode->value = NULL;

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | doublyLinkedListNodeSet \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | doublyLinkedListNodeSet \n");
            return -1;
        }
    }

    pNode->value = cp;

    return 0;
}
