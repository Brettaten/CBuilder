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
