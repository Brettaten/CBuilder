#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "test.h"
#include "../Util/String/string.h"
#include "../Util/List/list.h"
#include "../Main/main.h"

enum TYPE
{
    MACRO,
    FUNCTION,
    COMMENT,
    MULTI_COMMENT,
    STRUCT,
    OTHER
};

/**
 * Function used to update the splited files by adding additional information
 *
 * @param splitFiles the list with the files
 * @param token the addition
 *
 * @return Success: 0 | Failure: -1
 */
int updateFiles(List *splitFiles, String *token);

/**
 * Function used to get the name of a function
 *
 * @param func the function
 *
 * @return Success: the name
 */
String *getFunctionName(String *func);

int splitFile(Entry *src, Directory *dest)
{
    if (src == NULL)
    {
        printf("[ERROR] : the src entry can not be null | splitFile \n");
        return -1;
    }

    if (dest == NULL)
    {
        printf("[ERROR] : the dest directory can not be null | splitFile \n");
        return -1;
    }

    FILE *srcFile = fopen(entryGetPath(src), "r");

    if (srcFile == NULL)
    {
        printf("[ERROR] : src file could not be opened | splitFile \n");
        return -1;
    }

    String *preSet = stringCreate(NULL);
    String *token = stringCreate(NULL);

    List *splitFiles = listCreate(stringSize(), &stringCopy, &stringFree);
    List *fileNames = listCreate(stringSize(), &stringCopy, &stringFree);

    int type;
    int funcCounter;
    int lastC;
    int c;

    while ((c = getc(srcFile)) != EOF)
    {
        if (stringLength(token) == 0 && isspace(c) == false)
        {
            if (c == '#')
            {
                type = MACRO;
            }
            else if (c == '/')
            {
                stringAdd(token, c);
                c = getc(srcFile);

                if (c == '/')
                {
                    type = COMMENT;
                }
                else if (c == '*')
                {
                    type = MULTI_COMMENT;
                }
            }
            else
            {
                type = OTHER;
            }
            stringAdd(token, c);
        }
        else if (stringLength(token) == 0 && isspace(c))
        {
            stringAdd(preSet, c);
        }
        else if (type == MACRO)
        {
            stringAdd(token, c);

            if (c == '\n')
            {
                updateFiles(splitFiles, token);
                stringCat(preSet, token);
                stringClear(token);
            }
        }
        else if (type == COMMENT)
        {
            stringAdd(token, c);

            if (c == '\n')
            {
                updateFiles(splitFiles, token);
                stringCat(preSet, token);
                stringClear(token);
            }
        }
        else if (type == MULTI_COMMENT)
        {
            stringAdd(token, c);

            if (c == '*')
            {
                c = getc(srcFile);

                if (c == '/')
                {
                    stringAdd(token, c);
                    stringAdd(token, '\n');
                    updateFiles(splitFiles, token);
                    stringCat(preSet, token);
                    stringClear(token);
                    continue;
                }
                stringAdd(token, c);
            }
        }
        else if (type == OTHER)
        {
            stringAdd(token, c);

            if (c == ';')
            {
                stringAdd(token, '\n');
                updateFiles(splitFiles, token);
                stringCat(preSet, token);
                stringClear(token);
            }
            else if (c == '{')
            {
                if (lastC == ')')
                {
                    type = FUNCTION;
                    funcCounter = 0;
                }
                else
                {
                    funcCounter = 0;
                    type = STRUCT;
                }
            }

            if (!isspace(c))
            {
                lastC = c;
            }
        }
        else if (type == FUNCTION)
        {
            stringAdd(token, c);

            if (c == '{')
            {
                funcCounter++;
            }
            else if (c == '}')
            {
                funcCounter--;

                if (funcCounter < 0)
                {
                    stringAdd(token, '\n');
                    String *tempFile = stringCreate(stringToArr(preSet));
                    stringCat(tempFile, token);

                    String *tempName = getFunctionName(token);

                    listAdd(fileNames, tempName);
                    stringFree(tempName);

                    stringClear(token);

                    listAdd(splitFiles, tempFile);

                    stringFree(tempFile);
                }
            }
        }
        else if (type == STRUCT)
        {
            stringAdd(token, c);
            if (c == '}')
            {
                funcCounter = -1;
            }
            else if (c == ';' && funcCounter == -1)
            {
                stringAdd(token, '\n');
                updateFiles(splitFiles, token);
                stringCat(preSet, token);
                stringClear(token);
            }
        }
    }
    fclose(srcFile);

    stringFree(preSet);
    stringFree(token);

    String *separator = stringCreate("_");
    String *pathSeparator = stringCreate("/");
    String *name = utilGetName(entryGetName(src));
    String *cEx = stringCreate(".c");
    String *main = stringCreate("main");

    for (int i = 0; i < listLength(splitFiles); i++)
    {
        String *func = listGet(splitFiles, i);

        String *funcName = listGet(fileNames, i);

        if (stringEquals(funcName, main))
        {
            continue;
        }

        String *filePath = stringCreate(directoryGetPath(dest));
        stringCat(filePath, pathSeparator);
        stringCat(filePath, name);
        stringCat(filePath, separator);
        stringCat(filePath, funcName);
        stringCat(filePath, cEx);

        FILE *tempFile = fopen(stringToArr(filePath), "w");

        if (tempFile == NULL)
        {
            printf("[ERROR] : Could not open file | splitFile \n");
            return -1;
        }

        int c;

        for (int j = 0; j < stringLength(func); j++)
        {
            c = stringGet(func, j);

            putc(c, tempFile);
        }

        stringFree(funcName);
        stringFree(filePath);
        stringFree(func);
        fclose(tempFile);
    }

    stringFree(separator);
    stringFree(main);
    stringFree(cEx);
    stringFree(pathSeparator);
    stringFree(name);
    listFree(fileNames);
    listFree(splitFiles);

    return 0;
}

int updateFiles(List *splitFiles, String *token)
{
    if (splitFiles == NULL)
    {
        printf("[ERROR] : list can not be null | updateFiles \n");
        return -1;
    }

    if (token == NULL)
    {
        printf("[ERROR] : string can not be null | updateFiles \n");
        return -1;
    }

    for (int i = 0; i < listLength(splitFiles); i++)
    {
        String *temp = listGet(splitFiles, i);

        stringCat(temp, token);

        listSet(splitFiles, temp, i);

        stringFree(temp);
    }
    return 0;
}

String *getFunctionName(String *func)
{
    String *token = stringCreate(NULL);
    bool isName = false;
    int c;

    for (int i = 0; i < stringLength(func); i++)
    {
        c = stringGet(func, i);

        if (isName)
        {
            if (c == '*' && stringLength(token) == 0)
            {
                continue;
            }
            else if (isspace(c) || c == '(')
            {
                break;
            }
            else
            {
                stringAdd(token, c);
            }
        }
        else
        {
            if (isspace(c))
            {
                if (stringLength(token) != 0)
                {
                    stringClear(token);
                    isName = true;
                }
            }
            else
            {
                stringAdd(token, c);
            }
        }
    }

    return token;

    return 0;
}
