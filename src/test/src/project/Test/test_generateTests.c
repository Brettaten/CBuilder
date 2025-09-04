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












void generateTests(char *destPath, char *srcPath)
{
    Directory *srcDir = directoryGet(srcPath);
    Directory *destDir = directoryGet(destPath);

    if (srcDir == NULL || destDir == NULL)
    {
        printf("[ERROR] : Directory could not be found | generateTests \n");
        return;
    }

    Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
    Stack *stackDest = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

    if (stackSrc == NULL || stackDest == NULL)
    {
        printf("[ERROR] : function stackCreate failed | generateTests \n");
        return;
    }

    stackPush(stackSrc, srcDir);
    stackPush(stackDest, destDir);

    directoryFree(srcDir);
    directoryFree(destDir);

    int testNum = 1;

    char *cExt = stringCreate(".c");

    while (stackLength(stackSrc) > 0)
    {

        Directory *tempDirSrc = stackPop(stackSrc);
        Directory *tempDirDest = stackPop(stackDest);

        if (tempDirSrc == NULL || tempDirDest == NULL)
        {
            printf("[ERROR] : Function stackPop failed | generateTests \n");
            return;
        }

        for (int i = 0; i < directoryGetEntryAmount(tempDirSrc); i++)
        {

            Entry *entrySrc = directoryGetEntryAt(tempDirSrc, i);

            if (entrySrc == NULL)
            {
                printf("[ERROR] : function directoryGetEntryAt failed | generateTests \n");
                return;
            }

            if (entryGetType(entrySrc) == TYPE_DIRECTORY)
            {

                Directory *newSrc = directoryGet(entryGetPath(entrySrc));

                if (newSrc == NULL)
                {
                    printf("[ERROR] : function directoryGet failed | generateTests \n");
                    return;
                }

                bool st1 = directoryCreate(directoryGetPath(tempDirDest), entryGetName(entrySrc));

                if (st1 == false)
                {
                    printf("[ERROR] : Function directoryCreate failed | generateTests \n");
                    return;
                }

                char temp[MAX_LENGTH_PATH];
                strcpy(temp, directoryGetPath(tempDirDest));
                strcat(temp, "/");
                strcat(temp, entryGetName(entrySrc));

                Directory *newDest = directoryGet(temp);

                if (newDest == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | generateTests \n");
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
                char *prefix = stringSub(name, 0, 3);

                Entry *entryDest = directoryGetEntry(tempDirDest, entryGetName(entrySrc), TYPE_FILE);

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
                        return;
                    }

                    if (strcmp(prefix, "test") == 0 && strcmp(extension, ".c") == 0)
                    {
                        List *tempFuncNames = getFileNames(entrySrc);
                        List *testFunc = listCreate(sizeof(char *), &stringCopy, NULL);

                        for (int i = 0; i < listLength(tempFuncNames); i++)
                        {
                            char *temp = listGet(tempFuncNames, i);
                            temp = stringSub(temp, 5, strlen(temp) - 3);

                            if (temp == NULL)
                            {
                                printf("[ERROR] : function listGet failed | generateTests \n");
                                return;
                            }

                            char *funcPrefix = stringSub(temp, 0, 3);

                            if (strcmp(funcPrefix, "test") == 0 && strcmp(temp, entryGetName(entrySrc)) != 0)
                            {
                                listAdd(testFunc, temp);
                            }

                            free(funcPrefix);
                            free(temp);
                        }

                        FILE *testFile = fopen(dest, "a");

                        char *main = "\n#include <stdio.h>\n#include <time.h>\nint main(){\n";

                        int c;
                        for (int i = 0; i < strlen(main); i++)
                        {
                            c = main[i];
                            putc(c, testFile);
                        }

                        char *template = stringCreate("\tprintf(\"TEST $NUM | $NAME\n\");\n\ttime_t before = time(NULL);\n\t$NAME();\n\ttime_t after = time(NULL);\n\ttime_t time = after - before;\n\tprintf(\"%ld\n\", time);\n");

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

                        putc('}', testFile);

                        free(template);
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
}
