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

                        char *template = stringCreate("\tpassed = true;\n\tprintf(\"TEST $NUM | $NAME\\n\");\n\tbefore = getTime();\n\t$NAME();\n\tafter = getTime();\n\ttime = after - before;\n\tprintf(\"Execution time: %lld ms\", time);\n\texecutionTime += time;\n\ttestExe++;\n\tif(passed){\n\t\tprintf(\" | PASSED\\n\");\n\t\ttestPassed++;\n\t} else{\n\t\tprintf(\" | FAILED\\n\");\n\t\ttestFailed++;\n\t}\n");

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

                        char *cleanUp = stringCreate("\tif(isEnd && testExe > 0){\n\t\tprintf(\"--------------------------------------------------\\n\");\n\t\ttestPassedRel = ((double)testPassed / (double)testExe) * 100.0;\n\t\ttestFailedRel = ((double)testFailed / (double)testExe) * 100.0;\n\t\tprintf(\"Tests executed: %d | Total execution time: %d ms\\n\",testExe, executionTime);\n\t\tprintf(\"Tests passed: %d | %.2f %%\\n\",testPassed, testPassedRel);\n\t\tprintf(\"Tests failed: %d | %.2f %%\\n\",testFailed, testFailedRel);\n\t\tremove(path);\n\t} else if(isEnd && testExe == 0){\n\t\tprintf(\"--------------------------------------------------\\n\");\n\t\tprintf(\"No test was executed\");\n\t}\n\telse{\n\t\tsaveStats();\n\t}\n");

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
