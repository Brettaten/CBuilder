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









int stringSet(String *pString, char value, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringSet \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringSet \n");
        return -1;
    }

    int st1 = listSet(pString->list, &value, index);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listSet failed | stringSet \n");
        return -1;
    }

    return 0;
}