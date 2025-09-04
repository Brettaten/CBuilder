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
        char srcPath[MAX_LENGTH_PATH];
        char destPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/main/c");
        strcat(destPath, "/src/test/src/project");

        copyProject(destPath, srcPath);

        strcpy(srcPath, destPath);
        strcpy(destPath, projectPath);
        strcat(destPath, "/src/test/target/project");

        int fileCounter = 0;
        int alteredFiles = 0;

        char *oFileList = compile(destPath, srcPath, projectPath, true, &fileCounter, &alteredFiles);

        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/test/src/main/c");
        strcat(destPath, "/src/test/src/main/genTests");

        generateTests(destPath, srcPath);
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
