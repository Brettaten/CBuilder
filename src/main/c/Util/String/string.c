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

char *stringCreate(char *pString)
{
    char *newString;

    if (pString != NULL)
    {
        newString = malloc(sizeof(char) * strlen(pString) + 1);
        strcpy(newString, pString);
    }
    else{
        newString = malloc(sizeof(char));
        newString[0] = '\0';
    }

    return newString;
}

char *stringAdd(char *pString, char value)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringAdd \n");
        return NULL;
    }

    int len = strlen(pString);

    char *newString = (char *)malloc(sizeof(char) * (len + 2));

    if (newString == NULL)
    {
        printf("[ERROR] : memory reallocation failed | stringAdd \n");
        return NULL;
    }

    strcpy(newString, pString);

    newString[len] = value;
    newString[len + 1] = '\0';

    free(pString);

    return newString;
}

char *stringAddIndex(char *pString, char value, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : string is null | stringAddIndex \n");
        return NULL;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringAddIndex \n");
        return NULL;
    }

    char temp = pString[strlen(pString) - 1];

    pString = stringAdd(pString, temp);

    if (pString == NULL)
    {
        printf("[ERROR] : Function stringAdd failed | stringAddIndex \n");
        return NULL;
    }

    for (int i = strlen(pString) - 2; i > index; i--)
    {
        int st2 = stringSwap(pString, i - 1, i);

        if (st2 == -1)
        {
            printf("[ERROR] : Function stringSwap failed | stringAddIndex \n");
            free(pString);
            return NULL;
        }
    }

    pString[index] = value;

    return pString;
}

int stringSwap(char *pString, int index1, int index2)
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

    char temp = pString[index1];

    pString[index1] = pString[index2];
    pString[index2] = temp;

    return 0;
}

void *stringCopy(void *pString)
{

    char *cp = (char *)pString;
    if (cp == NULL)
    {
        printf("[ERROR] : String is null | stringCopy \n");
        return NULL;
    }

    char *stringCpy = stringCreate(cp);

    if (stringCpy == NULL)
    {
        printf("[ERROR] : Function stringCreate failed | stringCopy \n");
        return NULL;
    }

    return stringCpy;
}

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

char *stringClear(char *pString)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringClear \n");
        return NULL;
    }

    char *newString = (char *)malloc(sizeof(char));

    strcpy(newString, "");
    free(pString);

    return newString;
}

char *stringSub(char *pString, int beginning, int end)
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

    int length = end - beginning + 1;

    char *stringNew = (char *)malloc((sizeof(char) * length) + 1);

    for (int i = beginning, j = 0; i < beginning + length; i++, j++)
    {
        stringNew[j] = pString[i];
    }

    stringNew[length] = '\0';

    return stringNew;
}

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

char *stringRemove(char *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : String is null | stringRemove \n");
        return NULL;
    }

    if (!isIndexInBoundsString(pString, index))
    {
        printf("[WARN] : Index out of bounds | stringRemove \n");
        return NULL;
    }

    char *newString = (char *)malloc(sizeof(char) * (strlen(pString)));

    for (int i = 0, j = 0; i < strlen(pString); i++, j++)
    {
        if (i == index)
        {
            j--;
        }
        else
        {
            newString[j] = pString[i];
        }
    }

    newString[strlen(pString) - 1] = '\0';
    free(pString);
  
    return newString;
}

bool isIndexInBoundsString(char *pString, int index)
{
    if (pString == NULL)
    {
        printf("[ERROR] : Pointer to string is NULL | isIndexInBoundsString \n");
        return -1;
    }

    int length = strlen(pString);
    if (index < 0 || index >= length)
    {
        return false;
    }
    return true;
}
