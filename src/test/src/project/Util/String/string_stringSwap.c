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












int stringSwap(String *pString, int index1, int index2)
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

    int st1 = listSwap(pString->list, index1, index2);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listSwap failed | stringSwap \n");
        return -1;
    }

    return 0;
}
