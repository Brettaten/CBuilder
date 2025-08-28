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








int listAdd(List *pList, void *value)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listAdd \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | listAdd \n");
        return -1;
    }

    if (pList->length == pList->buffer)
    {
        pList->data = (void **)realloc(pList->data, sizeof(void *) * pList->buffer * 2);
        if (pList->data == NULL)
        {
            printf("[ERROR] : Memory allocation failed | listAdd \n");
            return -1;
        }

        pList->buffer = pList->buffer * 2;
    }

    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | listAdd \n");
            return -1;
        }
        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | listAdd \n");
            return -1;
        }
    }

    pList->data[pList->length] = cp;
    pList->length++;

    return 0;
}
