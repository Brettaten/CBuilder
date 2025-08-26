#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "directory.h"
#include "../Util/os.h"
#include "../Util/Stack/stack.h"

typedef struct Directory
{
    char path[MAX_LENGTH_PATH];
    char name[MAX_LENGTH_NAME];

    int entryAmount;
    Entry **entries;
} Directory;

typedef struct Entry
{
    char path[MAX_LENGTH_PATH];
    char name[MAX_LENGTH_NAME];
    int type;
    time_t lastModified;
} Entry;

/**
 * Util function to get the amount of entries in a directory so that this number can
 * be used to create an array that fits all entries
 *
 * @param dir The directory
 *
 * @return Success: the amount of entries in the passed dir | Failure: -1
 */
int utilGetEntryAmount(char *path);

#ifdef WIN

#include <windows.h>
#include <direct.h>

/**
 * Util function used to convert windows file time to unix time
 *
 * @param ft The file time
 *
 * @return unix time
 */
time_t utilFileTimeToUnix(FILETIME ft);















#elif defined(LINUX)

#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>













#elif defined(APPLE)

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <mach-o/dyld.h>













#endif













Directory *directoryGetParent(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetSub \n");
        return NULL;
    }

    char *path = dir->path;
    int length = strlen(path);
    int index = 0;

    for (int i = length - 1; i >= 0; i--)
    {
        if (path[i] == '/')
        {
            index = i;
            break;
        }
    }

    if (index == 0)
    {
        return NULL;
    }

    char pathParent[index + 1];

    for (int i = 0; i < index + 1; i++)
    {
        pathParent[i] = path[i];
    }

    pathParent[index + 1] = '\0';

    Directory *dirParent = directoryGet(pathParent);

    if (dirParent == NULL)
    {
        printf("[ERROR] : Parent directory does not exist | directoryGetParent \n");
        return NULL;
    }

    return dirParent;
}