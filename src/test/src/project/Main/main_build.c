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


 int x = 10;






















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

        char *binDirPath = stringCreate(entryGetPath(bin));

        Entry *builderFile = directoryGetEntry(dir, "cbuilderfile", TYPE_FILE);

        if (builderFile == NULL)
        {
            printf("[ERROR] : Entry for the specified directory was not found | build \n");
            return;
        }

        char builderFilePath[MAX_LENGTH_PATH];
        strcpy(builderFilePath, entryGetPath(builderFile));

        char relTarget[MAX_LENGTH_PATH];

        if (debug)
        {
            strcpy(relTarget, "/target/debug");
        }
        else
        {
            strcpy(relTarget, "/target/prod");
        }

        char srcPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcat(srcPath, "/src/main/c");

        char targetPath[MAX_LENGTH_PATH];
        strcpy(targetPath, projectPath);
        strcat(targetPath, relTarget);

        int fileCounter = 0;
        int alteredFiles = 0;

        char *oFileList = compile(targetPath, srcPath, projectPath, true, &fileCounter, &alteredFiles);

        directoryFree(dir);
        entryFree(bin);
        entryFree(builderFile);

        char linkCommand[] = "link";
        char *linkSystemCommand = stringCreate(NULL);
        char *objFiles = "$OBJFILES";
        char *binPath = "$BINPATH";
        char *permission = stringCreate("chmod a+x ");

        permission = stringCat(permission, binDirPath);

        linkSystemCommand = getCommand(linkCommand, builderFilePath, linkSystemCommand);

        linkSystemCommand = stringReplace(linkSystemCommand, objFiles, oFileList);
        linkSystemCommand = stringReplace(linkSystemCommand, binPath, binDirPath);

        system(linkSystemCommand);

#ifdef LINUX
        system(permission);
#elif defined(APPLE)
        system(permission);
#endif

        free(linkSystemCommand);
        free(oFileList);
        free(binDirPath);
        free(permission);

        char fileCounterC[16];
        char alteredFileCounterC[16];
        sprintf(fileCounterC, "%d", fileCounter);
        sprintf(alteredFileCounterC, "%d", alteredFiles);

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
