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

Directory *directoryGet(char *path)
{
    char absPath[MAX_LENGTH_PATH];
    directoryNormalizePath(absPath, path);

    char dirPath[MAX_LENGTH_PATH];
    char dirName[MAX_LENGTH_NAME];

    strcpy(dirPath, absPath);

    int nameLength = 0;

    for (int i = strlen(absPath) - 1; i >= 0; i--)
    {
        if (absPath[i] != '/')
        {
            nameLength++;
        }
        else
        {
            break;
        }
    }

    for (int i = strlen(absPath) - nameLength, j = 0; i < strlen(absPath); i++, j++)
    {
        dirName[j] = absPath[i];
    }

    dirName[nameLength] = '\0';

    DIR *dirUnix = opendir(absPath);

    if (dirUnix == NULL)
    {
        printf("[ERROR] : Directory specified in the passed path could not be found | directoryGet \n");
        return NULL;
    }

    Directory *dir = (Directory *)malloc(sizeof(Directory));

    if (dir == NULL)
    {
        printf("[ERROR] : Memory allocation failed | create \n");
        return NULL;
    }

    int entryAmount = utilGetEntryAmount(absPath);
    Entry **entries = (Entry **)malloc(sizeof(Entry *) * entryAmount);

    dir->entryAmount = entryAmount;
    dir->entries = entries;
    strcpy(dir->path, dirPath);
    strcpy(dir->name, dirName);

    struct dirent *dirent;
    int counter = 0;

    while ((dirent = readdir(dirUnix)) != NULL)
    {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
        {
        }
        else
        {
            Entry *entry = (Entry *)malloc(sizeof(Entry));

            if (entry == NULL)
            {
                dir->entryAmount = counter;
                directoryFree(dir);
                printf("[ERROR] : Memory allocation failed : create \n");
                return NULL;
            }

            strcpy(entry->name, dirent->d_name);

            char entryPath[MAX_LENGTH_PATH];
            strcpy(entryPath, dir->path);
            strcat(entryPath, "/");
            strcat(entryPath, entry->name);
            strcpy(entry->path, entryPath);

            struct stat statbuf;
            if (stat(entry->path, &statbuf) != 0)
            {
                dir->entryAmount = counter;
                directoryFree(dir);
                printf("[ERROR] : Can not access stats for entry at path %s | directoryGet", entry->path);
                return NULL;
            }

            if (S_ISDIR(statbuf.st_mode))
            {
                entry->type = TYPE_DIRECTORY;
            }
            else
            {
                entry->type = TYPE_FILE;
            }

            entry->lastModified = statbuf.st_mtime;

            dir->entries[counter] = entry;

            counter++;
        }
    }

    closedir(dirUnix);

    return dir;
}
#endif
