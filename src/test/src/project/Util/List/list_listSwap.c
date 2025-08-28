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












int listSwap(List *pList, int index1, int index2)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listSwap \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index1) || !isIndexInBoundsList(pList, index2))
    {
        printf("[INFO] : Index out of bounds | listSwap \n");
        return -1;
    }

    void *temp = pList->data[index1];
    pList->data[index1] = pList->data[index2];
    pList->data[index2] = temp;

    return 0;
}
