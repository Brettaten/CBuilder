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
















char *stringSub(char *pString, int beginning, int end)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringSub \n");
        return NULL;
    }

    if (!isIndexInBoundsString(pString, beginning) || !isIndexInBoundsString(pString, end))
    {
        printf("[INFO] : Index out of bounds | stringSub \n");
        return NULL;
    }

    if (end < beginning)
    {
        printf("[INFO] : Index end can not be bigger than index beginning | stringSub \n");
        return NULL;
    }

    int length = end - beginning + 1;

    char *stringNew = (char *)malloc((sizeof(char) * length) + 1);

    for (int i = beginning, j = 0; i < beginning + length; i++, j++)
    {
        stringNew[j] = pString[i];
    }

    stringNew[length] = '\0';

    return stringNew;
}
