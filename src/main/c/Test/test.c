#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "test.h"
#include "../Util/String/string.h"
#include "../Util/List/list.h"

enum TYPE
{
    MACRO,
    FUNCTION,
    COMMENT,
    MULTI_COMMENT,
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

    int type;
    int funcCounter;
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
                    updateFiles(splitFiles, token);
                    stringCat(preSet, token);
                    stringClear(token);
                }
                stringAdd(token, c);
            }
        }
        else if (type == OTHER)
        {
            stringAdd(token, c);

            if (c == ';')
            {
                updateFiles(splitFiles, token);
                stringCat(preSet, token);
                stringClear(token);
            }
            else if (c == '{')
            {
                type = FUNCTION;
                funcCounter = 0;
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
                    String *tempFile = stringCreate(stringToArr(preSet));
                    stringCat(tempFile, token);

                    stringClear(token);

                    listAdd(splitFiles, tempFile);

                    stringFree(tempFile);
                }
            }
        }
    }
    fclose(srcFile);

    stringFree(preSet);
    stringFree(token);

    for(int i = 0; i < listLength(splitFiles); i++){
        FILE *tempFile = fopen()
    }
}

int updateFiles(List *splitFiles, String *token)
{
    if(splitFiles == NULL){
        printf("[ERROR] : list can not be null | updateFiles \n");
        return -1;
    }

    if(token == NULL){
        printf("[ERROR] : string can not be null | updateFiles \n");
        return -1;
    }

    for(int i = 0; i < listLength(splitFiles); i++){
        String *temp = listGet(splitFiles, i);

        stringCat(temp, token);

        listSet(splitFiles, temp, i);

        stringFree(temp);
    }
    return 0;
}
