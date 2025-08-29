#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "main.h"
#include "../Util/os.h"
#include "../Util/display.h"
#include "../Util/List/list.h"
#include "../Util/Stack/stack.h"
#include "../Util/String/string.h"
#include "../Directory/directory.h"
#include "../Test/test.h"

/**
 * Functionn that checks if a character c is in the passed array
 *
 * @param arr The array
 * @param length The length of the array
 * @param c The character
 *
 * @return true if c is in arr, false if c is not in arr
 */

bool utilIsInArray(char *arr, int length, int c);








void printHelpBuild()
{
    printf(SEPERATOR);
    printf(HEADING, "B U I L D");
    printf(INFO, "By using this command, CBuilder compiles all c files int the src/main/c directory to object files.");
    printf(INFO, "When using the -d flag, the object files are placed in target/debug when not in target/prod.");
    printf(INFO, "Lastly, the object files are linked and the executable is placed in the bin directory.");
    printf(EMPTY);
    printf(LIST, "CBuilder will go up the directory tree to find a CBuilder project. It wil start at -p or the CWD");
    printf(LIST, "When a project was found, CBuilder compiles all c files to object files");
    printf(LIST, "For debugging use the -d flag");
    printf(LIST, "CBuilder manages object files with or without debug information separatly in target/prod and target/debug");
    printf(LIST, "CBuilder will check if the right object file of each c file already exists before compiling it");
    printf(LIST, "CBuilder will only compile it if no object file exists or if the object file was created before the c file was last modified");
    printf(LIST, "Lastly, CBuilder will link the object files in target/prod or target/debug to an executable that is placed in the bin directory");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-p [PATH]", "specifies a direct or indirect path");
    printf(LINE, "-d", "adds debug information");
    printf(SEPERATOR);
}
