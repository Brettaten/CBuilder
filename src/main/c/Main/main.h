#include <stdbool.h>
#include "../Directory/directory.h"

// Header guard
#ifndef MAIN
#define MAIN

#define VERSION "1.0"

/**
 * Function used to display general commands on the console to help the user
 */
void printHelpGeneral();

/**
 * Function used to display information about the command create
 */
void printHelpCreate();

/**
 * Function that displays some help after the user entered a wrong command
 */
void printInvalidCMD();

/**
 * Function that displays the user's version of cbuilder
 */
void printVersion();

/**
 * Function that executes the cbuilder create -p command
 * 
 * @param path The path were the cbuilder project should be created
 */
void create(char *path);

/**
 * Function that checks if a CBuilder project exists in a passed directory
 * 
 * @param dir The directory where the CBuilder project might be located
 * 
 * @return true, if there is a CBuilder project and false if it is not
 */
bool isProject(Directory *dir);

/**
 * Function used to set all elements in an array to null
 * 
 * @param **p pointer to the list
 * @param length length of the list
 * 
 * @return Success: 0 | Failure: -1
 */
int setArrayToNull(void **p, int length);

/**
 * Function used to check if every element is != null
 * 
 * @param p pointer to the list
 * @param length length of the list
 * 
 * @return true, if atleast one element is == null | false, if every element is != null
 */
bool isNull(void **p, int length);

#endif