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
 * Function used to display information about the command build
 */
void printHelpBuild();

/**
 * Function used to display information about the command execute
 */
void printHelpClear();

/**
 * Function that displays some help after the user entered a wrong command
 */
void printInvalidCMD();

/**
 * Function that displays the user's version of cbuilder
 */
void printVersion();

/**
 * Function that displays an error if no project was found
 */
void printNoProjectFound();

/**
 * Function that executes the cbuilder create -p command
 * 
 * @param path The path were the cbuilder project should be created
 */
void create(char *path);

/**
 * Function that executes the cbuilder build -p -d command
 * 
 * @param path The path were cbuilder should look for a project
 * @param debug Specifies whether debug information should be added or not
 */
void build(char *path, bool debug);

/**
 * Function that executes the cbuilder clear -p command
 * 
 * @param path The path were cbuilder should look for a project
 */
void clear(char *path);

/**
 * Function that executes the cbuilder create -p command
 * 
 * @param path The path were the cbuilder project should be created
 */
void create(char *path);

/**
 * Function used to get a command from the cbuilderfile
 * 
 * @param command The name of the command
 * @param path The path were to look for the project
 * @param destPrefix The destination of the prefix
 * @param destSuffix destSuffix
 * 
 * @return Success: 0 | Failure: -1
 */
int getCommand(char *command, char *path, char *destPrefix, char *destSuffix);
/**
 * Function that checks if a CBuilder project exists in a passed directory
 * 
 * @param dir The directory where the CBuilder project might be located
 * 
 * @return true, if there is a CBuilder project and false if it is not
 */
bool isProject(Directory *dir);

/**
 * Function used to find the path of a cbuilder project
 * 
 * @param path The initial path
 * @param dest The project path
 * 
 * @return Success: 0 | Failure: -1
 */
int findProject(char *path, char *dest);

/**
 * Function used to get the ressource directory of this cbuilder project
 * 
 * @return Success: The directory | Failure: NULL
 */
Directory *getRessourceDirectory();

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