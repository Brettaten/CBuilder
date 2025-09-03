#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "string.h"
#include "../List/list.h"

/**
 * Function used determine whether an index is in bounds
 *
 * @param pString pointer to the string
 * @param index position in the string
 *
 * @return true or false
 */

bool isIndexInBoundsString(char *pString, int index);






















bool isIndexInBoundsString(char *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : Pointer to string is NULL | isIndexInBoundsString \n");
        return -1;
    }

    int length = strlen(pString);
    if (index < 0 || index >= length)
    {
        return false;
    }
    return true;
}
