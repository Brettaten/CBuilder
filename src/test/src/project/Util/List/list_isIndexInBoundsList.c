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


























bool isIndexInBoundsList(List *pList, int index)
{
    if (pList == NULL)
    {
        printf("[ERROR] : Pointer to list is NULL | isIndexInBoundsList \n");
        return -1;
    }

    if (index < 0 || index >= pList->length)
    {
        return false;
    }
    return true;
}
