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












void printHelpTestBuild()
{
    printf(SEPERATOR);
    printf(HEADING, "T E S T _ B U I L D");
    printf(INFO, "By using this command, CBuilder copies all c files from the src/main/c directory into the test/src/project directory.");
    printf(INFO, "The c files are splitted into smaller c files, that contain just one function definition each and everything else");
    printf(INFO, "like function declarations will be the same for all split files. The static keyword will be removed.");
    printf(INFO, "Because of this process, problems can occur. For instance, a static function might share one name with another function, after the file was split.");
    printf(INFO, "Then the tests in test/src/main/c will be generated, thus there is no reason to add a main function in the test files.");
    printf(INFO, "Use the assert function at c/util/cbuilderTest.h .");
    printf(INFO, "Only files that start with \"test\" will be considered and only for functions that start with \"test\", a test will be generated.");
    printf(INFO, "functions that start with \"util\" will be ignored(copied), while every other function will be treated as a mock.");
    printf(INFO, "Then every test will be compiled and linked with the split files. Debug information will be enabled, always.");
    printf(INFO, "If a test contains a mock, cbuilder will look for a file that contains a function with that name among the split files");
    printf(INFO, "and if it finds it, this file will be excluded from linking. If the test does not contain a mock all files will be linked.");
    printf(INFO, "There will be an executable at test/bin that concatenates all tests to one and separate executables in test/bin/separate .");
    printf(INFO, "When calling tests separatly, use the argument \"1\" to signal that this will be the last test. This will ensure that the stats will be displayed and resetted");
    printf(EMPTY);
    printf(LIST, "CBuilder will go up the directory tree to find a CBuilder project. It wil start at -p or the CWD");
    printf(LIST, "When a project was found, CBuilder compiles all c files to object files");
    printf(LIST, "CBuilder will generate all tests and put the executables in test/bin/");
    printf(LIST, "Everything will be with debug information");
    printf(LIST, "CBuilder will check if the right object file of each c file already exists before compiling it");
    printf(LIST, "CBuilder will only compile it if no object file exists or if the object file was created before the c file was last modified");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-p [PATH]", "specifies a direct or indirect path");
    printf(SEPERATOR);
}
