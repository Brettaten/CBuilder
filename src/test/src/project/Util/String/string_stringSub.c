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




















String *stringSub(String *pString, int beginning, int end)
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

    String *stringNew = stringCreate(NULL);

    if (stringNew == NULL)
    {
        printf("[ERROR] : Function stringCreate failed | stringSub \n");
        return NULL;
    }

    int length = end - beginning + 1;

    for (int i = beginning; i < beginning + length; i++)
    {
        char temp = stringGet(pString, i);

        if (temp == -1)
        {
            printf("[ERROR] : Function stringGet failed | stringSub \n");
            return NULL;
        }

        int st1 = stringAdd(stringNew, temp);

        if (st1 == -1)
        {
            printf("[ERROR] : Function stringAdd failed | stringSub \n");
            return NULL;
        }
    }

    return stringNew;
}
