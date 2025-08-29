#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "main.h"
#include "../Util/os.h"
#include "../Util/display.h"
#include "../Util/List/list.h"
#include "../Util/Stack/stack.h"
#include "../Util/String/string.h"
#include "../Directory/directory.h"
#include "../Test/test.h"

/**
 * Functionn that checks if a character c is in the passed array
 *
 * @param arr The array
 * @param length The length of the array
 * @param c The character
 *
 * @return true if c is in arr, false if c is not in arr
 */

bool utilIsInArray(char *arr, int length, int c);












































String *compile(char *destPath, char *srcPath, char *projectPath, bool debug, int *fileCounter, int *alteredFiles)
{
    Directory *dir = directoryGet(projectPath);

    if (dir == NULL)
    {
        printf("[ERROR] : Directory for the specified path was not found | build \n");
        return NULL;
    }

    Entry *builderFile = directoryGetEntry(dir, "cbuilderfile", TYPE_FILE);

    if (builderFile == NULL)
    {
        printf("[ERROR] : Entry for the specified directory was not found | build \n");
        return NULL;
    }

    char builderFilePath[MAX_LENGTH_PATH];
    strcpy(builderFilePath, entryGetPath(builderFile));

    String *systemCommand = stringCreate(NULL);
    String *cFile = stringCreate("$CFILE");
    String *objFile = stringCreate("$OBJFILE");

    char relTarget[MAX_LENGTH_PATH];

    char command[64];

    if (debug)
    {
        strcpy(command, "debug");
    }
    else
    {
        strcpy(command, "build");
    }

    getCommand(command, builderFilePath, systemCommand);

    char *commandBluePrint = stringToArr(systemCommand);

    directoryFree(dir);
    entryFree(builderFile);

    Directory *src = directoryGet(srcPath);

    if (src == NULL)
    {
        printf("[ERROR] : The c directory of the project was not found | build \n");
        return NULL;
    }

    Directory *target = directoryGet(destPath);

    if (target == NULL)
    {
        printf("[ERROR] : The %s directory of the project was not found | build \n", relTarget);
        return NULL;
    }

    Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
    Stack *stackTarget = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

    if (stackSrc == NULL || stackTarget == NULL)
    {
        printf("[ERROR] : Function stackCreate failed | build \n");
        return NULL;
    }

    int st1 = stackPush(stackSrc, src);
    int st2 = stackPush(stackTarget, target);

    if (st1 == -1 || st2 == -1)
    {
        printf("[ERROR] : Function stackPush failed | build \n");
        return NULL;
    }

    *fileCounter = 0;
    *alteredFiles = 0;

    String *oFileList = stringCreate(NULL);
    String *delimiter = stringCreate(" ");

    String *objType = stringCreate(".o");
    String *cType = stringCreate(".c");

    while (stackLength(stackSrc) > 0)
    {
        Directory *tempSrc = stackPop(stackSrc);
        Directory *tempTarget = stackPop(stackTarget);

        if (tempSrc == NULL || tempTarget == NULL)
        {
            printf("[ERROR] : Function stackPop failed | build \n");
            return NULL;
        }

        for (int i = 0; i < directoryGetEntryAmount(tempSrc); i++)
        {
            Entry *tempEntrySrc = directoryGetEntryAt(tempSrc, i);

            if (tempEntrySrc == NULL)
            {
                printf("[ERROR] : Function directoryGetEntryAt failed | build \n");
                return NULL;
            }

            String *cPath = stringCreate(entryGetPath(tempEntrySrc));
            String *name = utilGetName(entryGetName(tempEntrySrc));
            String *type = utilGetEx(entryGetName(tempEntrySrc));
            String *objPath = stringCreate(directoryGetPath(tempTarget));
            String *objName = stringCopy(name);
            stringCat(objName, objType);
            String *slash = stringCreate("/");
            stringCat(objPath, slash);
            stringCat(objPath, name);
            stringCat(objPath, objType);

            if (entryGetType(tempEntrySrc) == TYPE_DIRECTORY)
            {
                Directory *newDirSrc = directoryGet(entryGetPath(tempEntrySrc));

                if (newDirSrc == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | build \n");
                    return NULL;
                }

                bool st3 = directoryCreate(directoryGetPath(tempTarget), entryGetName(tempEntrySrc));

                if (st3 == false)
                {
                    printf("[ERROR] : Function directoryCreate failed | build \n");
                    return NULL;
                }

                char temp[MAX_LENGTH_PATH];
                strcpy(temp, directoryGetPath(tempTarget));
                strcat(temp, "/");
                strcat(temp, entryGetName(tempEntrySrc));

                Directory *newDirTarget = directoryGet(temp);

                if (newDirTarget == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | build \n");
                    return NULL;
                }

                stackPush(stackSrc, newDirSrc);
                stackPush(stackTarget, newDirTarget);

                directoryFree(newDirSrc);
                directoryFree(newDirTarget);
            }

            else if (stringEquals(type, cType))
            {
                (*fileCounter)++;

                char *tempObjName = stringToArr(objName);
                Entry *tempEntryTarget = directoryGetEntry(tempTarget, tempObjName, TYPE_FILE);
                free(tempObjName);

                stringReplace(systemCommand, cFile, cPath);
                stringReplace(systemCommand, objFile, objPath);

                if (tempEntryTarget != NULL && entryGetLastModified(tempEntryTarget) < entryGetLastModified(tempEntrySrc))
                {
                    (*alteredFiles)++;

                    int st4 = remove(entryGetPath(tempEntryTarget));

                    if (st4 != 0)
                    {
                        printf("[ERROR] : Function remove failed | build \n");
                        return NULL;
                    }
                    char *tempCmd = stringToArr(systemCommand);
                    system(tempCmd);
                    free(tempCmd);
                }
                else if (tempEntryTarget == NULL)
                {
                    (*alteredFiles)++;

                    char *tempCmd = stringToArr(systemCommand);
                    system(tempCmd);
                    free(tempCmd);
                }

                if (tempEntryTarget != NULL)
                {
                    entryFree(tempEntryTarget);
                }
                stringFree(systemCommand);
                systemCommand = stringCreate(commandBluePrint);

                stringCat(oFileList, objPath);
                stringCat(oFileList, delimiter);
            }

            entryFree(tempEntrySrc);
            stringFree(cPath);
            stringFree(objPath);
            stringFree(objName);
            stringFree(type);
            stringFree(name);
            stringFree(slash);
        }

        for (int i = 0; i < directoryGetEntryAmount(tempTarget); i++)
        {
            Entry *entryTarget = directoryGetEntryAt(tempTarget, i);
            bool doesExist = false;

            for (int j = 0; j < directoryGetEntryAmount(tempSrc); j++)
            {
                Entry *entrySrc = directoryGetEntryAt(tempSrc, j);

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
                        String *targetName = utilGetName(entryGetName(entryTarget));
                        String *targetEx = utilGetEx(entryGetName(entryTarget));
                        String *srcName = utilGetName(entryGetName(entrySrc));
                        String *srcEx = utilGetEx(entryGetName(entrySrc));

                        if (stringEquals(targetName, srcName) && stringEquals(targetEx, objType) && stringEquals(srcEx, cType))
                        {
                            stringFree(targetName);
                            stringFree(targetEx);
                            stringFree(srcName);
                            stringFree(srcEx);
                            entryFree(entrySrc);
                            doesExist = true;
                            break;
                        }
                        stringFree(targetName);
                        stringFree(targetEx);
                        stringFree(srcName);
                        stringFree(srcEx);
                    }
                }
                entryFree(entrySrc);
            }

            if (!doesExist)
            {
                if (entryGetType(entryTarget) == TYPE_DIRECTORY)
                {
                    Directory *tempDir = directoryGetSub(tempTarget, entryGetName(entryTarget));
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

        directoryFree(tempSrc);
        directoryFree(tempTarget);
    }
    stackFree(stackSrc);
    stackFree(stackTarget);
    stringFree(systemCommand);
    stringFree(cFile);
    stringFree(objFile);
    stringFree(objType);
    stringFree(cType);
    stringFree(delimiter);
    free(commandBluePrint);

    int fileCounterTemp = *fileCounter;
    int alteredFilesTemp = *alteredFiles;

    memcpy(fileCounter, &fileCounterTemp, sizeof(int));
    memcpy(alteredFiles, &alteredFilesTemp, sizeof(int));

    return oFileList;
}
