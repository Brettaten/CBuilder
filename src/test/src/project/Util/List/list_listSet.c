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






int listSet(List *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listSet \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | listSet \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listSet \n");
        return -1;
    }

    void *cp = NULL;

    if (pList->copyElement == NULL)
    {
        cp = (void *)malloc(pList->size);

        if (cp == NULL)
        {
            printf("[ERROR] : Memory allocation failed | listSet \n");
            return -1;
        }
        memcpy(cp, value, pList->size);
    }
    else
    {
        cp = pList->copyElement(value);

        if (cp == NULL)
        {
            printf("[ERROR] : Function copyElement failed | listSet \n");
            return -1;
        }
    }

    void *lp = pList->data[index];

    if (pList->freeElement == NULL)
    {
        free(lp);
    }
    else
    {
        pList->freeElement(lp);
    }

    lp = NULL;

    pList->data[index] = cp;

    return 0;
}
