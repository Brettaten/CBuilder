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














void *listCopy(void *pList)
{
    List *cp = (List *) pList;

    if (cp == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listCopy \n");
        return NULL;
    }

    List *listCopy = listCreate(cp->size, cp->copyElement, cp->freeElement);

    if (listCopy == NULL)
    {
        printf("[ERROR] : Function listCreate failed | listCopy \n");
        return NULL;
    }

    for (int i = 0; i < cp->length; i++)
    {
        void *temp;
        temp = listGet(cp, i);

        if (temp == NULL)
        {
            printf("[ERROR] : Function listGet failed | listCopy \n");
            return NULL;
        }

        int st1 = listAdd(listCopy, temp);

        if (st1 == -1)
        {
            printf("[ERROR] : Function listAdd failed | listCopy \n");
            return NULL;
        }

        if (cp->freeElement == NULL)
        {
            free(temp);
        }
        else
        {
            cp->freeElement(temp);
        }
    }

    return listCopy;
}
