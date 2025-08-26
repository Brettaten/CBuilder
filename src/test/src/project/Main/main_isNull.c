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

/**
 * Function that strips the file name and returns the file extension as a string
 *
 * @param name the file name with file extension
 *
 * @return Success: the file extension without name | Failure: NULL
 */
String *utilGetEx(char *name);



































bool isNull(void **p, int length)
{
    if (p == NULL)
    {
        printf("[ERROR] : List is Null | isNotNull \n");
        return true;
    }

    if (length == 0)
    {
        printf("[ERROR] : List has a length of zero | isNotNull \n");
        return true;
    }

    for (int i = 0; i < length; i++)
    {
        if (p[i] == NULL)
        {
            return true;
        }
    }

    return false;
}