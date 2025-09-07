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










void directoryNormalizePath(char *dest, char *src)
{
    char absPath[MAX_LENGTH_PATH];
    _fullpath(absPath, src, sizeof(absPath));

    int length = strlen(absPath);

    if (absPath[length - 1] == '\\' || absPath[length - 1] == '/')
    {
        absPath[length - 1] = '\0';
        length--;
    }

    char terminator = '/';

    for (int i = 0; i < length; i++)
    {
        if (absPath[i] == '\\')
        {
            absPath[i] = '/';
        }
    }

    strcpy(dest, absPath);
}
#elif defined(LINUX)
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
void directoryNormalizePath(char *dest, char *src)
{
    char absPath[MAX_LENGTH_PATH];
    realpath(src, absPath);

    int length = strlen(absPath);

    if (absPath[length - 1] == '\\' || absPath[length - 1] == '/')
    {
        absPath[length - 1] = '\0';
        length--;
    }

    char terminator = '/';

    for (int i = 0; i < length; i++)
    {
        if (absPath[i] == '\\')
        {
            absPath[i] = '/';
        }
    }

    strcpy(dest, absPath);
}
#elif defined(APPLE)
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <mach-o/dyld.h>
void directoryNormalizePath(char *dest, char *src)
{
    char absPath[MAX_LENGTH_PATH];
    char cwd[MAX_LENGTH_PATH];

    if (src[0] != '/')
    {
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, src);
    }
    else
    {
        strcpy(cwd, src);
    }
    realpath(cwd, absPath);

    int length = strlen(absPath);

    if (absPath[length - 1] == '\\' || absPath[length - 1] == '/')
    {
        absPath[length - 1] = '\0';
        length--;
    }

    char terminator = '/';

    for (int i = 0; i < length; i++)
    {
        if (absPath[i] == '\\')
        {
            absPath[i] = '/';
        }
    }

    strcpy(dest, absPath);
}
#endif
