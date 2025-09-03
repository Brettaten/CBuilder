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




char *stringAdd(char *pString, char value)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringAdd \n");
        return NULL;
    }

    int len = strlen(pString);

    char *newString = (char *)malloc(sizeof(char) * (len + 2));

    if (newString == NULL)
    {
        printf("[ERROR] : memory reallocation failed | stringAdd \n");
        return NULL;
    }

    strcpy(newString, pString);

    newString[len] = value;
    newString[len + 1] = '\0';

    free(pString);

    return newString;
}
