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












char *stringCat(char *pStringDest, char *pStringSrc){
    if (pStringDest == NULL)
    {
        printf("[ERROR] : String is null | stringCat \n");
        return NULL;
    }

    if (pStringSrc == NULL)
    {
        printf("[ERROR] : String is null | stringCat \n");
        return NULL;
    }

    int lengthSrc = strlen(pStringSrc);
    int lengthDest = strlen(pStringDest);

    char *stringNew = (char *) malloc(sizeof(char) * (lengthSrc + lengthDest + 2));
    strcpy(stringNew, pStringDest);
    strcat(stringNew, pStringSrc);

    return stringNew;
}
