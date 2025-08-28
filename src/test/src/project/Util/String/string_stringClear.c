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


















int stringClear(String *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringClear \n");
        return -1;
    }

    int length = stringLength(pString);
    for (int i = length - 1; i >= 0; i--)
    {
        int st1 = stringRemove(pString, i);

        if (st1 == -1)
        {
            printf("[ERROR] : Function stringRemove failed | stringClear \n");
            return -1;
        }
    }

    return 0;
}
