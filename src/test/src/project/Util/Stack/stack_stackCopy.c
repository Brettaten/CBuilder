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
