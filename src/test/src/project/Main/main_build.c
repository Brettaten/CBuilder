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

/**
 * Function that strips the file name and returns the file extension as a string
 *
 * @param name the file name with file extension
 *
 * @return Success: the file extension without name | Failure: NULL
 */
String *utilGetEx(char *name);





















void build(char *path, bool debug)
{
    char projectPath[MAX_LENGTH_PATH];
    bool project = false;

    int st1 = findProject(path, projectPath);

    if (st1 == -1)
    {
        directoryNormalizePath(projectPath, path);
        project = false;
    }
    else
    {
        project = true;
    }

    if (project)
    {
        Directory *dir = directoryGet(projectPath);

        if (dir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | build \n");
            return;
        }

        Entry *bin = directoryGetEntry(dir, "bin", TYPE_DIRECTORY);

        if (bin == NULL)
        {
            printf("[ERROR] : Bin directory was not found | build \n");
            return;
        }

        String *binDirPath = stringCreate(entryGetPath(bin));

        entryFree(bin);

        Entry *builderFile = directoryGetEntry(dir, "cbuilderfile", TYPE_FILE);

        if (builderFile == NULL)
        {
            printf("[ERROR] : Entry for the specified directory was not found | build \n");
            return;
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
            strcpy(relTarget, "/target/debug");
        }
        else
        {
            strcpy(command, "build");
            strcpy(relTarget, "/target/prod");
        }

        getCommand(command, builderFilePath, systemCommand);

        char *commandBluePrint = stringToArr(systemCommand);

        char filePath[MAX_LENGTH_PATH];

        directoryFree(dir);
        entryFree(builderFile);

        char srcPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcat(srcPath, "/src/main/c");
        Directory *src = directoryGet(srcPath);

        if (src == NULL)
        {
            printf("[ERROR] : The c directory of the project was not found | build \n");
            return;
        }

        char targetPath[MAX_LENGTH_PATH];
        strcpy(targetPath, projectPath);
        strcat(targetPath, relTarget);
        Directory *target = directoryGet(targetPath);

        if (target == NULL)
        {
            printf("[ERROR] : The %s directory of the project was not found | build \n", relTarget);
            return;
        }

        Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
        Stack *stackTarget = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

        if (stackSrc == NULL || stackTarget == NULL)
        {
            printf("[ERROR] : Function stackCreate failed | build \n");
            return;
        }

        int st1 = stackPush(stackSrc, src);
        int st2 = stackPush(stackTarget, target);

        if (st1 == -1 || st2 == -1)
        {
            printf("[ERROR] : Function stackPush failed | build \n");
            return;
        }

        String *oFileList = stringCreate(NULL);
        String *delimiter = stringCreate(" ");

        String *objType = stringCreate(".o");
        String *cType = stringCreate(".c");

        int fileCounter = 0;
        int alteredFileCounter = 0;

        while (stackLength(stackSrc) > 0)
        {
            Directory *tempSrc = stackPop(stackSrc);
            Directory *tempTarget = stackPop(stackTarget);

            if (tempSrc == NULL || tempTarget == NULL)
            {
                printf("[ERROR] : Function stackPop failed | build \n");
                return;
            }

            for (int i = 0; i < directoryGetEntryAmount(tempSrc); i++)
            {
                Entry *tempEntrySrc = directoryGetEntryAt(tempSrc, i);

                if (tempEntrySrc == NULL)
                {
                    printf("[ERROR] : Function directoryGetEntryAt failed | build \n");
                    return;
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
                        return;
                    }

                    bool st3 = directoryCreate(directoryGetPath(tempTarget), entryGetName(tempEntrySrc));

                    if (st3 == false)
                    {
                        printf("[ERROR] : Function directoryCreate failed | build \n");
                        return;
                    }

                    char temp[MAX_LENGTH_PATH];
                    strcpy(temp, directoryGetPath(tempTarget));
                    strcat(temp, "/");
                    strcat(temp, entryGetName(tempEntrySrc));

                    Directory *newDirTarget = directoryGet(temp);

                    if (newDirTarget == NULL)
                    {
                        printf("[ERROR] : Function directoryGet failed | build \n");
                        return;
                    }

                    stackPush(stackSrc, newDirSrc);
                    stackPush(stackTarget, newDirTarget);

                    directoryFree(newDirSrc);
                    directoryFree(newDirTarget);
                }

                else if (stringEquals(type, cType))
                {
                    fileCounter++;

                    char *tempObjName = stringToArr(objName);
                    Entry *tempEntryTarget = directoryGetEntry(tempTarget, tempObjName, TYPE_FILE);
                    free(tempObjName);

                    stringReplace(systemCommand, cFile, cPath);
                    stringReplace(systemCommand, objFile, objPath);

                    if (tempEntryTarget != NULL && entryGetLastModified(tempEntryTarget) < entryGetLastModified(tempEntrySrc))
                    {
                        alteredFileCounter++;

                        int st4 = remove(entryGetPath(tempEntryTarget));

                        if (st4 != 0)
                        {
                            printf("[ERROR] : Function remove failed | build \n");
                            return;
                        }
                        char *tempCmd = stringToArr(systemCommand);
                        system(tempCmd);
                        free(tempCmd);
                    }
                    else if (tempEntryTarget == NULL)
                    {
                        alteredFileCounter++;

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

        char linkCommand[] = "link";
        String *linkSystemCommand = stringCreate(NULL);
        String *objFiles = stringCreate("$OBJFILES");
        String *binPath = stringCreate("$BINPATH");
        String *permission = stringCreate("chmod a+x ");

        stringCat(permission, binDirPath);

        getCommand(linkCommand, builderFilePath, linkSystemCommand);

        stringReplace(linkSystemCommand, objFiles, oFileList);
        stringReplace(linkSystemCommand, binPath, binDirPath);

        char *tempLinkCmd = stringToArr(linkSystemCommand);
        system(tempLinkCmd);

#ifdef LINUX
        char *tempPermissionCmd = stringToArr(permission);
        system(tempPermissionCmd);
        free(tempPermissionCmd);
#elif defined(APPLE)
        char *tempPermissionCmd = stringToArr(permission);
        system(tempPermissionCmd);
        free(tempPermissionCmd);
#endif
        free(tempLinkCmd);

        stringFree(linkSystemCommand);
        stringFree(objFiles);
        stringFree(oFileList);
        stringFree(binPath);
        stringFree(binDirPath);
        stringFree(permission);

        char fileCounterC[16];
        char alteredFileCounterC[16];
        sprintf(fileCounterC, "%d", fileCounter);
        sprintf(alteredFileCounterC, "%d", alteredFileCounter);

        printf(SEPERATOR);
        printf(HEADING, "S U C C E S S");
        printf(LINE, "Files compiled:", alteredFileCounterC);
        printf(LINE, "Files linked:", fileCounterC);
        printf(SEPERATOR);
    }
    else
    {
        printf(SEPERATOR);
        printf(HEADING, "E R R O R");
        printf(LINE, "No CBuilder project was found at:", projectPath);
        printf(SEPERATOR);
        return;
    }
}