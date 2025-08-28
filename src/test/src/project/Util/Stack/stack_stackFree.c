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
