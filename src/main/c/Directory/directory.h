#ifndef HEADERGUARDDIRCTORY
#define HEADERGUARDDIRCTORY
/**
 * Struct used to represent a platform independent directory
 */
typedef struct Directory Directory;

/**
 * Struct used to represent a platform independent directory entry/member
 */
typedef struct Entry Entry;

#define FILE 1
#define DIRECTORY 2

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
 * Function used to get a sub directory with the passed name
 * 
 * @param dir The directory
 * @param name The name of the potential sub directory
 * 
 * @return Success: A pointer to an entry struct if a sub directory was found | Failure: null
 * 
 * @note The returned entry is a deep copy and thus has to be freed by the caller
 */
Entry *directoryGetSubDir(Directory *dir, char *name);

/**
 * Function used to get a file with the passed name
 * 
 * @param dir The directory
 * @param name The name of the potential file
 * 
 * @return Success: A pointer to an entry struct if a file was found | Failure: null
 * 
 * @note The returned entry is a deep copy and thus has to be freed by the caller
 */
Entry *directoryGetFile(Directory *dir, char *name);

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
 * Function used to free a directory
 * 
 * @param dir The directory
 */
void directoryFree(Directory *dir);

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
time_t *entryGetLastModified(Entry *entry);

/**
 * Function used to free an entry
 * 
 * @param entry The entry
 */
void *entryFree(Entry *entry);

#endif

