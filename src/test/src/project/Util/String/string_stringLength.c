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





























int stringLength(String *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringLength \n");
        return -1;
    }

    return listLength(pString->list);
}