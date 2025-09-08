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






























void testClear(char *path)
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
        char targetProjectPath[MAX_LENGTH_PATH];
        char targetTestPath[MAX_LENGTH_PATH];
        char testProjectPath[MAX_LENGTH_PATH];
        char genTestPath[MAX_LENGTH_PATH];

        strcpy(targetProjectPath, projectPath);
        strcat(targetProjectPath, "/src/test/target/project");

        strcpy(targetTestPath, projectPath);
        strcat(targetTestPath, "/src/test/target/test");

        strcpy(testProjectPath, projectPath);
        strcat(testProjectPath, "/src/test/src/project");

        strcpy(genTestPath, projectPath);
        strcat(genTestPath, "/src/test/src/main/genTests");

        Directory *targetProjectPathDir = directoryGet(targetProjectPath);

        if (targetProjectPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *targetTestPathDir = directoryGet(targetTestPath);

        if (targetTestPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *testProjectPathDir = directoryGet(testProjectPath);

        if (testProjectPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *genTestPathDir = directoryGet(genTestPath);

        if (genTestPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        int st1 = directoryClear(targetProjectPathDir);
        int st2 = directoryClear(targetTestPathDir);
        int st3 = directoryClear(testProjectPathDir);
        int st4 = directoryClear(genTestPathDir);

        if (st1 == -1 || st2 == -1 || st3 == -1 || st4 == -1)
        {
            printf("[ERROR] : Function directoryClear was not able to clear the directory | clear \n");
            return;
        }

        directoryFree(targetProjectPathDir);
        directoryFree(targetTestPathDir);
        directoryFree(testProjectPathDir);
        directoryFree(genTestPathDir);

        char st1C[16];
        char st2C[16];
        char st3C[16];
        char st4C[16];

        sprintf(st1C, "%d", st1);
        sprintf(st2C, "%d", st2);
        sprintf(st3C, "%d", st3);
        sprintf(st4C, "%d", st4);

        printf(SEPERATOR);
        printf(HEADING, "S U C C E S S");
        printf(LINE, "Files deleted in target/project:", st1C);
        printf(LINE, "Files deleted in target/test:", st2C);
        printf(LINE, "Files deleted in src/project:", st3C);
        printf(LINE, "Files deleted in main/genTests:", st4C);
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
