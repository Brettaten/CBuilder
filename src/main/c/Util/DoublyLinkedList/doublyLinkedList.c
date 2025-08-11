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
bool isIndexInBounds(DoublyLinkedList *pList, int index);

/**
 * Function used to free a node
 *
 * @param pNode pointer to the node
 *
 * @return NULL
 *
 * @note This function only frees the pointer. If a struct is stored, that itself contains a pointer,
 * this pointer will not be freed.
 */
void freeNode(DoublyLinkedListNode *pNode);

typedef struct DoublyLinkedList
{
    DoublyLinkedListNode *head;
    DoublyLinkedListNode *tail;
    int length;
    int size;
} DoublyLinkedList;

typedef struct DoublyLinkedListNode
{
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
    void *value;
} DoublyLinkedListNode;

DoublyLinkedList *doublyLinkedListCreate(int size)
{
    DoublyLinkedList *pList = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));

    if (pList == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListCreate \n");
        return NULL;
    }

    pList->head = NULL;
    pList->tail = NULL;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void *doublyLinkedListGet(DoublyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListGet \n");
        return NULL;
    }

    if (!isIndexInBounds(pList, index))
    {
        printf("[INFO] : Index out of bounds | doublyLinkedListGet \n");
        return NULL;
    }

    DoublyLinkedListNode *pNode = doublyLinkedListGetNode(pList, index);

    if (pNode == NULL)
    {
        printf("[ERROR] : Function doublyLinkedListGetNode failed | doublyLinkedListGet \n");
        return NULL;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListGet \n");
        return NULL;
    }

    memcpy(cp, pNode->value, pList->size);

    return cp;
}

int doublyLinkedListSet(DoublyLinkedList *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListSet \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | doublyLinkedListSet \n");
        return -1;
    }

    if (!isIndexInBounds(pList, index))
    {
        printf("[INFO] : Index out of bounds | doublyLinkedListSet \n");
        return -1;
    }

    DoublyLinkedListNode *pNode = doublyLinkedListGetNode(pList, index);

    if (pNode == NULL)
    {
        printf("[ERROR] : Function doublyLinkedListGetNode failed | doublyLinkedListSet \n");
        return -1;
    }

    free(pNode->value);
    pNode->value = NULL;

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListSet \n");
        return -1;
    }

    memcpy(cp, value, pList->size);

    pNode->value = cp;

    return 0;
}

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

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListAdd \n");
        return -1;
    }

    memcpy(cp, value, pList->size);

    DoublyLinkedListNode *pNodeNew = (DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
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

int doublyLinkedListAddIndex(DoublyLinkedList *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListAddIndex \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | doublyLinkedListAddIndex \n");
        return -1;
    }

    if (!isIndexInBounds(pList, index))
    {
        printf("[INFO] : Index out of bounds | doublyLinkedListAddIndex \n");
        return -1;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListAddIndex \n");
        return -1;
    }

    memcpy(cp, value, pList->size);

    DoublyLinkedListNode *pNodeNew = (DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
        printf("[ERROR] : Memory allocation failed | doublyLinkedListAddIndex \n");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;
    pNodeNew->prev = NULL;

    DoublyLinkedListNode *pNodeP;
    DoublyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head,

        pList->head = pNodeNew;
        pNodeNew->next = pNodeC;

        if (pList->length == 0)
        {
            pList->tail = pNodeNew;
        }
    }
    else
    {
        pNodeP = doublyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            free(cp);
            free(pNodeNew);
            printf("[ERROR] : Function doublyLinkedListGetNode failed | doublyLinkedListAddIndex \n");
            return -1;
        }

        pNodeC = pNodeP->next;

        pNodeP->next = pNodeNew;
        pNodeNew->prev = pNodeP;
        pNodeNew->next = pNodeC;
        pNodeC->prev = pNodeNew;
    }

    pList->length++;

    return 0;
}

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

    if (!isIndexInBounds(pList, index))
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

        freeNode(pList->head);
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

        freeNode(pNodeP->next);
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

int doublyLinkedListLength(DoublyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListLength \n");
        return -1;
    }

    return pList->length;
}

int doublyLinkedListSize(DoublyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListSize \n");
        return -1;
    }

    return pList->size;
}

DoublyLinkedListNode *doublyLinkedListGetHead(DoublyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListGetHead \n");
        return NULL;
    }

    return pList->head;
}

DoublyLinkedListNode *doublyLinkedListGetTail(DoublyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListGetTail \n");
        return NULL;
    }

    return pList->tail;
}

DoublyLinkedListNode *doublyLinkedListNodeNext(DoublyLinkedListNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | doublyLinkedListNodeNext \n");
        return NULL;
    }

    return pNode->next;
}

DoublyLinkedListNode *doublyLinkedListNodePrev(DoublyLinkedListNode *pNode)
{
    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | doublyLinkedListNodeNext \n");
        return NULL;
    }

    return pNode->prev;
}

void *doublyLinkedListNodeGet(DoublyLinkedList *pList, DoublyLinkedListNode *pNode)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListNodeGet \n");
        return NULL;
    }

    if (pNode == NULL)
    {
        printf("[INFO] : Pointer to node is NULL | doublyLinkedListNodeGet \n");
        return NULL;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListNodeGet \n");
        return NULL;
    }

    memcpy(cp, pNode->value, pList->size);

    return cp;
}

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

    free(pNode->value);
    pNode->value = NULL;

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | doublyLinkedListNodeSet \n");
        return -1;
    }

    memcpy(cp, value, pList->size);

    pNode->value = cp;

    return 0;
}

void doublyLinkedListFree(DoublyLinkedList *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListGetHead \n");
        return;
    }

    DoublyLinkedListNode *pNode = pList->head;

    for (int i = 0; i < pList->length; i++)
    {
        DoublyLinkedListNode *pNodeTemp = pNode->next;

        freeNode(pNode);
        pNode = pNodeTemp;
    }

    free(pList);
}

DoublyLinkedListNode *doublyLinkedListGetNode(DoublyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListGetNode \n");
        return NULL;
    }

    if (pList->length == 0)
    {
        printf("[INFO] : List is empty | doublyLinkedListGetNode \n");
        return NULL;
    }

    if (!isIndexInBounds(pList, index))
    {
        printf("[INFO] : Index out of bounds | doublyLinkedListGetNode\n");
        return NULL;
    }

    DoublyLinkedListNode *node;

    if (index <= pList->length / 2)
    {
        node = pList->head;

        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
    }
    else
    {
        node = pList->tail;

        for (int i = pList->length - 1; i > index; i--)
        {
            node = node->prev;
        }
    }

    return node;
}

bool isIndexInBounds(DoublyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[ERROR] : Pointer to list is NULL | isIndexInBounds \n");
        return -1;
    }

    if (pList == NULL)
    {
        return false;
    }

    if (index < 0 || index >= pList->length)
    {
        return false;
    }
    return true;
}

void freeNode(DoublyLinkedListNode *pNode)
{
    free(pNode->value);
    pNode->value = NULL;
    pNode->next = NULL;
    pNode->prev = NULL;
    free(pNode);

    pNode = NULL;
}
