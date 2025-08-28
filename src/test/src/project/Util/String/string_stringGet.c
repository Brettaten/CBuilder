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








char stringGet(String *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringGet \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringGet \n");
        return -1;
    }

    char *c = (char *)listGet(pString->list, index);

    if (c == NULL)
    {
        printf("[ERROR] : Function listGet failed : stringGet \n");
        return -1;
    }

    char chr = *c;

    free(c);

    return chr;
}
