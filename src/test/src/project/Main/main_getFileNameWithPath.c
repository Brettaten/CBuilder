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


















































char *getFileNameWithPath(char *path)
{
    char *name = stringCreate(NULL);
    int nameLength = 0;

    for (int i = strlen(path) - 1; i >= 0; i--)
    {
        if (path[i] != '/')
        {
            nameLength++;
        }
        else
        {
            break;
        }
    }

    for (int i = strlen(path) - nameLength, j = 0; i < strlen(path); i++, j++)
    {
        name = stringAdd(name, path[i]);
    }

    return name;
}
