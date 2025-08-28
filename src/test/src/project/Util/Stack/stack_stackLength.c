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












int stackLength(Stack *pStack)
{
    if (pStack == NULL)
    {
        printf("[WARN] : Pointer to the stack is null | stackLength \n");
        return -1;
    }

    return doublyLinkedListLength(pStack->list);
}
