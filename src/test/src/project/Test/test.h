#include "../Directory/directory.h"

/**
 * Function used to split the source file into multiple sub files which each contain just one function
 * 
 * @param src the source file
 * @param dest the directory where the sub files should be stored
 * 
 * @return Success: 0 | Failure: -1
 */
int splitFile(Entry *src, Directory *dest);
