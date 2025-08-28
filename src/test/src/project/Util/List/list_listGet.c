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




void *listGet(List *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listGet \n");
        return NULL;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listGet \n");
        return NULL;
    }

    void *value = pList->data[index];
    void *cp;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | listGet \n");
            return NULL;
        }

        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | listGet \n");
            return NULL;
        }
    }

    return cp;
}
