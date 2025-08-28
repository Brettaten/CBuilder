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










int listAddIndex(List *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listAddIndex \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | listAddIndex \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listAddIndex \n");
        return -1;
    }

    void *p1 = pList->data[pList->length - 1];

    int st1 = listAdd(pList, p1);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listAdd failed | listAddIndex \n");
        return -1;
    }

    for (int i = pList->length - 2; i > index; i--)
    {
        int st2 = listSwap(pList, i - 1, i);

        if (st2 == -1)
        {
            printf("[ERROR] : Function listSwap failed | listAddIndex \n");
            return -1;
        }
    }

    int st3 = listSet(pList, value, index);

    if (st3 == -1)
    {
        printf("[ERROR] : Function listSet failed | listAddIndex \n");
        return -1;
    }
    else
    {
        return 0;
    }
}
