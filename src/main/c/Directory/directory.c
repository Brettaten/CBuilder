#include <time.h>

#include "directory.h"
#include "../Util/os.h"

typedef struct Directory
{
    char *path;
    char *name;

    int entryAmount;
    Entry *entries;
} Directory;

typedef struct Entry
{
    char *path;
    char *name;
    char *type;
    time_t *lastModified;
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