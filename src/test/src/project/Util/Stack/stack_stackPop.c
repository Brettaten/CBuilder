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
