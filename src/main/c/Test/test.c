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

    if (listLength(funcNames) == 0)
    {

        char *filePath = stringCreate(entryGetName(src));

        listAdd(fileNames, filePath);

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

int updateFiles(List *splitFiles, char *token)
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
        char *temp = listGet(splitFiles, i);

        temp = stringCat(temp, token);

        listSet(splitFiles, temp, i);

        free(temp);
    }
    return 0;
}

char *getFunctionName(char *func)
{
    char *token = stringCreate(NULL);
    bool isName = false;
    int c;

    for (int i = 0; i < strlen(func); i++)
    {
        c = func[i];

        if (isName)
        {
            if (c == '*' && strlen(token) == 0)
            {
                continue;
            }
            else if (isspace(c) || c == '(')
            {
                break;
            }
            else
            {
                token = stringAdd(token, c);
            }
        }
        else
        {
            if (isspace(c))
            {
                if (strlen(token) != 0 && strcmp(token, "static") != 0 && strcmp(token, "extern") != 0 && strcmp(token, "inline") != 0 && strcmp(token, "_Noreturn") != 0)
                {
                    token = stringClear(token);
                    isName = true;
                }
                else if (strcmp(token, "static") == 0 || strcmp(token, "extern") == 0 || strcmp(token, "inline") == 0 || strcmp(token, "_Noreturn") == 0)
                {
                    token = stringClear(token);
                }
            }
            else
            {
                token = stringAdd(token, c);
            }
        }
    }

    return token;
}

