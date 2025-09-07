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




















































void linkTest(char *destPath, char *files, char *builderFilePath, char *name)
{
    char *path = stringCreate(destPath);
    path = stringCat(path, "/temp.txt");
    FILE *file = fopen(path, "w");
    int c;

    for (int i = 0; i < strlen(files); i++)
    {
        c = files[i];

        putc(c, file);
    }

    char responseFile[4096];
    strcpy(responseFile, "@");
    strcat(responseFile, path);

    fclose(file);

    char linkCommand[] = "linkTest";
    char *linkSystemCommand = stringCreate(NULL);
    char *objFiles = "$OBJFILES";
    char *binPath = "$BINPATH";
    char *permission = stringCreate("chmod a+x ");

    permission = stringCat(permission, destPath);

    linkSystemCommand = getCommand(linkCommand, builderFilePath, linkSystemCommand);

    destPath = stringCat(destPath, "/");
    destPath = stringCat(destPath, name);

    linkSystemCommand = stringReplace(linkSystemCommand, objFiles, responseFile);
    linkSystemCommand = stringReplace(linkSystemCommand, binPath, destPath);

    system(linkSystemCommand);

#ifdef LINUX
    system(permission);
#elif defined(APPLE)
    system(permission);
#endif

    remove(path);

    free(linkSystemCommand);
    free(permission);
    free(path);
}
