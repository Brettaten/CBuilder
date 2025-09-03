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






char *stringAddIndex(char *pString, char value, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringAddIndex \n");
        return NULL;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringAddIndex \n");
        return NULL;
    }

    char temp = pString[strlen(pString) - 1];

    pString = stringAdd(pString, temp);

    if (pString == NULL)
    {
        printf("[ERROR] : Function stringAdd failed | stringAddIndex \n");
        return NULL;
    }

    for (int i = strlen(pString) - 2; i > index; i--)
    {
        int st2 = stringSwap(pString, i - 1, i);

        if (st2 == -1)
        {
            printf("[ERROR] : Function stringSwap failed | stringAddIndex \n");
            free(pString);
            return NULL;
        }
    }

    pString[index] = value;

    return pString;
}
