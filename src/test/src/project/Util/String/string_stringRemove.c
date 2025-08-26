#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "string.h"
#include "../List/list.h"

typedef struct String
{
    List *list;
} String;

/**
 * Function used determine whether an index is in bounds
 *
 * @param pString pointer to the string
 * @param index position in the string
 *
 * @return true or false
 */
bool isIndexInBoundsString(String *pString, int index);



























int stringRemove(String *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringRemove \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringRemove \n");
        return -1;
    }

    int st1 = listRemove(pString->list, index);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listRemove failed | stringRemove \n");
        return -1;
    }

    return 0;
}