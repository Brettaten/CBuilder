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

int stringAdd(String *pString, char value)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringAdd \n");
        return -1;
    }

    int st1 = listAdd(pString->list, &value);

    if (st1 == -1)
    {
        printf("[ERROR] : function listAdd failed | stringAdd");
        return -1;
    }

    return 0;
}

int stringAddIndex(String *pString, char value, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringAddIndex \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringAddIndex \n");
        return -1;
    }

    int st1 = listAddIndex(pString->list, &value, index);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listAddIndex failed | stringAddIndex \n");
        return -1;
    }

    return 0;
}

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

int stringSet(String *pString, char value, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringSet \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringSet \n");
        return -1;
    }

    int st1 = listSet(pString->list, &value, index);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listSet failed | stringSet \n");
        return -1;
    }

    return 0;
}

int stringSwap(String *pString, int index1, int index2)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringSwap \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index1) || !isIndexInBoundsString(pString, index2))
    {
        printf("[WARN] : Index out of bounds | stringSwap \n");
        return -1;
    }

    int st1 = listSwap(pString->list, index1, index2);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listSwap failed | stringSwap \n");
        return -1;
    }

    return 0;
}

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

int stringClear(String *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringClear \n");
        return -1;
    }

    int length = stringLength(pString);
    for (int i = length - 1; i >= 0; i--)
    {
        int st1 = stringRemove(pString, i);

        if (st1 == -1)
        {
            printf("[ERROR] : Function stringRemove failed | stringClear \n");
            return -1;
        }
    }

    return 0;
}

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

int stringRemove(String *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringRemove \n");
        return -1;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringRemove \n");
        return -1;
    }

    int st1 = listRemove(pString->list, index);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listRemove failed | stringRemove \n");
        return -1;
    }

    return 0;
}

int stringLength(String *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringLength \n");
        return -1;
    }

    return listLength(pString->list);
}

int stringContentSize(String *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringSize \n");
        return -1;
    }

    return listSize(pString->list);
}

int stringSize()
{
    return sizeof(String);
}

void stringFree(void *pString)
{
    String *cp = (String *)pString;

    listFree(cp->list);
    free(cp);
}

bool isIndexInBoundsString(String *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : Pointer to string is NULL | isIndexInBoundsString \n");
        return -1;
    }

    int length = stringLength(pString);
    if (index < 0 || index >= length)
    {
        return false;
    }
    return true;
}
