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


















char *stringReplace(char *pString, char *pStringDest, char *pStringSrc)
{
    if (pString == NULL || pStringDest == NULL || pStringSrc == NULL)
    {
        printf("[ERROR] : String is null | stringReplace \n");
        return NULL;
    }

    int lengthDest = strlen(pStringDest);
    int lengthSrc = strlen(pStringSrc);
    int length = strlen(pString);
    if (lengthDest > length)
    {
        printf("[INFO] : StringDest can not be longer than the main string | stringReplace \n");
        return NULL;
    }

    int len = 0;

    for (int i = 0; i < length; i++)
    {
        int end = i + lengthDest - 1;

        if (isIndexInBoundsString(pString, end))
        {
            char *temp = stringSub(pString, i, end);

            if (strcmp(pStringDest, temp) == 0)
            {
                len += lengthSrc;
                i += lengthDest - 1;
                free(temp);
                continue;
            }
            free(temp);
        }
        len++;
    }

    len++;

    char *newString = (char *)malloc(sizeof(char) * len);

    for (int i = 0, j = 0; i < len; i++, j++)
    {
        int end = j + lengthDest - 1;

        if (!isIndexInBoundsString(pString, end))
        {
            newString[i] = pString[j];
        }
        else
        {
            char *temp = stringSub(pString, j, end);

            if (strcmp(pStringDest, temp) == 0)
            {
                for (int k = 0; k < lengthSrc; k++)
                {
                    newString[i] = pStringSrc[k];
                    i++;
                }
                i--;
                j += lengthDest - 1;
            }
            else
            {
                newString[i] = pString[j];
            }
            free(temp);
        }
    }

    free(pString);

    return newString;
}
