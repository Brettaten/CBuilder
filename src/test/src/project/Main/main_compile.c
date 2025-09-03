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


 int x = 10;












































char *compile(char *destPath, char *srcPath, char *projectPath, bool debug, int *fileCounter, int *alteredFiles)
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

    char *systemCommand = stringCreate(NULL);
    char *cFile = stringCreate("$CFILE");
    char *objFile = stringCreate("$OBJFILE");

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

    systemCommand = getCommand(command, builderFilePath, systemCommand);

    char *commandBluePrint = stringCreate(systemCommand);

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

    char *oFileList = stringCreate(NULL);

    char *delimiter = " ";
    char *objType = ".o";
    char *cType = ".c";
    char *slash = "/";

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

            char *cPath = stringCreate(entryGetPath(tempEntrySrc));
            char *name = utilGetName(entryGetName(tempEntrySrc));
            char *type = utilGetEx(entryGetName(tempEntrySrc));
            char *objPath = stringCreate(directoryGetPath(tempTarget));
            char *objName = stringCreate(name);
            objName = stringCat(objName, objType);
            objPath = stringCat(objPath, slash);
            objPath = stringCat(objPath, name);
            objPath = stringCat(objPath, objType);

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
                strcat(temp, slash);
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

            else if (strcmp(type, cType) == 0)
            {
                (*fileCounter)++;

                Entry *tempEntryTarget = directoryGetEntry(tempTarget, objName, TYPE_FILE);

                systemCommand = stringReplace(systemCommand, cFile, cPath);
                systemCommand = stringReplace(systemCommand, objFile, objPath);

                if (tempEntryTarget != NULL && entryGetLastModified(tempEntryTarget) < entryGetLastModified(tempEntrySrc))
                {
                    (*alteredFiles)++;

                    int st4 = remove(entryGetPath(tempEntryTarget));

                    if (st4 != 0)
                    {
                        printf("[ERROR] : Function remove failed | build \n");
                        return NULL;
                    }
                    system(systemCommand);
                }
                else if (tempEntryTarget == NULL)
                {
                    (*alteredFiles)++;

                    system(systemCommand);
                }

                if (tempEntryTarget != NULL)
                {
                    entryFree(tempEntryTarget);
                }
                free(systemCommand);
                systemCommand = stringCreate(commandBluePrint);

                oFileList = stringCat(oFileList, objPath);
                oFileList = stringCat(oFileList, delimiter);
            }

            entryFree(tempEntrySrc);
            free(cPath);
            free(objPath);
            free(objName);
            free(type);
            free(name);
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
                        char *targetName = utilGetName(entryGetName(entryTarget));
                        char *targetEx = utilGetEx(entryGetName(entryTarget));
                        char *srcName = utilGetName(entryGetName(entrySrc));
                        char *srcEx = utilGetEx(entryGetName(entrySrc));

                        if (strcmp(targetName, srcName) == 0 && strcmp(targetEx, objType) == 0 && strcmp(srcEx, cType) == 0)
                        {
                            free(targetName);
                            free(targetEx);
                            free(srcName);
                            free(srcEx);
                            free(entrySrc);
                            doesExist = true;
                            break;
                        }
                        free(targetName);
                        free(targetEx);
                        free(srcName);
                        free(srcEx);
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
    free(systemCommand);
    free(cFile);
    free(objFile);
    free(commandBluePrint);

    int fileCounterTemp = *fileCounter;
    int alteredFilesTemp = *alteredFiles;

    memcpy(fileCounter, &fileCounterTemp, sizeof(int));
    memcpy(alteredFiles, &alteredFilesTemp, sizeof(int));

    return oFileList;
}
