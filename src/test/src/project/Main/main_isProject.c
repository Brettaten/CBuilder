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






























bool isProject(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dir, "cbuilderfile", TYPE_FILE) || !directoryIsEntry(dir, "bin", TYPE_DIRECTORY) || !directoryIsEntry(dir, "src", TYPE_DIRECTORY) || !directoryIsEntry(dir, "target", TYPE_DIRECTORY))
    {
        return false;
    }

    Directory *dirTarget = directoryGetSub(dir, "target");

    if (dirTarget == NULL)
    {
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTarget, "prod", TYPE_DIRECTORY) || !directoryIsEntry(dirTarget, "debug", TYPE_DIRECTORY))
    {
        directoryFree(dirTarget);
        return false;
    }

    Directory *dirSrc = directoryGetSub(dir, "src");

    if (dirSrc == NULL)
    {
        directoryFree(dirTarget);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirSrc, "main", TYPE_DIRECTORY) || !directoryIsEntry(dirSrc, "test", TYPE_DIRECTORY))
    {
        directoryFree(dirTarget);
        directoryFree(dirSrc);
        return false;
    }

    Directory *dirMain = directoryGetSub(dirSrc, "main");

    if (dirMain == NULL)
    {
        directoryFree(dirTarget);
        directoryFree(dirSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirMain, "c", TYPE_DIRECTORY) || !directoryIsEntry(dirMain, "ressources", TYPE_DIRECTORY))
    {
        directoryFree(dirTarget);
        directoryFree(dirSrc);
        directoryFree(dirMain);
        return false;
    }

    directoryFree(dirTarget);
    directoryFree(dirSrc);
    directoryFree(dirMain);

    return true;
}
