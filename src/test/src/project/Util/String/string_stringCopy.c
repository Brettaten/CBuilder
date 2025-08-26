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















void *stringCopy(void *pString)
{

    String *cp = (String *)pString;
    if (cp == NULL)
    {
        printf("[ERROR] : String is null | stringCopy \n");
        return NULL;
    }

    String *stringCpy = stringCreate(NULL);

    if (stringCpy == NULL)
    {
        printf("[ERROR] : Function stringCreate failed | stringCopy \n");
        return NULL;
    }

    stringCpy->list = listCopy(cp->list);

    if (stringCpy->list == NULL)
    {
        printf("[ERROR] : Function listCopy failed | stringCopy \n");
        return NULL;
    }

    return stringCpy;
}