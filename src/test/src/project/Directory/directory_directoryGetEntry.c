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







Entry *directoryGetEntry(Directory *dir, char *name, int type)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetSubDir \n");
        return NULL;
    }

    for (int i = 0; i < dir->entryAmount; i++)
    {
        if (strcmp(dir->entries[i]->name, name) == 0 && dir->entries[i]->type == type)
        {

            Entry *newEntry = (Entry *)malloc(sizeof(Entry));

            if (newEntry == NULL)
            {
                printf("[ERROR] : Memory allocation failed | directoryGetEntry \n");
                return NULL;
            }

            memcpy(newEntry, dir->entries[i], sizeof(Entry));

            return newEntry;
        }
    }

    return NULL;
}