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

    for(int i = 0; i < length; i++){
        if(path[i] == '\\'){
            terminator = '\\';
            return;
        }
        else if(path[i] == '/'){
            terminator == '/';
            return;
        }
    }

    char pathEx[length + 2];
    strcpy(pathEx, path);

    char suffix[2];
    if(terminator = '/'){
        strcpy(suffix, "/*");
    }
    else{
        strcpy(suffix, "\\*");
    }

    strcat(pathEx, suffix);

    WIN32_FIND_DATAW findFileData;
    HANDLE handle;

    handle = FindFirstFileW(pathEx, &findFileData);

    if(handle == INVALID_HANDLE_VALUE){
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
    if(dir == NULL){
        printf("[ERROR] : Directory is null | directoryGetPath");
        return NULL;
    }

    return dir->path;
}

char *directoryGetName(Directory *dir)
{
    if(dir == NULL){
        printf("[ERROR] : Directory is null | directoryGetName");
        return NULL;
    }

    return dir->name;
}

int directoryGetEntryAmount(Directory *dir)
{
    if(dir == NULL){
        printf("[ERROR] : Directory is null | directoryGetEntryAmount");
        return -1;
    }

    return dir->entryAmount;
}

Entry *directoryGetSubDir(Directory *dir, char *name)
{
    return nullptr;
}

Entry *directoryGetFile(Directory *dir, char *name)
{
    return nullptr;
}

Directory *directoryGetParent(Directory *dir)
{
    return nullptr;
}

Directory *directoryGetSub(Directory *dir, char *name)
{
    return nullptr;
}

void directoryFree(Directory *dir)
{
    for(int i = 0; i < dir->entryAmount; i++){
        entryFree(dir->entries[i]);
    }
    free(dir->entries);
    free(dir);
}

char *entryGetPath(Entry *entry)
{
    if(entry == NULL){
        printf("[ERROR] : Entry is null | entryGetPath");
        return NULL;
    }

    return entry->path;
}

char *entryGetName(Entry *entry)
{
    if(entry == NULL){
        printf("[ERROR] : Entry is null | entryGetName");
        return NULL;
    }

    return entry->name;
}

int entryGetType(Entry *entry)
{
    if(entry == NULL){
        printf("[ERROR] : Entry is null | entryGetType");
        return -1;
    }

    return entry->type;
}

time_t *entryGetLastModified(Entry *entry)
{
    if(entry == NULL){
        printf("[ERROR] : Entry is null | entryGetLasModified");
        return NULL;
    }

    return entry->lastModified;
}

void *entryFree(Entry *entry)
{
    free(entry);
}
