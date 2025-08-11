#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stack.h"
#include "../DoublyLinkedList/doublyLinkedList.h"

typedef struct Stack
{
    DoublyLinkedList *list;
    int size;
    int length;
} Stack;

Stack *stackCreate(int size)
{
    Stack *pStack = (Stack *)malloc(sizeof(Stack));

    if (pStack == NULL)
    {
        printf("[ERROR] : Memory allocation failed | stackCreate \n");
        return NULL;
    }

    DoublyLinkedList *pList = doublyLinkedListCreate(size);
    pStack->list = pList;
    pStack->size = size;
    pStack->length = 0;

    return pStack;
}

int stackPush(Stack *pStack, void *value)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackPush \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to the value is null | stackPush \n");
        return -1;
    }

    int st1 = doublyLinkedListAdd(pStack->list, value);

    if (st1 == -1)
    {
        printf("[ERROR] : Function doublyLinkedListAdd failed | stackPush \n");
        return -1;
    }

    pStack->length++;

    return 0;
}

void *stackPop(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackPop \n");
        return NULL;
    }

    void *value = stackPeek(pStack);

    if (value == NULL)
    {
        printf("[ERROR] : Function stackPeek failed | stackPop \n");
        return NULL;
    }

    int st1 = doublyLinkedListRemove(pStack->list, pStack->length - 1);

    if (st1 == -1)
    {
        printf("[ERROR] : Function doublyLinkedListRemove failed | stackPop \n");
        free(value);
        return NULL;
    }

    pStack->length--;

    return value;
}

void *stackPeek(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackPeek \n");
        return NULL;
    }

    if (pStack->length == 0)
    {
        printf("[INFO] : List is empty | stackPeek \n");
        return NULL;
    }

    void *value = doublyLinkedListGet(pStack->list, pStack->length - 1);

    if (value == NULL)
    {
        printf("[ERROR] : Function doublyLinkedListGet failed | stackPeek \n");
        return NULL;
    }

    return value;
}

int stackLength(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackLength \n");
        return -1;
    }

    return pStack->length;
}

int stackSize(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackSize \n");
        return -1;
    }

    return pStack->size;
}

void stackFree(Stack *pStack)
{
    doublyLinkedListFree(pStack->list);

    free(pStack);
}
