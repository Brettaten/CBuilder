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
















int listRemove(List *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listRemove \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listRemove \n");
        return -1;
    }

    if (pList->length == 0)
    {
        printf("[INFO] : List is empty | listRemove");
        return -1;
    }

    for (int i = index + 1; i < pList->length; i++)
    {
        int st1 = listSwap(pList, i, i - 1);

        if (st1 == -1)
        {
            printf("[ERROR] : Function listSwap failed | listRemove \n");
            return -1;
        }
    }

    void *lastP = pList->data[pList->length - 1];

    if (pList->freeElement == NULL)
    {
        free(lastP);
    }
    else
    {
        pList->freeElement(lastP);
    }

    lastP = NULL;
    pList->length--;

    return 0;
}