void copyProject(char *destPath, char *srcPath)
{
    Directory *srcDir = directoryGet(srcPath);
    Directory *destDir = directoryGet(destPath);

    if (srcDir == NULL || destDir == NULL)
    {
        printf("[ERROR] : Directory could not be found | copyProject \n");
        return;
    }

    Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
    Stack *stackDest = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

    if (stackSrc == NULL || stackDest == NULL)
    {
        printf("[ERROR] : function stackCreate failed | copyProject \n");
        return;
    }

    stackPush(stackSrc, srcDir);
    stackPush(stackDest, destDir);

    directoryFree(srcDir);
    directoryFree(destDir);

    char *cExt = stringCreate(".c");

    while (stackLength(stackSrc) > 0)
    {

        Directory *tempDirSrc = stackPop(stackSrc);
        Directory *tempDirDest = stackPop(stackDest);

        if (tempDirSrc == NULL || tempDirDest == NULL)
        {
            printf("[ERROR] : Function stackPop failed | copyProject \n");
            return;
        }

        List *fileNames = listCreate(sizeof(char *), &stringCopy, NULL);

        for (int i = 0; i < directoryGetEntryAmount(tempDirSrc); i++)
        {

            Entry *entrySrc = directoryGetEntryAt(tempDirSrc, i);

            if (entrySrc == NULL)
            {
                printf("[ERROR] : function directoryGetEntryAt failed | copyProject \n");
                return;
            }

            if (entryGetType(entrySrc) == TYPE_DIRECTORY)
            {

                Directory *newSrc = directoryGet(entryGetPath(entrySrc));

                if (newSrc == NULL)
                {
                    printf("[ERROR] : function directoryGet failed | copyProject \n");
                    return;
                }

                bool st1 = directoryCreate(directoryGetPath(tempDirDest), entryGetName(entrySrc));

                if (st1 == false)
                {
                    printf("[ERROR] : Function directoryCreate failed | copyProject \n");
                    return;
                }

                char temp[MAX_LENGTH_PATH];
                strcpy(temp, directoryGetPath(tempDirDest));
                strcat(temp, "/");
                strcat(temp, entryGetName(entrySrc));

                Directory *newDest = directoryGet(temp);

                if (newDest == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | copyProject \n");
                    return;
                }

                stackPush(stackSrc, newSrc);
                stackPush(stackDest, newDest);

                directoryFree(newSrc);
                directoryFree(newDest);
            }

            else
            {

                char *extension = utilGetEx(entryGetName(entrySrc));
                char *name = utilGetName(entryGetName(entrySrc));

                Entry *entryDest = directoryGetEntry(tempDirDest, entryGetName(entrySrc), TYPE_FILE);

                if (strcmp(extension, cExt) == 0)
                {
                    List *tempFileNames = getFileNames(entrySrc);

                    if (tempFileNames == NULL)
                    {
                        printf("[ERROR] : Function getFileNames failed | copyProject \n");
                        return;
                    }

                    utilConcatenateLists(fileNames, tempFileNames);

                    int delete = 2;
                    for (int i = 0; i < listLength(tempFileNames); i++)
                    {
                        char *fileName = listGet(tempFileNames, i);
                        bool doesExist = false;
                        for (int j = 0; j < directoryGetEntryAmount(tempDirDest); j++)
                        {
                            Entry *tempEntryDest = directoryGetEntryAt(tempDirDest, j);
                            char *tempName = stringCreate(entryGetName(tempEntryDest));

                            if (strcmp(tempName, fileName) == 0 && entryGetLastModified(tempEntryDest) > entryGetLastModified(entrySrc))
                            {
                                entryFree(tempEntryDest);
                                free(tempName);
                                doesExist = true;
                                break;
                            }

                            entryFree(tempEntryDest);
                            free(tempName);
                        }

                        if (!doesExist)
                        {
                            splitFile(entrySrc, tempDirDest);
                            free(fileName);
                            break;
                        }
                        free(fileName);
                    }

                    listFree(tempFileNames);
                }
                else if (entryDest == NULL || entryGetLastModified(entryDest) < entryGetLastModified(entrySrc))
                {
                    char dest[MAX_LENGTH_PATH];
                    strcpy(dest, directoryGetPath(tempDirDest));
                    strcat(dest, "/");
                    strcat(dest, entryGetName(entrySrc));

                    bool st2 = fileCopy(dest, entryGetPath(entrySrc));

                    if (st2 == false)
                    {
                        printf("[ERROR] : function fileCopy failed | copyProject \n");
                        return;
                    }
                }

                free(extension);
                free(name);
                if (entryDest != NULL)
                {
                    entryFree(entryDest);
                }
            }

            entryFree(entrySrc);
        }

        for (int i = 0; i < directoryGetEntryAmount(tempDirDest); i++)
        {
            Entry *entryTarget = directoryGetEntryAt(tempDirDest, i);
            char *targetEx = utilGetEx(entryGetName(entryTarget));
            bool doesExist = false;

            if (entryGetType(entryTarget) == TYPE_DIRECTORY)
            {
                for (int j = 0; j < directoryGetEntryAmount(tempDirSrc); j++)
                {
                    Entry *entrySrc = directoryGetEntryAt(tempDirSrc, j);

                    if (entryGetType(entrySrc) == TYPE_DIRECTORY && strcmp(entryGetName(entryTarget), entryGetName(entrySrc)) == 0)
                    {
                        entryFree(entrySrc);
                        doesExist = true;
                        break;
                    }
                    entryFree(entrySrc);
                }
            }

            else
            {
                if (strcmp(targetEx, cExt) == 0)
                {
                    char *name = stringCreate(entryGetName(entryTarget));

                    for (int i = 0; i < listLength(fileNames); i++)
                    {
                        char *temp = listGet(fileNames, i);
                        if (strcmp(name, temp) == 0)
                        {
                            free(temp);
                            doesExist = true;
                            break;
                        }
                        free(temp);
                    }
                    free(name);
                }
                else
                {
                    for (int j = 0; j < directoryGetEntryAmount(tempDirSrc); j++)
                    {
                        Entry *entrySrc = directoryGetEntryAt(tempDirSrc, j);

                        if (entryGetType(entrySrc) == TYPE_FILE && strcmp(entryGetName(entryTarget), entryGetName(entrySrc)) == 0)
                        {
                            entryFree(entrySrc);
                            doesExist = true;
                            break;
                        }
                        entryFree(entrySrc);
                    }
                }
            }

            if (!doesExist)
            {
                if (entryGetType(entryTarget) == TYPE_DIRECTORY)
                {
                    Directory *tempDir = directoryGetSub(tempDirDest, entryGetName(entryTarget));
                    directoryClear(tempDir);
                    directoryDelete(directoryGetPath(tempDir));

                    directoryFree(tempDir);
                }
                else
                {
                    remove(entryGetPath(entryTarget));
                }
            }

            entryFree(entryTarget);
            free(targetEx);
        }

        directoryFree(tempDirSrc);
        directoryFree(tempDirDest);
        listFree(fileNames);
    }
    free(cExt);

    stackFree(stackSrc);
    stackFree(stackDest);
}

