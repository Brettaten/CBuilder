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


























void clear(char *path)
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
        char prodPath[MAX_LENGTH_PATH];
        char debugPath[MAX_LENGTH_PATH];

        strcpy(prodPath, projectPath);
        strcpy(debugPath, projectPath);
        strcat(prodPath, "/target/prod");
        strcat(debugPath, "/target/debug");

        Directory *targetProd = directoryGet(prodPath);

        if (targetProd == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *targetDebug = directoryGet(debugPath);

        if (targetDebug == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        int fileCounterProd = directoryClear(targetProd);
        int fileCounterDebug = directoryClear(targetDebug);

        if (fileCounterProd == -1 || fileCounterDebug == -1)
        {
            printf("[ERROR] : Function directoryClear was not able to clear the directory | clear \n");
            return;
        }

        directoryFree(targetProd);
        directoryFree(targetDebug);

        char fileCounterProdC[16];
        char fileCounterDebugC[16];
        sprintf(fileCounterProdC, "%d", fileCounterProd);
        sprintf(fileCounterDebugC, "%d", fileCounterDebug);

        printf(SEPERATOR);
        printf(HEADING, "S U C C E S S");
        printf(LINE, "Files deleted in prod:", fileCounterProdC);
        printf(LINE, "Files deleted in debug:", fileCounterDebugC);
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
