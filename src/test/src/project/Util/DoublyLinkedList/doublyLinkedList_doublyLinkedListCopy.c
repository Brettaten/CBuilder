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












void *doublyLinkedListCopy(void *pList)
{
    DoublyLinkedList *cp = (DoublyLinkedList *)pList;

    if (cp == NULL)
    {
        printf("[ERROR] : List is null | doublyLinkedListCopy \n");
        return NULL;
    }

    DoublyLinkedList *copy = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));

    if (copy == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListCopy \n");
        return NULL;
    }

    copy->copyElement = cp->copyElement;
    copy->freeElement = cp->freeElement;
    copy->length = cp->length;
    copy->size = cp->size;

    copy->head = doublyLinkedListNodeCopy(cp, cp->head);

    DoublyLinkedListNode *dest = copy->head;
    DoublyLinkedListNode *src = cp->head;

    while (src->next != NULL)
    {
        dest->next = doublyLinkedListNodeCopy(cp, src->next);

        if (dest->next == NULL)
        {
            printf("[ERROR] : Function doublyLinkedListNodeCopy failed | doublyLinkedListCopy \n");
            return NULL;
        }

        dest->next->prev = dest;

        dest = dest->next;
        src = src->next;
    }

    copy->tail = dest;
    
    return copy;
}
