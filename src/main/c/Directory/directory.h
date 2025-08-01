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

Directory *directoryGet(char *path);

#endif

