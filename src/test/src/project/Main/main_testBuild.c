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


























void testBuild(char *path)
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
        char srcPath[MAX_LENGTH_PATH];
        char destPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/main/c");
        strcat(destPath, "/src/test/src/project");

        Directory *srcDir = directoryGet(srcPath);
        Directory *destDir = directoryGet(destPath);

        if (srcDir == NULL || destDir == NULL)
        {
            printf("[ERROR] : Directory could not be found | testBuild \n");
            return;
        }

        Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
        Stack *stackDest = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

        if (stackSrc == NULL || stackDest == NULL)
        {
            printf("[ERROR] : function stackCreate failed | testBuild \n");
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
                printf("[ERROR] : Function stackPop failed | testBuild \n");
                return;
            }

            for (int i = 0; i < directoryGetEntryAmount(tempDirSrc); i++)
            {

                Entry *entrySrc = directoryGetEntryAt(tempDirSrc, i);

                if (entrySrc == NULL)
                {
                    printf("[ERROR] : function directoryGetEntryAt failed | testBuild \n");
                    return;
                }

                if (entryGetType(entrySrc) == TYPE_DIRECTORY)
                {

                    Directory *newSrc = directoryGet(entryGetPath(entrySrc));

                    if (newSrc == NULL)
                    {
                        printf("[ERROR] : function directoryGet failed | testBuild \n");
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
                            int st3 = splitFile(entrySrc, tempDirDest);

                            if (st3 == 1)
                            {
                                printf("[ERROR] : Function splitFile failed | testBuild \n");
                                return;
                            }
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
                            printf("[ERROR] : function fileCopy failed | testBuild \n");
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
            directoryFree(tempDirSrc);
            directoryFree(tempDirDest);
        }
        stringFree(cExt);

        stackFree(stackSrc);
        stackFree(stackDest);

        strcpy(srcPath, destPath);
        strcpy(destPath, projectPath);
        strcat(destPath, "/src/test/target/project");

        int fileCounter = 0;
        int alteredFiles = 0;

        String *oFileList = compile(destPath, srcPath, projectPath, true, &fileCounter, &alteredFiles);
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
