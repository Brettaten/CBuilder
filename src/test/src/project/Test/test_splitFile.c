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


void splitFile(Entry *src, Directory *dest)
{
    if (src == NULL)
    {
        printf("[ERROR] : the src entry can not be null | splitFile \n");
        return;
    }

    if (dest == NULL)
    {
        printf("[ERROR] : the dest directory can not be null | splitFile \n");
        return;
    }

    FILE *srcFile = fopen(entryGetPath(src), "r");

    if (srcFile == NULL)
    {
        printf("[ERROR] : src file could not be opened | splitFile \n");
        return;
    }

    char *preSet = stringCreate(NULL);
    char *token = stringCreate(NULL);
    char *currToken = stringCreate(NULL);

    char *structStr = stringCreate("struct");

    List *splitFiles = listCreate(sizeof(char *), &stringCopy, NULL);
    List *funcNames = listCreate(sizeof(char *), &stringCopy, NULL);

    int type = OTHER;
    int funcCounter;
    int lastC;
    int c;

    while ((c = getc(srcFile)) != EOF)
    {
        if (type == OTHER)
        {
            if (strlen(currToken) == 0 && strlen(token) == 0 && !isspace(c))
            {
                currToken = stringClear(currToken);
                currToken = stringAdd(currToken, c);
                if (c == '#')
                {
                    type = MACRO;
                    token = stringCat(token, currToken);
                }
                else if (c == '/')
                {
                    c = getc(srcFile);
                    currToken = stringAdd(currToken, c);

                    if (c == '/')
                    {
                        type = COMMENT;
                        token = stringCat(token, currToken);
                    }
                    else if (c == '*')
                    {
                        type = MULTI_COMMENT;
                        token = stringCat(token, currToken);
                    }
                }
                lastC = c;
            }
            else if (strlen(currToken) == 0 && isspace(c))
            {
                preSet = stringAdd(preSet, c);
            }
            else
            {
                if (!isspace(c))
                {
                    if (c == ';')
                    {
                        currToken = stringAdd(currToken, c);
                        if (lastC == ')')
                        {
                            token = stringCat(token, currToken);
                            type = OTHER;
                            token = stringAdd(token, '\n');
                            updateFiles(splitFiles, token);
                            preSet = stringCat(preSet, token);
                            token = stringClear(token);
                            currToken = stringClear(currToken);
                        }
                        else
                        {
                            token = stringCat(token, currToken);
                            type = OTHER;
                            token = stringAdd(token, '\n');
                            updateFiles(splitFiles, token);
                            preSet = stringCat(preSet, token);
                            token = stringClear(token);
                            currToken = stringClear(currToken);
                        }
                    }
                    else if (c == '{' && lastC == ')')
                    {
                        currToken = stringAdd(currToken, c);

                        token = stringCat(token, currToken);
                        type = FUNCTION;
                        funcCounter = 0;
                    }
                    else
                    {
                        currToken = stringAdd(currToken, c);
                        lastC = c;
                    }
                }
                if (isspace(c))
                {
                    if (strcmp(currToken, "struct") == 0)
                    {
                        type = STRUCT;
                        funcCounter = 0;
                        currToken = stringAdd(currToken, c);
                        token = stringCat(token, currToken);
                    }
                    else if (strcmp(currToken, "union") == 0)
                    {
                        type = STRUCT;
                        funcCounter = 0;
                        currToken = stringAdd(currToken, c);
                        token = stringCat(token, currToken);
                    }
                    else if (strcmp(currToken, "enum") == 0)
                    {
                        type = STRUCT;
                        funcCounter = 0;
                        currToken = stringAdd(currToken, c);
                        token = stringCat(token, currToken);
                    }
                    else if (strcmp(currToken, "static") == 0)
                    {
                        currToken = stringClear(currToken);
                        token = stringAdd(token, c);
                    }
                    else
                    {
                        token = stringCat(token, currToken);
                        currToken = stringClear(currToken);
                        token = stringAdd(token, c);
                    }
                }
            }
        }
        else if (type == MACRO)
        {
            token = stringAdd(token, c);

            if (c == '\n')
            {
                updateFiles(splitFiles, token);
                preSet = stringCat(preSet, token);
                token = stringClear(token);
                currToken = stringClear(currToken);

                type = OTHER;
            }
        }
        else if (type == COMMENT)
        {
            token = stringAdd(token, c);

            if (c == '\n')
            {
                updateFiles(splitFiles, token);
                preSet = stringCat(preSet, token);
                token = stringClear(token);
                currToken = stringClear(currToken);

                type = OTHER;
            }
        }
        else if (type == MULTI_COMMENT)
        {
            token = stringAdd(token, c);

            if (c == '*')
            {
                c = getc(srcFile);

                if (c == '/')
                {
                    token = stringAdd(token, c);
                    token = stringAdd(token, '\n');
                    updateFiles(splitFiles, token);
                    preSet = stringCat(preSet, token);
                    token = stringClear(token);
                    currToken = stringClear(currToken);

                    type = OTHER;
                    continue;
                }
                token = stringAdd(token, c);
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
                    token = stringAdd(token, '\n');
                    char *tempFile = stringCreate(preSet);
                    tempFile = stringCat(tempFile, token);

                    char *tempName = getFunctionName(token);

                    int counter = -1;

                    for (int i = 0; i < listLength(funcNames); i++)
                    {
                        char *tempFuncName = listGet(funcNames, i);

                        if (strcmp(tempFuncName, tempName) == 0)
                        {
                            counter = i;
                        }

                        free(tempFuncName);
                    }

                    if (counter != -1)
                    {
                        char *duplicateFile = listGet(splitFiles, counter);
                        duplicateFile = stringCat(duplicateFile, token);

                        listSet(splitFiles, duplicateFile, counter);

                        free(duplicateFile);
                    }
                    else
                    {
                        listAdd(funcNames, tempName);
                        free(tempName);

                        listAdd(splitFiles, tempFile);
                    }

                    token = stringClear(token);
                    currToken = stringClear(currToken);

                    free(tempFile);

                    type = OTHER;
                }
            }
        }
        else if (type == STRUCT)
        {
            token = stringAdd(token, c);
            if (c == '}')
            {
                funcCounter = -1;
            }
            else if (c == ';' && funcCounter == -1)
            {
                token = stringAdd(token, '\n');
                updateFiles(splitFiles, token);
                preSet = stringCat(preSet, token);
                token = stringClear(token);
                currToken = stringClear(currToken);

                type = OTHER;
            }
        }
    }
    fclose(srcFile);

    free(token);
    free(currToken);

    char *name = utilGetName(entryGetName(src));

    for (int i = 0; i < listLength(splitFiles); i++)
    {
        char *func = listGet(splitFiles, i);

        char *funcName = listGet(funcNames, i);

        if (strcmp(funcName, "main") == 0)
        {
            continue;
        }

        char *filePath = stringCreate(directoryGetPath(dest));
        filePath = stringCat(filePath, "/");
        filePath = stringCat(filePath, name);
        filePath = stringCat(filePath, "_");
        filePath = stringCat(filePath, funcName);
        filePath = stringCat(filePath, ".c");

        FILE *tempFile = fopen(filePath, "w");

        if (tempFile == NULL)
        {
            printf("[ERROR] : Could not open file | splitFile \n");
            return;
        }

        int c;

        for (int j = 0; j < strlen(func); j++)
        {
            c = func[j];

            putc(c, tempFile);
        }

        free(funcName);
        free(filePath);
        free(func);
        fclose(tempFile);
    }

    if (listLength(funcNames) == 0)
    {

        char *filePath = stringCreate(directoryGetPath(dest));
        filePath = stringCat(filePath, "/");
        filePath = stringCat(filePath, entryGetName(src));

        FILE *tempFile = fopen(filePath, "w");

        if (tempFile == NULL)
        {
            printf("[ERROR] : Could not open file | splitFile \n");
            return;
        }

        int c;

        for (int j = 0; j < strlen(preSet); j++)
        {
            c = preSet[j];

            putc(c, tempFile);
        }

        free(filePath);
        fclose(tempFile);
    }

    free(preSet);
    free(name);
    listFree(funcNames);
    listFree(splitFiles);
}
