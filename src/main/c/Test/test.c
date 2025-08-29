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

List *splitFile(Entry *src, Directory *dest)
{
    if (src == NULL)
    {
        printf("[ERROR] : the src entry can not be null | splitFile \n");
        return NULL;
    }

    if (dest == NULL)
    {
        printf("[ERROR] : the dest directory can not be null | splitFile \n");
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

    List *splitFiles = listCreate(stringSize(), &stringCopy, &stringFree);
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

                    listAdd(funcNames, tempName);
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

    List *fileNames = listCreate(stringSize(), &stringCopy, &stringFree);

    for (int i = 0; i < listLength(splitFiles); i++)
    {
        String *func = listGet(splitFiles, i);

        String *funcName = listGet(funcNames, i);

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

        listAdd(fileNames, filePath);

        FILE *tempFile = fopen(stringToArr(filePath), "w");

        if (tempFile == NULL)
        {
            printf("[ERROR] : Could not open file | splitFile \n");
            return NULL;
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
    listFree(funcNames);
    listFree(splitFiles);

    return fileNames;
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

    String *cExt = stringCreate(".c");

    while (stackLength(stackSrc) > 0)
    {

        Directory *tempDirSrc = stackPop(stackSrc);
        Directory *tempDirDest = stackPop(stackDest);

        if (tempDirSrc == NULL || tempDirDest == NULL)
        {
            printf("[ERROR] : Function stackPop failed | copyProject \n");
            return;
        }

        List *fileNames = listCreate(stringSize(), &stringCopy, &stringFree);

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
                    printf("[ERROR] : Function directoryCreate failed | build \n");
                    return;
                }

                char temp[MAX_LENGTH_PATH];
                strcpy(temp, directoryGetPath(tempDirDest));
                strcat(temp, "/");
                strcat(temp, entryGetName(entrySrc));

                Directory *newDest = directoryGet(temp);

                if (newDest == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | build \n");
                    return;
                }

                stackPush(stackSrc, newSrc);
                stackPush(stackDest, newDest);

                directoryFree(newSrc);
                directoryFree(newDest);
            }

            else
            {

                String *extension = utilGetEx(entryGetName(entrySrc));
                String *name = utilGetName(entryGetName(entrySrc));

                Entry *entryDest = directoryGetEntry(tempDirDest, entryGetName(entrySrc), TYPE_FILE);

                if (stringEquals(extension, cExt))
                {
                    int delete = 2;
                    for (int i = 0; i < directoryGetEntryAmount(tempDirDest); i++)
                    {
                        Entry *tempEntryDest = directoryGetEntryAt(tempDirDest, i);
                        String *tempName = stringCreate(entryGetName(tempEntryDest));
                        String *subName = stringSub(name, 0, stringLength(name) - 1);
                        String *tempEx = utilGetEx(stringToArr(tempName));

                        if (stringEquals(subName, name) && stringEquals(tempEx, cExt))
                        {
                            if (delete == 0)
                            {
                                remove(entryGetPath(tempEntryDest));
                            }
                            else if (entryGetLastModified(tempEntryDest) > entryGetLastModified(entrySrc))
                            {
                                delete = 1;
                                entryFree(tempEntryDest);
                                stringFree(tempName);
                                stringFree(subName);
                                stringFree(tempEx);
                                break;
                            }
                            else
                            {
                                delete = 0;
                                remove(entryGetPath(tempEntryDest));
                            }
                        }

                        entryFree(tempEntryDest);
                        stringFree(tempName);
                        stringFree(subName);
                        stringFree(tempEx);
                    }

                    if (delete == 2 || delete == 0)
                    {
                        List *tempFileNames = splitFile(entrySrc, tempDirDest);

                        if (tempFileNames == NULL)
                        {
                            printf("[ERROR] : Function splitFile failed | copyProject \n");
                            return;
                        }

                        utilConcatenateLists(fileNames, tempFileNames);

                        listFree(tempFileNames);
                    }
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

                stringFree(extension);
                stringFree(name);
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
                String *name = stringCreate(entryGetName(entryTarget));

                for (int i = 0; i < listLength(fileNames); i++)
                {
                    String *temp = listGet(fileNames, i);
                    if (stringEquals(name, temp))
                    {
                        stringFree(temp);
                        doesExist = true;
                        break;
                    }
                    stringFree(temp);
                }
                stringFree(name);
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
        listFree(fileNames);
    }
    stringFree(cExt);

    stackFree(stackSrc);
    stackFree(stackDest);
}

void generateTests(char *destPath, char *srcPath)
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

    String *cExt = stringCreate(".c");

    while (stackLength(stackSrc) > 0)
    {

        Directory *tempDirSrc = stackPop(stackSrc);
        Directory *tempDirDest = stackPop(stackDest);

        if (tempDirSrc == NULL || tempDirDest == NULL)
        {
            printf("[ERROR] : Function stackPop failed | copyProject \n");
            return;
        }

        List *fileNames = listCreate(stringSize(), &stringCopy, &stringFree);

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
                    printf("[ERROR] : Function directoryCreate failed | build \n");
                    return;
                }

                char temp[MAX_LENGTH_PATH];
                strcpy(temp, directoryGetPath(tempDirDest));
                strcat(temp, "/");
                strcat(temp, entryGetName(entrySrc));

                Directory *newDest = directoryGet(temp);

                if (newDest == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | build \n");
                    return;
                }

                stackPush(stackSrc, newSrc);
                stackPush(stackDest, newDest);

                directoryFree(newSrc);
                directoryFree(newDest);
            }

            else
            {

                String *extension = utilGetEx(entryGetName(entrySrc));
                String *name = utilGetName(entryGetName(entrySrc));

                Entry *entryDest = directoryGetEntry(tempDirDest, entryGetName(entrySrc), TYPE_FILE);

                if (stringEquals(extension, cExt))
                {
                    int delete = 2;
                    for (int i = 0; i < directoryGetEntryAmount(tempDirDest); i++)
                    {
                        Entry *tempEntryDest = directoryGetEntryAt(tempDirDest, i);
                        String *tempName = stringCreate(entryGetName(tempEntryDest));
                        String *subName = stringSub(name, 0, stringLength(name) - 1);
                        String *tempEx = utilGetEx(stringToArr(tempName));

                        if (stringEquals(subName, name) && stringEquals(tempEx, cExt))
                        {
                            if (delete == 0)
                            {
                                remove(entryGetPath(tempEntryDest));
                            }
                            else if (entryGetLastModified(tempEntryDest) > entryGetLastModified(entrySrc))
                            {
                                delete = 1;
                                entryFree(tempEntryDest);
                                stringFree(tempName);
                                stringFree(subName);
                                stringFree(tempEx);
                                break;
                            }
                            else
                            {
                                delete = 0;
                                remove(entryGetPath(tempEntryDest));
                            }
                        }

                        entryFree(tempEntryDest);
                        stringFree(tempName);
                        stringFree(subName);
                        stringFree(tempEx);
                    }

                    if (delete == 2 || delete == 0)
                    {
                        List *tempFileNames = splitFile(entrySrc, tempDirDest);

                        if (tempFileNames == NULL)
                        {
                            printf("[ERROR] : Function splitFile failed | copyProject \n");
                            return;
                        }

                        utilConcatenateLists(fileNames, tempFileNames);

                        listFree(tempFileNames);
                    }
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

                stringFree(extension);
                stringFree(name);
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
                String *name = stringCreate(entryGetName(entryTarget));

                for (int i = 0; i < listLength(fileNames); i++)
                {
                    String *temp = listGet(fileNames, i);
                    if (stringEquals(name, temp))
                    {
                        stringFree(temp);
                        doesExist = true;
                        break;
                    }
                    stringFree(temp);
                }
                stringFree(name);
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
        listFree(fileNames);
    }
    stringFree(cExt);

    stackFree(stackSrc);
    stackFree(stackDest);
}

void utilConcatenateLists(List *dest, List *src)
{

    for (int i = 0; i < listLength(src); i++)
    {
        String *temp = listGet(src, i);
        listAdd(dest, temp);
        stringFree(temp);
    }
}
