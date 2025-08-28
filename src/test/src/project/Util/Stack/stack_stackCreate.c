#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stack.h"
#include "../DoublyLinkedList/doublyLinkedList.h"

typedef struct Stack
{
    DoublyLinkedList *list;
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
} Stack;


Stack *stackCreate(int size, void *(*copyElement)(void *), void (*freeElement)(void *))
{
    Stack *pStack = (Stack *)malloc(sizeof(Stack));

    if (pStack == NULL)
    {
        printf("[ERROR] : Memory allocation failed | stackCreate \n");
        return NULL;
    }

    DoublyLinkedList *pList = doublyLinkedListCreate(size, copyElement, freeElement);
    pStack->list = pList;
    pStack->copyElement = copyElement;
    pStack->freeElement = freeElement;

    return pStack;
}
