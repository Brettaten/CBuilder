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

















int directoryClear(Directory *dir)
{
    Stack *stack = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

    if (stack == NULL)
    {
        printf("[ERROR] : Function stackCreate failed | directoryClear \n");
        return -1;
    }

    int st1 = stackPush(stack, dir);

    if (st1 == -1)
    {
        printf("[ERROR] : Function stackPush failed | directoryClear \n");
        return -1;
    }

    int fileCounter = 0;

    while (stackLength(stack) > 0)
    {
        Directory *temp = stackPop(stack);

        char dirPath[MAX_LENGTH_PATH];
        strcpy(dirPath, directoryGetPath(temp));

        directoryFree(temp);
        temp = directoryGet(dirPath);
        stackPush(stack, temp);

        if (temp == NULL)
        {
            printf("[ERROR] : Function stackPop failed | directoryClear \n");
            return -1;
        }

        if (directoryGetEntryAmount(temp) == 0)
        {
            if (stackLength(stack) != 1)
            {
                int st1 = directoryDelete(directoryGetPath(temp));

                if (st1 == -1)
                {
                    printf("[ERROR] : Function directoryDelete failed | directoryClear \n");
                    return -1;
                }
            }
            stackPop(stack);
        }

        for (int i = 0; i < directoryGetEntryAmount(temp); i++)
        {
            Entry *tempEntry = directoryGetEntryAt(temp, i);

            if (tempEntry == NULL)
            {
                printf("[ERROR] : Function directoryGetEntryAt failed | directoryClear \n");
                return -1;
            }

            if (entryGetType(tempEntry) == TYPE_DIRECTORY)
            {
                Directory *newDir = directoryGet(entryGetPath(tempEntry));

                if (newDir == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | directoryClear \n");
                    return -1;
                }

                stackPush(stack, newDir);

                directoryFree(newDir);
            }

            else
            {
                fileCounter++;

                int st2 = remove(entryGetPath(tempEntry));

                if (st2 != 0)
                {
                    printf("[ERROR] : Function remove failed | directoryClear \n");
                    return -1;
                }
            }

            entryFree(tempEntry);
        }
        directoryFree(temp);
    }
    stackFree(stack);

    return fileCounter;
}