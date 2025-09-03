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














char *stringClear(char *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringClear \n");
        return NULL;
    }

    char *newString = (char *)malloc(sizeof(char));

    strcpy(newString, "");
    free(pString);

    return newString;
}
