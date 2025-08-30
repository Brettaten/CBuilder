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

                String *extension = utilGetEx(entryGetName(entrySrc));
                String *name = utilGetName(entryGetName(entrySrc));

                Entry *entryDest = directoryGetEntry(tempDirDest, entryGetName(entrySrc), TYPE_FILE);

                if (stringEquals(extension, cExt))
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
                        String *fileName = listGet(fileNames, i);
                        bool doesExist = false;
                        for (int j = 0; j < directoryGetEntryAmount(tempDirDest); j++)
                        {
                            Entry *tempEntryDest = directoryGetEntryAt(tempDirDest, j);
                            String *tempName = stringCreate(entryGetName(tempEntryDest));

                            if (stringEquals(tempName, fileName) && entryGetLastModified(tempEntryDest) > entryGetLastModified(entrySrc))
                            {
                                entryFree(tempEntryDest);
                                stringFree(tempName);
                                doesExist = true;
                                break;
                            }

                            entryFree(tempEntryDest);
                            stringFree(tempName);
                        }

                        if (!doesExist)
                        {
                            splitFile(entrySrc, tempDirDest);
                            stringFree(fileName);
                            break;
                        }
                        stringFree(fileName);
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
            String *targetEx = utilGetEx(entryGetName(entryTarget));
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
                if (stringEquals(targetEx, cExt))
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
            stringFree(targetEx);
        }

        directoryFree(tempDirSrc);
        directoryFree(tempDirDest);
        listFree(fileNames);
    }
    stringFree(cExt);

    stackFree(stackSrc);
    stackFree(stackDest);
}
