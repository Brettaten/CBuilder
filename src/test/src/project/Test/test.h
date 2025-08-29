#include "../Directory/directory.h"
#include "../Util/List/list.h"

/**
 * Function used to split the source file into multiple sub files which each contain just one function
 * 
 * @param src the source file
 * @param dest the directory where the sub files should be stored
 * 
 * @return a list of the created file names
 */
List *splitFile(Entry *src, Directory *dest);

/**
 * Function used to copy the project to the test directory and split the c files
 * 
 * @param destPath the destPath
 * @param srcPath the srcPath
 */
void copyProject(char *destPath, char *srcPath);

/**
 * Function used to generate a main function for each test file
 * 
 * @param destPath the destPath
 * @param srcPath the srcPath
 */
void generateTests(char *destPath, char *srcPath);
