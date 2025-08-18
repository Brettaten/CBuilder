#ifndef HEADERGUARDDIRCTORY
#define HEADERGUARDDIRCTORY

#include <stdbool.h>
#include <time.h>

/**
 * Struct used to represent a platform independent directory
 */
typedef struct Directory Directory;

/**
 * Struct used to represent a platform independent directory entry/member
 */
typedef struct Entry Entry;

#define TYPE_FILE 1
#define TYPE_DIRECTORY 2

#define MAX_LENGTH_NAME 512
#define MAX_LENGTH_PATH 4096

/**
 * Function used to get the directory at the specified path
 * 
 * @param path The path to the directory
 * 
 * @return Success: A directory struct of this path | Failure: null
 * 
 * @note The returned directory has to be freed by the caller
 */
Directory *directoryGet(char *path);

/**
 * Function used to create a directory at the specified path
 * 
 * @param directoryPath the parent directory of the new directory
 * @param directoryName the name of the new directory
 * 
 * @return Success: true | Failure: false
 * 
 */
bool directoryCreate(char *directoryPath, char *directoryName);

/**
 * Function used to delete a dirctory at the specified path
 * 
 * @param directoryPath the path of the directory
 * 
 * @return Success: 0 | Failure: -1
 * 
 */
int directoryDelete(char *directoryPath);

/**
 * Function used to get the executable path
 * 
 * @param dest The path to the executable path
 * 
 * @return Success: 0 | Failure: -1
 */
int directoryGetExecutablePath(char *dest);

/**
 * Function used to normalize the passed path for later use
 *
 * @param dest the normalized path
 * @param src The path that should be normalized
 */
void directoryNormalizePath(char *dest, char *src);

/**
 * Function used to get the path of a directory 
 * 
 * @param dir The directory
 * 
 * @return Success: the path to the directory | Failure: null
 */
char *directoryGetPath(Directory *dir);

/**
 * Function used to get the name of a directory
 * 
 * @param dir The directory
 * 
 * @return Success: the name of the directory | Failure: null
 */
char *directoryGetName(Directory *dir);

/**
 * Function used to get the amount of entries in a directory
 * 
 * @param dir The directory
 * 
 * @return Success: the amount of entries in the directory | Failure: -1
 */
int directoryGetEntryAmount(Directory *dir);

/**
 * Function used to get a entry with the passed name and type
 * 
 * @param dir The directory
 * @param name The name of the potential sub directory
 * @param type The type of entry
 * 
 * @return Success: A pointer to an entry struct if a fitting entry was found | Failure: null
 * 
 * @note The returned entry is a deep copy and thus has to be freed by the caller
 */
Entry *directoryGetEntry(Directory *dir, char *name, int type);

/**
 * Function used to get a entry at the passed index
 * 
 * @param dir The directory
 * @param index the index
 * 
 * @return Success: A pointer to an entry struct | Failure: null
 * 
 * @note The returned entry is a deep copy and thus has to be freed by the caller
 */
Entry *directoryGetEntryAt(Directory *dir, int index);

/**
 * Function used to determine whether an entry exists in a directory or not
 * 
 * @param dir The directory
 * @param name The name of the potential sub directory
 * @param type The type of entry
 * 
 * @return Success: true | Failure: false
 */
bool directoryIsEntry(Directory *dir, char *name, int type);

/**
 * Function used to get the parent directory of the passed directory
 * 
 * @param dir The directory
 * 
 * @return Success: The parent directory if one exists | Failure: null
 * 
 * @note The returned directory has to be freed by the caller
 */
Directory *directoryGetParent(Directory *dir);

/**
 * Function used to get the sub directory with the specified name of the passed directory
 * 
 * @param dir The directory
 * @param name The name of the sub directory
 * 
 * @return Success: The sub directory if it exists | Failure: null
 * 
 * @note The returned directory has to be freed by the caller
 */
Directory *directoryGetSub(Directory *dir, char *name);

/**
 * Function used to delete all files and sub directories of the passed directory
 * 
 * @param dir the directory
 * 
 * @return Success: the amount of deleted files | Failure: -1
 */
int directoryClear(Directory *dir);

/**
 * Function used to get the size of a directory struct
 */
int directoryGetSize();

/**
 * Function used to free a directory
 * 
 * @param dir The directory
 */
void directoryFree(void *dir);

/**
 * Function used to copy a directory
 * 
 * @param dir the directory
 * 
 * @return Success: the copy of the directory | Failure: NULL
 */
void *directoryCopy(void *dir);

/**
 * Function used to get the path of an entry
 * 
 * @param entry The entry
 * 
 * @return Success: the path to the entry | Failure: null
 */
char *entryGetPath(Entry *entry);

/**
 * Function used to get the name of an entry
 * 
 * @param entry The entry
 * 
 * @return Success: then name of the entry | Failure: null
 */
char *entryGetName(Entry *entry);

/**
 * Function used to get the type of an entry
 * 
 * @param entry The entry
 * 
 * @return Success: A number that represents the entry type. Use the specified macros | Failure: -1
 */
int entryGetType(Entry *entry);

/**
 * Function used to get the time, where the entry was last modified
 * 
 * @param entry The entry
 * 
 * @return Success: The time, where the entry was last modified | Failure: null
 */
time_t entryGetLastModified(Entry *entry);

/**
 * Function used to free an entry
 * 
 * @param entry The entry
 */
void entryFree(void *entry);

/**
 * Function used to deep copy an entry
 * 
 * @param entry the entry
 * 
 * @return Success: the copied entry | Failure: NULL
 */
void *entryCopy(void *entry);

/**
 * Function used to create a file
 * 
 * @param path The directory of the file
 * @param fileName The name of the new file
 * 
 * @return Success: true | Failure: false
 */
bool fileCreate(char *path, char *fileName);

/**
 * Function used to copy one file to another
 * 
 * @param destPath The path to the destination file
 * @param destName The name of the destination file
 * @param srcPath The path to the source file
 * @param srcName The name of the source file
 * 
 * @return Success: true | Failure: false
 */
bool fileCopy(char *destPath, char *destName, char *srcPath, char *srcName);

#endif

