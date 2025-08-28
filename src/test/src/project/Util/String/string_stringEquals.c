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
























bool stringEquals(String *pString1, String *pString2)
{
    if (pString1 == NULL || pString2 == NULL)
    {
        printf("[ERROR] : String is null | stringEquals \n");
        return false;
    }

    int length1 = stringLength(pString1);
    int length2 = stringLength(pString2);
    if (length1 != length2)
    {
        return false;
    }

    for (int i = 0; i < length1; i++)
    {
        char temp1 = stringGet(pString1, i);
        char temp2 = stringGet(pString2, i);

        if (temp1 == -1 || temp2 == -1)
        {
            printf("[ERROR] : Function stringGet failed | stringEquals \n");
            return false;
        }

        if (temp1 != temp2)
        {
            return false;
        }
    }
    return true;
}
