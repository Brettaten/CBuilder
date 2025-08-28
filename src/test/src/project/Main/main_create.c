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
        strcpy(pathBuilderfileDest, path);
        strcpy(pathBuilderfileDest, "/cbuilderfile");

        char pathBuilderfileSrc[MAX_LENGTH_PATH];
        strcpy(pathBuilderfileSrc, directoryGetPath(ressource));
        strcat(pathBuilderfileSrc, entryGetName(template));

        if (!directoryCreate(path, "bin") || !directoryCreate(path, "src") || !directoryCreate(path, "target") || !fileCreate(path, "cbuilderfile") || !fileCopy(pathBuilderfileDest, pathBuilderfileSrc))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTarget[MAX_LENGTH_PATH];
        strcpy(pathTarget, path);
        strcat(pathTarget, "/target");

        if (!directoryCreate(pathTarget, "prod") || !directoryCreate(pathTarget, "debug"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathSrc[MAX_LENGTH_PATH];
        strcpy(pathSrc, path);
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

        printf(SEPERATOR);
        printf(HEADING, "S U C E S S S");
        printf(LINE, "CBuilder project created at:", projectPath);
        printf(SEPERATOR);

        directoryFree(ressource);
        entryFree(template);
    }
}
