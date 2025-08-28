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


























char *stringToArr(String *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringToArr \n");
        return NULL;
    }

    int length = stringLength(pString);
    char *arr = (char *)malloc(sizeof(char) * (length + 1));

    if (arr == NULL)
    {
        printf("[ERROR] : Memory allocation failed | stringToArr \n");
        return NULL;
    }

    for (int i = 0; i < length; i++)
    {
        char temp = stringGet(pString, i);

        if (temp == -1)
        {
            printf("[ERROR] : Function stringGet failed | stringToArr \n");
            return NULL;
        }
        arr[i] = temp;
    }
    arr[length] = '\0';

    return arr;
}
