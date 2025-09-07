#include "../Directory/directory.h"
#include "../Util/List/list.h"

/**
 * Function used to split the source file into multiple sub files which each contain just one function
 * 
 * @param src the source file
 * @param dest the directory where the sub files should be stored
 */
void splitFile(Entry *src, Directory *dest);

/**
 * Function used to get the function names for every function in a c file
 * 
 * @param src the source file
 * 
 * @return a list of all function names
 */
List *getFileNames(Entry *src);

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
 * 
 * @return A list that contains the mock functions for each test file
 */
List *generateTests(char *destPath, char *srcPath);
