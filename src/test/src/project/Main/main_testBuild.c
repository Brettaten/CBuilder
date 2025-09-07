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
        char builderFilePath[MAX_LENGTH_PATH];
        strcpy(builderFilePath, projectPath);
        strcat(builderFilePath, "/cbuilderfile");

        char binDirPath[MAX_LENGTH_PATH];
        strcpy(binDirPath, projectPath);
        strcat(binDirPath, "/src/test/bin");

        char srcPath[MAX_LENGTH_PATH];
        char destPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/main/c");
        strcat(destPath, "/src/test/src/project");

        copyProject(destPath, srcPath);

        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/test/src/main/c");
        strcat(destPath, "/src/test/src/main/genTests");

        List *mockList = generateTests(destPath, srcPath);

        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/test/src/project");
        strcat(destPath, "/src/test/target/project");

        int fileCounter = 0;
        int alteredFiles = 0;

        char *oFileListProject = compile(destPath, srcPath, projectPath, true, &fileCounter, &alteredFiles);

        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/test/src/main/genTests");
        strcat(destPath, "/src/test/target/test");

        char *oFileListTest = compile(destPath, srcPath, projectPath, true, &fileCounter, &alteredFiles);

        List *tests = listCreate(sizeof(char *), &stringCopy, NULL);
        char *testOFiles = stringCreate(NULL);
        char *token = stringCreate(NULL);
        int c;

        for (int i = 0; i < strlen(oFileListTest); i++)
        {
            c = oFileListTest[i];

            if (isspace(c))
            {
                char *name = getFileNameWithPath(token);

                if (strlen(name) >= 6)
                {
                    char *sub = stringSub(name, 0, 3);

                    if (strcmp(sub, "test") == 0)
                    {
                        listAdd(tests, token);
                    }
                    else
                    {
                        testOFiles = stringCat(testOFiles, token);
                        testOFiles = stringCat(testOFiles, " ");
                    }

                    free(sub);
                }
                else
                {
                    testOFiles = stringCat(testOFiles, token);
                    testOFiles = stringCat(testOFiles, " ");
                }

                token = stringClear(token);

                free(name);
            }
            else
            {
                token = stringAdd(token, c);
            }
        }

        free(token);

        for (int i = 0; i < listLength(tests); i++)
        {
            char *testFile = listGet(tests, i);
            char *listFiles = stringCreate(testFile);

            listFiles = stringCat(listFiles, " ");
            listFiles = stringCat(listFiles, testOFiles);

            List *mockFiles = listGet(mockList, i);
            char *projectFiles = stringCreate(oFileListProject);

            for (int j = 0; j < listLength(mockFiles); j++)
            {
                char *mockName = listGet(mockFiles, j);
                char *token = stringCreate(NULL);
                int c;

                for (int k = 0; k < strlen(projectFiles); k++)
                {
                    c = projectFiles[k];

                    if (isspace(c))
                    {
                        char *name = getFileNameWithPathSplit(token);

                        if (name != NULL && strcmp(name, mockName) == 0)
                        {
                            projectFiles = stringReplace(projectFiles, token, "");
                        }

                        token = stringClear(token);

                        free(name);
                    }
                    else
                    {
                        token = stringAdd(token, c);
                    }
                }
                free(mockName);
                free(token);
            }

            listFiles = stringCat(listFiles, projectFiles);

            char *testName = getFileNameWithPath(testFile);
            testName = utilGetName(testName);

            char *binDirPathTemp = stringCreate(binDirPath);
            directoryCreate(binDirPathTemp, "separate");
            binDirPathTemp = stringCat(binDirPathTemp, "/separate");

            linkTest(binDirPathTemp, listFiles, builderFilePath, testName);

            free(testFile);
            free(listFiles);
            listFree(mockFiles);
            free(projectFiles);
            free(testName);
            free(binDirPathTemp);
        }

        free(testOFiles);
        listFree(tests);
        listFree(mockList);
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
