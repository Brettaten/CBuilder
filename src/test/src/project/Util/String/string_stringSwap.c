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








int stringSwap(char *pString, int index1, int index2)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringSwap \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index1) || !isIndexInBoundsString(pString, index2))
    {
        printf("[WARN] : Index out of bounds | stringSwap \n");
        return -1;
    }

    char temp = pString[index1];

    pString[index1] = pString[index2];
    pString[index2] = temp;

    return 0;
}
