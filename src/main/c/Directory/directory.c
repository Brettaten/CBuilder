#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "directory.h"
#include "../Util/os.h"

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

Directory *directoryGet(char *path)
{
    char absPath[MAX_LENGTH_PATH];
    directoryNormalizePath(absPath, path);

    int length = strlen(absPath);
    char pathEx[length + 2];
    strcpy(pathEx, absPath);

    char *suffix = "/*";
    char dirPath[MAX_LENGTH_PATH];
    char dirName[MAX_LENGTH_NAME];

    strcat(pathEx, suffix);
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

    WIN32_FIND_DATAA findFileData;
    HANDLE handle;

    handle = FindFirstFileA(pathEx, &findFileData);

    if (handle == INVALID_HANDLE_VALUE)
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

    int entryAmount = utilGetEntryAmount(pathEx);
    Entry **entries = (Entry **)malloc(sizeof(Entry *) * entryAmount);

    dir->entryAmount = entryAmount;
    dir->entries = entries;
    strcpy(dir->path, dirPath);
    strcpy(dir->name, dirName);

    int counter = 0;

    while (&findFileData != NULL)
    {
        if (strcmp(findFileData.cFileName, ".") == 0 || strcmp(findFileData.cFileName, "..") == 0)
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

            strcpy(entry->name, findFileData.cFileName);

            char entryPath[MAX_LENGTH_PATH];
            strcpy(entryPath, dir->path);
            strcat(entryPath, "/");
            strcat(entryPath, entry->name);
            strcpy(entry->path, entryPath);

            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                entry->type = TYPE_DIRECTORY;
            }
            else
            {
                entry->type = TYPE_FILE;
            }

            entry->lastModified = utilFileTimeToUnix(findFileData.ftLastWriteTime);

            dir->entries[counter] = entry;

            counter++;
        }

        WINBOOL st1 = FindNextFileA(handle, &findFileData);

        if (st1 == false)
        {
            break;
        }
    }

    FindClose(handle);

    return dir;
}

bool directoryCreate(char *directoryPath, char *directoryName)
{
    char absPath[MAX_LENGTH_PATH];
    directoryNormalizePath(absPath, directoryPath);
    strcat(absPath, "/");
    strcat(absPath, directoryName);

    if (!CreateDirectoryA(absPath, NULL))
    {
        DWORD err = GetLastError();
        if (err != ERROR_ALREADY_EXISTS)
        {
            printf("[ERROR] : Directory %s could not be created | directoryCreate \n", absPath);
            return false;
        }
    }
    return true;
}

int directoryGetExecutablePath(char *dest){
    char path[MAX_LENGTH_PATH];
    DWORD len = GetModuleFileNameA(NULL, path, MAX_LENGTH_PATH);
    if (len == 0) {
        printf("[ERROR] : Executable path could not be determined | directoryGetProjectPath \n");
        return -1;
    } 
    char pathNorm[MAX_LENGTH_PATH];
    directoryNormalizePath(pathNorm, path);
    strcpy(dest, pathNorm);
    return 0;
}

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

int utilGetEntryAmount(char *path)
{
    if (path == NULL)
    {
        printf("[ERROR] : Directory is null : utilGetEntryAmount");
        return -1;
    }

    WIN32_FIND_DATAA findFileData;
    HANDLE handle;

    handle = FindFirstFileA(path, &findFileData);

    if (handle == INVALID_HANDLE_VALUE)
    {
        printf("[ERROR] : Directory specified in the passed path could not be found | utilGetEntryAmount \n");
        return -1;
    }

    int counter = 0;

    while (&findFileData != NULL)
    {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0)
        {
            counter++;
        }

        WINBOOL st1 = FindNextFileA(handle, &findFileData);

        if (st1 == false)
        {
            break;
        }
    }
    FindClose(handle);
    return counter;
}

time_t utilFileTimeToUnix(FILETIME ft)
{
    ULARGE_INTEGER ull;
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;

    ull.QuadPart -= 116444736000000000ULL;

    return (time_t)(ull.QuadPart / 10000000ULL);
}

#elif defined(LINUX)

#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

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

bool directoryCreate(char *directoryPath, char *directoryName)
{
    char absPath[MAX_LENGTH_PATH];
    directoryNormalizePath(absPath, directoryPath);
    strcat(absPath, "/");
    strcat(absPath, directoryName);

    if (mkdir(absPath, 0777) != 0 && errno != EEXIST)
    {
        printf("[ERROR] : Directory %s could not be created | directoryCreate \n", absPath);
        return false;
    }

    return true;
}