List *generateTests(char *destPath, char *srcPath)
{
    Directory *srcDir = directoryGet(srcPath);
    Directory *destDir = directoryGet(destPath);

    if (srcDir == NULL || destDir == NULL)
    {
        printf("[ERROR] : Directory could not be found | generateTests \n");
        return NULL;
    }

    Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
    Stack *stackDest = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

    if (stackSrc == NULL || stackDest == NULL)
    {
        printf("[ERROR] : function stackCreate failed | generateTests \n");
        return NULL;
        ;
    }

    stackPush(stackSrc, srcDir);
    stackPush(stackDest, destDir);

    directoryFree(srcDir);
    directoryFree(destDir);

    int testNum = 1;

    List *mockList = listCreate(listSize(), &listCopy, &listFree);

    char *cExt = stringCreate(".c");

    while (stackLength(stackSrc) > 0)
    {

        Directory *tempDirSrc = stackPop(stackSrc);
        Directory *tempDirDest = stackPop(stackDest);

        if (tempDirSrc == NULL || tempDirDest == NULL)
        {
            printf("[ERROR] : Function stackPop failed | generateTests \n");
            return NULL;
            ;
        }

        for (int i = 0; i < directoryGetEntryAmount(tempDirSrc); i++)
        {

            Entry *entrySrc = directoryGetEntryAt(tempDirSrc, i);

            if (entrySrc == NULL)
            {
                printf("[ERROR] : function directoryGetEntryAt failed | generateTests \n");
                return NULL;
                ;
            }

            if (entryGetType(entrySrc) == TYPE_DIRECTORY)
            {

                Directory *newSrc = directoryGet(entryGetPath(entrySrc));

                if (newSrc == NULL)
                {
                    printf("[ERROR] : function directoryGet failed | generateTests \n");
                    return NULL;
                    ;
                }

                bool st1 = directoryCreate(directoryGetPath(tempDirDest), entryGetName(entrySrc));

                if (st1 == false)
                {
                    printf("[ERROR] : Function directoryCreate failed | generateTests \n");
                    return NULL;
                    ;
                }

                char temp[MAX_LENGTH_PATH];
                strcpy(temp, directoryGetPath(tempDirDest));
                strcat(temp, "/");
                strcat(temp, entryGetName(entrySrc));

                Directory *newDest = directoryGet(temp);

                if (newDest == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | generateTests \n");
                    return NULL;
                    ;
                }

                stackPush(stackSrc, newSrc);
                stackPush(stackDest, newDest);

                directoryFree(newSrc);
                directoryFree(newDest);
            }

            else
            {

                char *extension = utilGetEx(entryGetName(entrySrc));
                char *name = utilGetName(entryGetName(entrySrc));
                char *prefix = stringSub(name, 0, 3);

                Entry *entryDest = directoryGetEntry(tempDirDest, entryGetName(entrySrc), TYPE_FILE);

                if (strcmp(prefix, "test") == 0 && strcmp(extension, ".c") == 0)
                {
                    List *fileNamesList = getFileNames(entrySrc);
                    List *mockListTemp = listCreate(sizeof(char *), &stringCopy, NULL);

                    for (int i = 0; i < listLength(fileNamesList); i++)
                    {
                        char *funcName = listGet(fileNamesList, i);
                        char *tempFuncName = getFileNameWithPathSplit(funcName);

                        free(funcName);

                        tempFuncName = stringSub(tempFuncName, 0, strlen(tempFuncName) - 3);

                        if (tempFuncName == NULL)
                        {
                            printf("[ERROR] : function listGet failed | generateTests \n");
                            return NULL;
                        }

                        char *funcPrefix = stringSub(tempFuncName, 0, 3);

                        if (strcmp(funcPrefix, "test") != 0 && strcmp(funcPrefix, "util") != 0 && strcmp(funcName, name) != 0)
                        {
                            tempFuncName = stringCat(tempFuncName, ".o");
                            listAdd(mockListTemp, tempFuncName);
                        }

                        free(tempFuncName);
                        free(funcPrefix);
                    }
                    listFree(fileNamesList);

                    listAdd(mockList, mockListTemp);

                    listFree(mockListTemp);
                }

                if (entryDest == NULL || entryGetLastModified(entryDest) < entryGetLastModified(entrySrc))
                {
                    char dest[MAX_LENGTH_PATH];
                    strcpy(dest, directoryGetPath(tempDirDest));
                    strcat(dest, "/");
                    strcat(dest, entryGetName(entrySrc));

                    bool st2 = fileCopy(dest, entryGetPath(entrySrc));

                    if (st2 == false)
                    {
                        printf("[ERROR] : function fileCopy failed | generateTests \n");
                        return NULL;
                        ;
                    }

                    if (strcmp(prefix, "test") == 0 && strcmp(extension, ".c") == 0)
                    {
                        List *tempFuncNames = getFileNames(entrySrc);
                        List *testFunc = listCreate(sizeof(char *), &stringCopy, NULL);

                        for (int i = 0; i < listLength(tempFuncNames); i++)
                        {
                            char *temp = listGet(tempFuncNames, i);
                            char *tempTestName = getFileNameWithPathSplit(temp);

                            free(temp);

                            tempTestName = stringSub(tempTestName, 0, strlen(tempTestName) - 3);

                            if (tempTestName == NULL)
                            {
                                printf("[ERROR] : function listGet failed | generateTests \n");
                                return NULL;
                            }

                            char *funcPrefix = stringSub(tempTestName, 0, 3);

                            if (strcmp(funcPrefix, "test") == 0 && strcmp(tempTestName, name) != 0)
                            {
                                listAdd(testFunc, tempTestName);
                            }

                            free(funcPrefix);
                            free(tempTestName);
                        }

                        FILE *testFile = fopen(dest, "a");

                        char *pathTemp = stringCreate(destPath);
                        pathTemp = stringCat(pathTemp, "/util/temp.txt");
                        char *pathUtil = stringCreate(destPath);
                        pathUtil = stringCat(pathUtil, "/util/cbuilderTest.h");

                        char *main = stringCreate("\n#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>\n#include \"$PATHUTIL\"\nint main(int argc, char *argv[]){\n\tint64_t before, after, time;\n\tstrcpy(path,\"$PATHTEMP\");\n\tbool isEnd = false;\n\tif(argc == 2){\n\t\tint end = atoi(argv[1]);\n\t\tif(end == 1){\n\t\t\tisEnd = true;\n\t\t}\n\t}\n\tgetStats();\n");
                        main = stringReplace(main, "$PATHTEMP", pathTemp);
                        main = stringReplace(main, "$PATHUTIL", pathUtil);

                        free(pathTemp);
                        free(pathUtil);

                        int c;
                        for (int i = 0; i < strlen(main); i++)
                        {
                            c = main[i];
                            putc(c, testFile);
                        }

                        char *template = stringCreate("\tpassed = true;\n\tprintf(\"TEST $NUM | $NAME\\n\");\n\tbefore = getTime();\n\t$NAME();\n\tafter = getTime();\n\ttime = after - before;\n\tprintf(\"Execution time: %ld ms\", time);\n\texecutionTime += time;\n\ttestExe++;\n\tif(passed){\n\t\tprintf(\" | PASSED\\n\");\n\t\ttestPassed++;\n\t} else{\n\t\tprintf(\" | FAILED\\n\");\n\t\ttestFailed++;\n\t}\n");

                        for (int i = 0; i < listLength(testFunc); i++)
                        {
                            char *func = listGet(testFunc, i);

                            char *currTemplate = stringCreate(template);
                            currTemplate = stringReplace(currTemplate, "$NAME", func);

                            char num[20];
                            sprintf(num, "%d", testNum);

                            currTemplate = stringReplace(currTemplate, "$NUM", num);

                            for (int j = 0; j < strlen(currTemplate); j++)
                            {
                                c = currTemplate[j];
                                putc(c, testFile);
                            }

                            testNum++;

                            free(func);
                            free(currTemplate);
                        }

                        char *cleanUp = stringCreate("\tif(isEnd && testExe > 0){\n\t\tprintf(\"--------------------------------------------------\\n\");\n\t\ttestPassedRel = ((double)testPassed / (double)testExe) * 100.0;\n\t\ttestFailedRel = ((double)testFailed / (double)testExe) * 100.0;\n\t\tprintf(\"Tests executed: %d | Total execution time: %d ms\\n\",testExe, executionTime);\n\t\tprintf(\"Tests passed: %d | %.2f %\\n\",testPassed, testPassedRel);\n\t\tprintf(\"Tests failed: %d | %.2f %\\n\",testFailed, testFailedRel);\n\t\tremove(path);\n\t} else if(isEnd && testExe == 0){\n\t\tprintf(\"--------------------------------------------------\\n\");\n\t\tprintf(\"No test was executed\");\n\t}\n\telse{\n\t\tsaveStats();\n\t}\n");

                        for (int i = 0; i < strlen(cleanUp); i++)
                        {
                            c = cleanUp[i];
                            putc(c, testFile);
                        }

                        putc('}', testFile);

                        free(template);
                        free(main);
                        free(cleanUp);
                        listFree(tempFuncNames);
                        listFree(testFunc);
                        fclose(testFile);
                    }
                }

                free(extension);
                free(name);
                free(prefix);

                if (entryDest != NULL)
                {
                    entryFree(entryDest);
                }
            }

            entryFree(entrySrc);
        }

        for (int i = 0; i < directoryGetEntryAmount(tempDirDest); i++)
        {
            Entry *entryTarget = directoryGetEntryAt(tempDirDest, i);
            bool doesExist = false;

            for (int j = 0; j < directoryGetEntryAmount(tempDirSrc); j++)
            {
                Entry *entrySrc = directoryGetEntryAt(tempDirSrc, j);

                if (entryGetType(entryTarget) == entryGetType(entrySrc))
                {
                    if ((entryGetType(entryTarget) == TYPE_DIRECTORY) && (strcmp(entryGetName(entryTarget), entryGetName(entrySrc)) == 0))
                    {
                        entryFree(entrySrc);
                        doesExist = true;
                        break;
                    }
                    else if ((entryGetType(entryTarget) == TYPE_FILE))
                    {
                        if (strcmp(entryGetName(entryTarget), entryGetName(entrySrc)) == 0)
                        {
                            free(entrySrc);
                            doesExist = true;
                            break;
                        }
                    }
                }
                entryFree(entrySrc);
            }

            if (!doesExist)
            {
                if (entryGetType(entryTarget) == TYPE_DIRECTORY)
                {
                    Directory *tempDir = directoryGetSub(tempDirDest, entryGetName(entryTarget));
                    directoryClear(tempDir);
                    directoryDelete(directoryGetPath(tempDir));

                    directoryFree(tempDir);
                }
                else
                {
                    remove(entryGetPath(entryTarget));
                }
            }

            entryFree(entryTarget);
        }

        directoryFree(tempDirSrc);
        directoryFree(tempDirDest);
    }
    free(cExt);

    stackFree(stackSrc);
    stackFree(stackDest);

    return mockList;
}

void utilConcatenateLists(List *dest, List *src)
{

    for (int i = 0; i < listLength(src); i++)
    {
        char *temp = listGet(src, i);
        listAdd(dest, temp);
        free(temp);
    }
}