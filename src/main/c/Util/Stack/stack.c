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
    int length = stackLength(pStack);
    int st1 = doublyLinkedListRemove(pStack->list, length - 1);

    if (st1 == -1)
    {
        if(pStack->freeElement == NULL){
            free(value);
        }
        else{
            pStack->freeElement(value);
        }

        printf("[ERROR] : Function doublyLinkedListRemove failed | stackPop \n");
        return NULL;
    }

    return value;
}

void *stackPeek(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackPeek \n");
        return NULL;
    }

    int length = stackLength(pStack);
    if (length == 0)
    {
        printf("[INFO] : Stack is empty | stackPeek \n");
        return NULL;
    }

    void *value = doublyLinkedListGet(pStack->list, length - 1);

    if (value == NULL)
    {
        printf("[ERROR] : Function doublyLinkedListGet failed | stackPeek \n");
        return NULL;
    }

    return value;
}

void *stackCopy(void *pStack)
{
    Stack *cp = (Stack *) pStack;

    if(cp == NULL){
        printf("[ERROR] : Stack is null | stackCopy \n");
        return NULL;
    }

    Stack *copy = (Stack *) malloc(sizeof(Stack));

    if(copy == NULL){
        printf("[ERROR] : Memory allocation failed | stackCopy \n");
        return NULL;
    }

    copy->copyElement = cp->copyElement;
    copy->freeElement = cp->freeElement;

    DoublyLinkedList *copyList = (DoublyLinkedList *) doublyLinkedListCopy(cp->list);

    if(copyList == NULL){
        printf("[ERROR] : Function doublyLinkedListCopy failed | stackCopy \n");
        return NULL;
    }

    copy->list = copyList;

    return copy;
}

int stackLength(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackLength \n");
        return -1;
    }

    return doublyLinkedListLength(pStack->list);
}

int stackContentSize(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackSize \n");
        return -1;
    }

    return doublyLinkedListSize(pStack->list);
}

int stackSize(){
    return sizeof(Stack);
}

void stackFree(void *pStack)
{
    Stack *cp = (Stack *) pStack;

    if(cp == NULL){
        printf("[WARN] : stack is null | stackFree \n");
        return;
    }

    doublyLinkedListFree(cp->list);

    free(cp);
}
