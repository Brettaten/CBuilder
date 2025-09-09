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

    directoryFree(dirTarget);

    Directory *dirSrc = directoryGetSub(dir, "src");

    if (dirSrc == NULL)
    {
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirSrc, "main", TYPE_DIRECTORY) || !directoryIsEntry(dirSrc, "test", TYPE_DIRECTORY))
    {
        directoryFree(dirSrc);
        return false;
    }

    Directory *dirMain = directoryGetSub(dirSrc, "main");

    if (dirMain == NULL)
    {
        directoryFree(dirSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirMain, "c", TYPE_DIRECTORY) || !directoryIsEntry(dirMain, "ressources", TYPE_DIRECTORY))
    {
        directoryFree(dirSrc);
        directoryFree(dirMain);
        return false;
    }

    directoryFree(dirMain);

    Directory *dirTest = directoryGetSub(dirSrc, "test");

    if (dirTest == NULL)
    {
        directoryFree(dirSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTest, "bin", TYPE_DIRECTORY) || !directoryIsEntry(dirTest, "src", TYPE_DIRECTORY) || !directoryIsEntry(dirTest, "target", TYPE_DIRECTORY))
    {
        directoryFree(dirSrc);
        directoryFree(dirTest);
        return false;
    }

    directoryFree(dirSrc);

    Directory *dirTestSrc = directoryGetSub(dirTest, "src");

    if (dirTestSrc == NULL)
    {
        directoryFree(dirTest);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTestSrc, "main", TYPE_DIRECTORY) || !directoryIsEntry(dirTestSrc, "project", TYPE_DIRECTORY))
    {
        directoryFree(dirTest);
        directoryFree(dirTestSrc);
        return false;
    }

    Directory *dirTestMain = directoryGetSub(dirTestSrc, "main");

    if (dirTestMain == NULL)
    {
        directoryFree(dirTest);
        directoryFree(dirTestSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTestMain, "c", TYPE_DIRECTORY) || !directoryIsEntry(dirTestMain, "genTests", TYPE_DIRECTORY))
    {
        directoryFree(dirTestMain);
        directoryFree(dirTest);
        directoryFree(dirTestSrc);
        return false;
    }

    directoryFree(dirTestMain);
    directoryFree(dirTestSrc);

    Directory *dirTestTarget = directoryGetSub(dirTest, "target");

    if (dirTestTarget == NULL)
    {
        directoryFree(dirTest);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTestTarget, "project", TYPE_DIRECTORY) || !directoryIsEntry(dirTestTarget, "test", TYPE_DIRECTORY))
    {
        directoryFree(dirTestTarget);
        directoryFree(dirTest);
        return false;
    }

    directoryFree(dirTest);
    directoryFree(dirTestTarget);

    return true;
}
