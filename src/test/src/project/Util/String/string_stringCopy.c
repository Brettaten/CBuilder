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










void *stringCopy(void *pString)
{

    char *cp = (char *)pString;
    if (cp == NULL)
    {
        printf("[ERROR] : String is null | stringCopy \n");
        return NULL;
    }

    char *stringCpy = stringCreate(cp);

    if (stringCpy == NULL)
    {
        printf("[ERROR] : Function stringCreate failed | stringCopy \n");
        return NULL;
    }

    return stringCpy;
}
