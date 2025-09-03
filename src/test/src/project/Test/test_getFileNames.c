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

int updateFiles(List *splitFiles, char *token);


/**
 * Function used to get the name of a function
 *
 * @param func the function
 *
 * @return Success: the name
 */

char *getFunctionName(char *func);


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

    char *preSet = stringCreate(NULL);
    char *token = stringCreate(NULL);

    List *funcNames = listCreate(sizeof(char *), &stringCopy, NULL);

    int type;
    int funcCounter;
    int lastC;
    int c;

    while ((c = getc(srcFile)) != EOF)
    {
        if (strlen(token) == 0 && isspace(c) == false)
        {
            if (c == '#')
            {
                type = MACRO;
            }
            else if (c == '/')
            {
                token = stringAdd(token, c);
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
            token = stringAdd(token, c);
        }
        else if (strlen(token) == 0 && isspace(c))
        {
            ;
        }
        else if (type == MACRO)
        {
            if (c == '\n')
            {
                token = stringClear(token);
            }
        }
        else if (type == COMMENT)
        {

            if (c == '\n')
            {
                token = stringClear(token);
            }
        }
        else if (type == MULTI_COMMENT)
        {

            if (c == '*')
            {
                c = getc(srcFile);

                if (c == '/')
                {
                    token = stringClear(token);
                    continue;
                }
            }
        }
        else if (type == OTHER)
        {
            token = stringAdd(token, c);

            if (c == ';')
            {
                token = stringClear(token);
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
            token = stringAdd(token, c);

            if (c == '{')
            {
                funcCounter++;
            }
            else if (c == '}')
            {
                funcCounter--;

                if (funcCounter < 0)
                {
                    char *tempName = getFunctionName(token);

                    listAdd(funcNames, tempName);
                    free(tempName);

                    token = stringClear(token);
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
                token = stringClear(token);
            }
        }
    }
    fclose(srcFile);

    free(preSet);
    free(token);

    char *separator = stringCreate("_");
    char *pathSeparator = stringCreate("/");
    char *name = utilGetName(entryGetName(src));
    char *cEx = stringCreate(".c");
    char *main = stringCreate("main");

    List *fileNames = listCreate(sizeof(char *), &stringCopy, NULL);

    for (int i = 0; i < listLength(funcNames); i++)
    {
        char *funcName = listGet(funcNames, i);

        if (strcmp(funcName, main) == 0)
        {
            continue;
        }

        char *filePath = stringCreate(NULL);
        filePath = stringCat(filePath, name);
        filePath = stringCat(filePath, separator);
        filePath = stringCat(filePath, funcName);
        filePath = stringCat(filePath, cEx);

        listAdd(fileNames, filePath);

        free(funcName);
        free(filePath);
    }

    free(separator);
    free(main);
    free(cEx);
    free(pathSeparator);
    free(name);
    listFree(funcNames);

    return fileNames;
}
