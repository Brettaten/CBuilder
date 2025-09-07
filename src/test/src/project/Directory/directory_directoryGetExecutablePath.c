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








int directoryGetExecutablePath(char *dest)
{
    char path[MAX_LENGTH_PATH];
    DWORD len = GetModuleFileNameA(NULL, path, MAX_LENGTH_PATH);
    if (len == 0)
    {
        printf("[ERROR] : Executable path could not be determined | directoryGetProjectPath \n");
        return -1;
    }
    char pathNorm[MAX_LENGTH_PATH];
    directoryNormalizePath(pathNorm, path);
    strcpy(dest, pathNorm);
    return 0;
}
#elif defined(LINUX)
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
int directoryGetExecutablePath(char *dest)
{
    char path[MAX_LENGTH_PATH];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1)
    {
        printf("[ERROR] : Executable path could not be determined | directoryGetProjectPath \n");
        return -1;
    }
    char pathNorm[MAX_LENGTH_PATH];
    directoryNormalizePath(pathNorm, path);
    strcpy(dest, pathNorm);
    return 0;
}
#elif defined(APPLE)
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <mach-o/dyld.h>
int directoryGetExecutablePath(char *dest)
{
    char path[MAX_LENGTH_PATH];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0)
    {
        printf("[ERROR] : Executable path could not be determined | directoryGetProjectPath \n");
        return -1;
    }
    char pathNorm[MAX_LENGTH_PATH];
    directoryNormalizePath(pathNorm, path);
    strcpy(dest, pathNorm);
    return 0;
}
#endif
