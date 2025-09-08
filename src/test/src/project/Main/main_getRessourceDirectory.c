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






































Directory *getRessourceDirectory()
{
    char pathExe[MAX_LENGTH_PATH];

    int st1 = directoryGetExecutablePath(pathExe);

    if (st1 == -1)
    {
        printf("[ERROR] : Executable path could not be found | getRessourceDirectory \n");
        return NULL;
    }

    char pathPro[MAX_LENGTH_PATH];

    for (int i = strlen(pathExe) - 1; i >= 0; i--)
    {
        if (pathExe[i] == '/')
        {
            pathExe[i] = '\0';
            break;
        }
    }

    int st2 = findProject(pathExe, pathPro);

    if (st2 == -1)
    {
        printf("[ERROR] : CBuilder project could not be found | getRessourceDirectory \n");
        return NULL;
    }

    strcat(pathPro, "/src/main/ressources");

    Directory *dir = directoryGet(pathPro);

    if (dir == NULL)
    {
        printf("[ERROR] : Directory could not be found | getRessourceDirectory \n");
        return NULL;
    }

    return dir;
}
