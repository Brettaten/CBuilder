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






















void create(char *path)
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
        printf(SEPERATOR);
        printf(HEADING, "I N F O");
        printf(LINE, "A CBuilder project exists at:", projectPath);
        printf(SEPERATOR);
        return;
    }
    else
    {
        Directory *ressource = getRessourceDirectory();

        if (ressource == NULL)
        {
            printf("[ERROR] : Ressource directory was not found | create");
            return;
        }

        Entry *template = directoryGetEntry(ressource, "cbuilderfile", TYPE_FILE);

        if (template == NULL)
        {
            printf("[ERROR] : CBuilderfile template was not found | create");
        }

        char pathBuilderfileDest[MAX_LENGTH_PATH];
        strcpy(pathBuilderfileDest, projectPath);
        strcat(pathBuilderfileDest, "/cbuilderfile");

        char pathBuilderfileSrc[MAX_LENGTH_PATH];
        strcpy(pathBuilderfileSrc, directoryGetPath(ressource));
        strcat(pathBuilderfileSrc, "/");
        strcat(pathBuilderfileSrc, entryGetName(template));

        if (!directoryCreate(projectPath, "bin") || !directoryCreate(projectPath, "src") || !directoryCreate(projectPath, "target") || !fileCreate(projectPath, "cbuilderfile") || !fileCopy(pathBuilderfileDest, pathBuilderfileSrc))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTarget[MAX_LENGTH_PATH];
        strcpy(pathTarget, projectPath);
        strcat(pathTarget, "/target");

        if (!directoryCreate(pathTarget, "prod") || !directoryCreate(pathTarget, "debug"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathSrc[MAX_LENGTH_PATH];
        strcpy(pathSrc, projectPath);
        strcat(pathSrc, "/src");

        if (!directoryCreate(pathSrc, "main") || !directoryCreate(pathSrc, "test"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathMain[MAX_LENGTH_PATH];
        strcpy(pathMain, pathSrc);
        strcat(pathMain, "/main");

        if (!directoryCreate(pathMain, "c") || !directoryCreate(pathMain, "ressources"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTest[MAX_LENGTH_PATH];
        strcpy(pathTest, pathSrc);
        strcat(pathTest, "/test");

        if (!directoryCreate(pathTest, "bin") || !directoryCreate(pathTest, "src") || !directoryCreate(pathTest, "target"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestSrc[MAX_LENGTH_PATH];
        strcpy(pathTestSrc, pathTest);
        strcat(pathTestSrc, "/src");

        if (!directoryCreate(pathTestSrc, "main") || !directoryCreate(pathTestSrc, "project"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestMain[MAX_LENGTH_PATH];
        strcpy(pathTestMain, pathTestSrc);
        strcat(pathTestMain, "/main");

        if (!directoryCreate(pathTestMain, "c") || !directoryCreate(pathTestMain, "genTests"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestC[MAX_LENGTH_PATH];
        strcpy(pathTestC, pathTestMain);
        strcat(pathTestC, "/c");

        char pathTestUtilC[MAX_LENGTH_PATH];
        strcpy(pathTestUtilC, pathTestC);
        strcat(pathTestUtilC, "/util/cbuilderTest.c");

        char pathTestUtilH[MAX_LENGTH_PATH];
        strcpy(pathTestUtilH, pathTestC);
        strcat(pathTestUtilH, "/util/cbuilderTest.h");

        char pathRessourceUtilC[MAX_LENGTH_PATH];
        strcpy(pathRessourceUtilC, directoryGetPath(ressource));
        strcat(pathRessourceUtilC, "/util/cbuilderTest.c");

        char pathRessourceUtilH[MAX_LENGTH_PATH];
        strcpy(pathRessourceUtilH, directoryGetPath(ressource));
        strcat(pathRessourceUtilH, "/util/cbuilderTest.h");

        if (!directoryCreate(pathTestC, "util") || !fileCopy(pathTestUtilC, pathRessourceUtilC) || !fileCopy(pathTestUtilH, pathRessourceUtilH))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestTarget[MAX_LENGTH_PATH];
        strcpy(pathTestTarget, pathTest);
        strcat(pathTestTarget, "/target");

        if (!directoryCreate(pathTestTarget, "project") || !directoryCreate(pathTestTarget, "test"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        printf(SEPERATOR);
        printf(HEADING, "S U C E S S S");
        printf(LINE, "CBuilder project created at:", projectPath);
        printf(SEPERATOR);

        directoryFree(ressource);
        entryFree(template);
    }
}
