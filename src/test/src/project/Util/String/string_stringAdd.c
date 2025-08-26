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



int stringAdd(String *pString, char value)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringAdd \n");
        return -1;
    }

    int st1 = listAdd(pString->list, &value);

    if (st1 == -1)
    {
        printf("[ERROR] : function listAdd failed | stringAdd");
        return -1;
    }

    return 0;
}