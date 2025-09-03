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




















char *stringRemove(char *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringRemove \n");
        return NULL;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringRemove \n");
        return NULL;
    }

    char *newString = (char *)malloc(sizeof(char) * (strlen(pString)));

    for (int i = 0, j = 0; i < strlen(pString); i++, j++)
    {
        if (i == index)
        {
            j--;
        }
        else
        {
            newString[j] = pString[i];
        }
    }

    newString[strlen(pString) - 1] = '\0';
    free(pString);
  
    return newString;
}
