#include <stdlib.h>
#include <time.h>

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

#ifdef WIN

#include <windows.h>

Directory *directoryGet(char *path)
{
    int length = strlen(path);

    if (path[length - 1] == '\\' || path[length - 1] == '/')
    {
        path[length - 1] = '\0';
        length--;
    }

    char terminator = '/';

    for (int i = 0; i < length; i++)
    {
        if (path[i] == '\\')
        {
            terminator = '\\';
            return;
        }
        else if (path[i] == '/')
        {
            terminator == '/';
            return;
        }
    }

    char pathEx[length + 2];
    strcpy(pathEx, path);

    char suffix[2];
    if (terminator = '/')
    {
        strcpy(suffix, "/*");
    }
    else
    {
        strcpy(suffix, "\\*");
    }

    strcat(pathEx, suffix);

    WIN32_FIND_DATAW findFileData;
    HANDLE handle;

    handle = FindFirstFileW(pathEx, &findFileData);

    if (handle == INVALID_HANDLE_VALUE)
    {
        printf("[ERROR] : Directory specified in the passed path could not be found | directoryGet");
        return NULL;
    }
}

#elif UNIX

#include "dirent.h"

Directory *directoryGet(char *path)
{
    DIR
}

#endif

char *directoryGetPath(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetPath");
        return NULL;
    }

    return dir->path;
}

char *directoryGetName(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetName");
        return NULL;
    }

    return dir->name;
}

int directoryGetEntryAmount(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetEntryAmount");
        return -1;
    }

    return dir->entryAmount;
}

Entry *directoryGetEntry(Directory *dir, char *name, int type)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetSubDir");
        return NULL;
    }

    for (int i = 0; i < dir->entryAmount; i++)
    {
        if (strcmp(dir->entries[i]->name, name) && dir->entries[i]->type == type)
        {

            Entry *newEntry = (Entry *)malloc(sizeof(Entry));

            if (newEntry == NULL)
            {
                printf("[ERROR] : Memory allocation failed | directoryGetEntry");
                return NULL;
            }

            memcpy_s(newEntry, sizeof(Entry), dir->entries[i], sizeof(Entry));

            return newEntry;
        }
    }

    return NULL;
}

Directory *directoryGetParent(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetSub");
        return NULL;
    }

    char *path = dir->path;
    int length = strlen(path);
    int index = 0;

    for(int i = length - 1; i >= 0; i--){
        if(path[i] == '/'){
            index = i;
        }
    }

    if(index == 0){
        return NULL;
    }

    char pathParent[index + 1];

    for(int i = 0; i < index + 1; i++){
        pathParent[i] = path[i];
    }

    pathParent[index + 1] = '\0';

    Directory *dir = directoryGet(pathParent);

    if(dir == NULL){
        printf("[ERROR] : Parent directory does not exist | directoryGetParent");
        return NULL;
    }

    return dir;
}

Directory *directoryGetSub(Directory *dir, char *name)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | directoryGetSub");
        return NULL;
    }

    Entry *entry = directoryGetEntry(dir, name, DIRECTORY);

    if (entry == NULL)
    {
        printf("[ERROR] : Subdirectory with the passed name does not exist | directoryGetSub");
        return NULL;
    }

    char *path = entry->path;

    Directory *dir = directoryGet(path);

    if (dir == NULL)
    {
        entryFree(entry);
        printf("[ERROR] : Sub directory could not be found | directoryGetSub");
        return NULL;
    }

    entryFree(entry);

    return dir;
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
        printf("[ERROR] : Entry is null | entryGetPath");
        return NULL;
    }

    return entry->path;
}

char *entryGetName(Entry *entry)
{
    if (entry == NULL)
    {
        printf("[ERROR] : Entry is null | entryGetName");
        return NULL;
    }

    return entry->name;
}

int entryGetType(Entry *entry)
{
    if (entry == NULL)
    {
        printf("[ERROR] : Entry is null | entryGetType");
        return -1;
    }

    return entry->type;
}

time_t *entryGetLastModified(Entry *entry)
{
    if (entry == NULL)
    {
        printf("[ERROR] : Entry is null | entryGetLasModified");
        return NULL;
    }

    return entry->lastModified;
}

void *entryFree(Entry *entry)
{
    free(entry);
}
