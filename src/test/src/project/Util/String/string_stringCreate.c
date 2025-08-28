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


String *stringCreate(char *string)
{
    List *list = listCreate(sizeof(char), NULL, NULL);

    if (list == NULL)
    {
        printf("[ERROR] : Memory allocation failed | stringCreate \n");
        return NULL;
    }

    String *pString = (String *)malloc(sizeof(String));

    if (pString == NULL)
    {
        printf("[ERROR] : Memory allocation failed | stringCreate \n");
        return NULL;
    }

    pString->list = list;

    if (string != NULL)
    {

        int length = strlen(string);
        for (int i = 0; i < length; i++)
        {
            int st1 = stringAdd(pString, string[i]);

            if (st1 == -1)
            {
                printf("[ERROR] : function stringAdd failed | stringCreate \n");
            }
        }
    }

    return pString;
}
