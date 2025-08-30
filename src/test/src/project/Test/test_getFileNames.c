#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "test.h"
#include "../Util/String/string.h"
#include "../Util/List/list.h"
#include "../Util/Stack/stack.h"
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


/**
 * Function used to concatenate two lists that contain strings
 *
 * @param dest the destination list
 * @param src the source list
 */

void utilConcatenateLists(List *dest, List *src);




List *getFileNames(Entry *src)
{
    if (src == NULL)
    {
        printf("[ERROR] : the src entry can not be null | splitFile \n");
        return NULL;
    }

    FILE *srcFile = fopen(entryGetPath(src), "r");

    if (srcFile == NULL)
    {
        printf("[ERROR] : src file could not be opened | splitFile \n");
        return NULL;
    }

    String *preSet = stringCreate(NULL);
    String *token = stringCreate(NULL);

    List *funcNames = listCreate(stringSize(), &stringCopy, &stringFree);

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
            ;
        }
        else if (type == MACRO)
        {
            if (c == '\n')
            {
                stringClear(token);
            }
        }
        else if (type == COMMENT)
        {

            if (c == '\n')
            {
                stringClear(token);
            }
        }
        else if (type == MULTI_COMMENT)
        {

            if (c == '*')
            {
                c = getc(srcFile);

                if (c == '/')
                {
                    stringClear(token);
                    continue;
                }
            }
        }
        else if (type == OTHER)
        {
            stringAdd(token, c);

            if (c == ';')
            {
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
                    String *tempName = getFunctionName(token);

                    listAdd(funcNames, tempName);
                    stringFree(tempName);

                    stringClear(token);
                }
            }
        }
        else if (type == STRUCT)
        {
            if (c == '}')
            {
                funcCounter = -1;
            }
            else if (c == ';' && funcCounter == -1)
            {
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

    List *fileNames = listCreate(stringSize(), &stringCopy, &stringFree);

    for (int i = 0; i < listLength(funcNames); i++)
    {
        String *funcName = listGet(funcNames, i);

        if (stringEquals(funcName, main))
        {
            continue;
        }

        String *filePath = stringCreate(NULL);
        stringCat(filePath, name);
        stringCat(filePath, separator);
        stringCat(filePath, funcName);
        stringCat(filePath, cEx);

        listAdd(fileNames, filePath);

        stringFree(funcName);
        stringFree(filePath);
    }

    stringFree(separator);
    stringFree(main);
    stringFree(cEx);
    stringFree(pathSeparator);
    stringFree(name);
    listFree(funcNames);

    return fileNames;
}
