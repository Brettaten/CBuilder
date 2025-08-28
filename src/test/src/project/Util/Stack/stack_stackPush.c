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
