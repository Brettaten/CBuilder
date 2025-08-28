#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

typedef struct List
{
    void **data;
    int size;
    int buffer;
    int length;
    void *(*copyElement)(void *);
    void (*freeElement)(void *);
} List;


/**
 * Function used determine whether an index is in bounds
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return true or false
 */

bool isIndexInBoundsList(List *pList, int index);


List *listCreate(int size, void *(*copyElement)(void *), void (*freeElement)(void *))
{
    List *pList = (List *)malloc(sizeof(List));
    if (pList == NULL)
    {
        printf("[ERROR] : Memory allocation failed | listCreate \n");
        return NULL;
    }

    pList->data = (void **)malloc(sizeof(void *) * 8);
    if (pList->data == NULL)
    {
        free(pList);
        printf("[ERROR] : Memory allocation failed | listCreate \n");
        return NULL;
    }

    pList->buffer = 8;
    pList->length = 0;
    pList->size = size;
    pList->copyElement = copyElement;
    pList->freeElement = freeElement;

    return pList;
}