int directoryGetExecutablePath(char *dest){
    char path[MAX_LENGTH_PATH];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path)-1);
    if (len == -1) {
        printf("[ERROR] : Executable path could not be determined | directoryGetProjectPath \n");
        return -1;
    } 
    char pathNorm[MAX_LENGTH_PATH];
    directoryNormalizePath(pathNorm, path);
    strcpy(dest, pathNorm);
    return 0;
}

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

int utilGetEntryAmount(char *path)
{
    if (path == NULL)
    {
        printf("[ERROR] : Directory is null : utilGetEntryAmount");
        return -1;
    }

    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        printf("[ERROR] : Directory specified in the passed path could not be found | utilGetEntryAmount \n");
        return -1;
    }

    struct dirent *dirent;
    int counter = 0;

    while ((dirent = readdir(dir)) != NULL)
    {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
        {
            counter++;
        }
    }
    closedir(dir);
    return counter;
}

#elif defined(APPLE)

#endif

char *directoryGetPath(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetPath \n");
        return NULL;
    }

    return dir->path;
}

char *directoryGetName(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetName \n");
        return NULL;
    }

    return dir->name;
}

int directoryGetEntryAmount(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetEntryAmount \n");
        return -1;
    }

    return dir->entryAmount;
}

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

bool directoryIsEntry(Directory *dir, char *name, int type)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetSubDir \n");
        return false;
    }

    for (int i = 0; i < dir->entryAmount; i++)
    {
        if (strcmp(dir->entries[i]->name, name) == 0 && dir->entries[i]->type == type)
        {
            return true;
        }
    }

    return false;
}

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

Directory *directoryGetSub(Directory *dir, char *name)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetSub \n");
        return NULL;
    }

    Entry *entry = directoryGetEntry(dir, name, TYPE_DIRECTORY);

    if (entry == NULL)
    {
        printf("[ERROR] : Subdirectory with the passed name does not exist | directoryGetSub \n");
        return NULL;
    }

    char *path = entry->path;

    Directory *dirSub = directoryGet(path);

    if (dirSub == NULL)
    {
        entryFree(entry);
        printf("[ERROR] : Sub directory could not be found | directoryGetSub \n");
        return NULL;
    }

    entryFree(entry);

    return dirSub;
}

void directoryFree(Directory *dir)
{
    for (int i = 0; i < dir->entryAmount; i++)
    {
        entryFree(dir->entries[i]);
    }
    free(dir->entries);
    free(dir);
}

char *entryGetPath(Entry *entry)
{
    if (entry == NULL)
    {
        printf("[ERROR] : Entry is null | entryGetPath \n");
        return NULL;
    }

    return entry->path;
}

char *entryGetName(Entry *entry)
{
    if (entry == NULL)
    {
        printf("[ERROR] : Entry is null | entryGetName \n");
        return NULL;
    }

    return entry->name;
}

int entryGetType(Entry *entry)
{
    if (entry == NULL)
    {
        printf("[ERROR] : Entry is null | entryGetType \n");
        return -1;
    }

    return entry->type;
}

time_t entryGetLastModified(Entry *entry)
{
    if (entry == NULL)
    {
        printf("[ERROR] : Entry is null | entryGetLasModified \n");
        return (time_t)-1;
    }

    return entry->lastModified;
}

void entryFree(Entry *entry)
{
    free(entry);
}

bool fileCreate(char *path, char *fileName)
{
    char absPath[MAX_LENGTH_NAME];
    directoryNormalizePath(absPath, path);
    strcat(absPath, "/");
    strcat(absPath, fileName);

    FILE *file = fopen(absPath, "w");

    if (file == NULL)
    {
        printf("[ERROR] : File %s could not be created | fileCreate \n", absPath);
        return false;
    }

    fclose(file);
    return true;
}

bool fileCopy(char *destPath, char *destName, char *srcPath, char *srcName)
{
    char absPathDest[MAX_LENGTH_NAME];
    directoryNormalizePath(absPathDest, destPath);
    strcat(absPathDest, "/");
    strcat(absPathDest, destName);

    char absPathSrc[MAX_LENGTH_NAME];
    directoryNormalizePath(absPathSrc, srcPath);
    strcat(absPathSrc, "/");
    strcat(absPathSrc, srcName);

    FILE *dest = fopen(absPathDest, "w");
    FILE *src = fopen(absPathSrc, "r");

    if (dest == NULL || src == NULL)
    {
        printf("[ERROR] : File %s could not be copied to %s| fileCopy \n", absPathSrc, absPathDest);
        return false;
    }

    int c; 

    while ((c = getc(src)) != EOF)
    {
        putc(c, dest);
    }

    fclose(dest);
    fclose(src);

    return true;
}
