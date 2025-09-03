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


char *stringCreate(char *pString)
{
    char *newString;

    if (pString != NULL)
    {
        newString = malloc(sizeof(char) * strlen(pString) + 1);
        strcpy(newString, pString);
    }
    else{
        newString = malloc(sizeof(char));
        newString[0] = '\0';
    }

    return newString;
}
