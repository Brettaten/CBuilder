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






















int stringReplace(String *pString, String *pStringDest, String *pStringSrc)
{
    if (pString == NULL || pStringDest == NULL || pStringSrc == NULL)
    {
        printf("[ERROR] : String is null | stringReplace \n");
        return -1;
    }

    int lengthDest = stringLength(pStringDest);
    int lengthSrc = stringLength(pStringSrc);
    int length = stringLength(pString);
    if (lengthDest > length)
    {
        printf("[INFO] : StringDest can not be longer than the main string | stringReplace \n");
        return -1;
    }

    bool isMatch = false;
    int matchCounter = 0;

    int i = -1;

    while (true)
    {
        i++;
        lengthDest = stringLength(pStringDest);
        lengthSrc = stringLength(pStringSrc);
        if (isMatch)
        {
            if (matchCounter < lengthDest && matchCounter < lengthSrc)
            {
                char temp = stringGet(pStringSrc, matchCounter);

                if (temp == -1)
                {
                    printf("[ERROR] : Function stringGet failed | stringReplace \n");
                    return -1;
                }
                int st1;
                if (isIndexInBoundsString(pString, i))
                {
                    st1 = stringSet(pString, temp, i);
                }
                else
                {
                    st1 = stringAdd(pString, temp);
                }

                if (st1 == -1)
                {
                    printf("[ERROR] : Function stringSet failed | stringReplace \n");
                    return -1;
                }

                matchCounter++;
            }
            else if (matchCounter < lengthDest)
            {
                int st2 = stringRemove(pString, i);

                if (st2 == -1)
                {
                    printf("[ERROR] : Function stringRemove failed | stringReplace \n");
                    return -1;
                }

                i--;
                matchCounter++;
            }

            else if (matchCounter < lengthSrc)
            {
                char temp = stringGet(pStringSrc, matchCounter);

                if (temp == -1)
                {
                    printf("[ERROR] : Function stringGet failed | stringReplace \n");
                    return -1;
                }

                int st3;
                if (isIndexInBoundsString(pString, i))
                {
                    st3 = stringAddIndex(pString, temp, i);
                }
                else
                {
                    st3 = stringAdd(pString, temp);
                }

                if (st3 == -1)
                {
                    printf("[ERROR] : Function stringSet failed | stringReplace \n");
                    return -1;
                }

                matchCounter++;
            }
            else
            {
                isMatch = false;
                matchCounter = 0;
                i--;
            }
        }
        else
        {
            int end = i + lengthDest - 1;

            if (!isIndexInBoundsString(pString, end))
            {
                return 0;
            }
            else
            {
                String *sub = stringSub(pString, i, end);

                if (sub == NULL)
                {
                    printf("[ERROR] : Function stringSub failed | stringReplace \n");
                    return -1;
                }

                if (stringEquals(pStringDest, sub))
                {
                    isMatch = true;
                    i--;
                }

                stringFree(sub);
            }
        }
    }
    return 0;
}
