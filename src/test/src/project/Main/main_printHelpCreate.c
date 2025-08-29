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






void printHelpCreate()
{
    printf(SEPERATOR);
    printf(HEADING, "C R E A T E");
    printf(INFO, "By using this command, CBuilder creates the project structure with the cbuilder file,");
    printf(INFO, "which is necessary for CBuilder to function properly. Before creating the project structure");
    printf(INFO, "at the specified path, CBuilder is going up the directory tree to check if it is already in a CBuilder project.");
    printf(EMPTY);
    printf(LIST, "CBuilder will only create files and folders, it will not delete existing files or folders");
    printf(LIST, "CBuilder will use the current working directory if no path is specified");
    printf(LIST, "The create command can be used to check if the project structure is valid or not");
    printf(LIST, "CBuilder will create the project at the specified path if no CBuilder project in this dirctory was found");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-p [PATH]", "specifies a direct or indirect path");
    printf(SEPERATOR);
}
