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

DoublyLinkedList *doublyLinkedListCreate(int size, void *(*copyElement)(void *), void (*freeElement)(void *))
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
    pList->copyElement = copyElement;
    pList->freeElement = freeElement;

    return pList;
}

void *doublyLinkedListGet(DoublyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListGet \n");
        return NULL;
    }

    if (!isIndexInBoundsDoubly(pList, index))
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

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | doublyLinkedListGet \n");
            return NULL;
        }

        memcpy(cp, pNode->value, pList->size);
    }
    else
    {
        cp = pList->copyElement(pNode->value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | doublyLinkedListGet \n");
            return NULL;
        }
    }

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

    if (!isIndexInBoundsDoubly(pList, index))
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
            printf("[ERROR] : Memory allocation failed | doublyLinkedListSet \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | doublyLinkedListSet \n");
            return -1;
        }
    }

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

    if (!isIndexInBoundsDoubly(pList, index))
    {
        printf("[INFO] : Index out of bounds | doublyLinkedListAddIndex \n");
        return -1;
    }

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | doublyLinkedListAddIndex \n");
            return -1;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | doublyLinkedListAddIndex \n");
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
            if (pList->freeElement == NULL)
            {
                free(cp);
            }
            else
            {
                pList->freeElement(cp);
            }

            freeNode(pList, pNodeNew);
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

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | doublyLinkedListNodeGet \n");
            return NULL;
        }

        memcpy(cp, pNode->value, pList->size);
    }
    else
    {
        cp = pList->copyElement(pNode->value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | doublyLinkedListNodeGet \n");
            return NULL;
        }
    }

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

void doublyLinkedListFree(void *pList)
{
    DoublyLinkedList *cp = (DoublyLinkedList *) pList;

    if (cp == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | doublyLinkedListGetHead \n");
        return;
    }

    DoublyLinkedListNode *pNode = cp->head;

    for (int i = 0; i < cp->length; i++)
    {
        DoublyLinkedListNode *pNodeTemp = pNode->next;

        freeNode(cp, pNode);
        pNode = pNodeTemp;
    }

    free(cp);
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

    if (!isIndexInBoundsDoubly(pList, index))
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

bool isIndexInBoundsDoubly(DoublyLinkedList *pList, int index)
{
    if (pList == NULL)
    {
        printf("[ERROR] : Pointer to list is NULL | isIndexInBoundsDoubly \n");
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

void freeNode(DoublyLinkedList *pList, DoublyLinkedListNode *pNode)
{
    if(pNode == NULL){
        printf("[INFO] : Pointer to node is NULL | freeNode \n");
        return;
    }

    if(pList->freeElement == NULL){
        free(pNode->value);
    }
    else{
        pList->freeElement(pNode->value);
    }

    pNode->value = NULL;
    pNode->next = NULL;
    pNode->prev = NULL;
    free(pNode);

    pNode = NULL;
}
