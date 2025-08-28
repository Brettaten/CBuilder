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


















void listFree(void *pList)
{
    List *cp = (List *) pList;

    if (cp == NULL)
    {
        printf("[INFO] : Pointer to list is NULL | listFree \n");
        return;
    }

    for (int i = 0; i < cp->length; i++)
    {
        if (cp->freeElement == NULL)
        {
            free(cp->data[i]);
        }
        else
        {
            cp->freeElement(cp->data[i]);
        }
    }

    free(cp->data);
    free(cp);
}
