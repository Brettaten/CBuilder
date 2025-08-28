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














int stringCat(String *pStringDest, String *pStringSrc)
{
    if (pStringDest == NULL)
    {
        printf("[ERROR] : String is null | stringCat \n");
        return -1;
    }

    if (pStringSrc == NULL)
    {
        printf("[ERROR] : String is null | stringCat \n");
        return -1;
    }

    int length = stringLength(pStringSrc);
    for (int i = 0; i < length; i++)
    {
        char temp = stringGet(pStringSrc, i);

        if (temp == -1)
        {
            printf("[ERROR] : Function stringGet failed | \n");
            return -1;
        }

        int st1 = stringAdd(pStringDest, temp);

        if (st1 == -1)
        {
            printf("[ERROR] : Function stringAdd failed | \n");
            return -1;
        }
    }

    return 0;
}
