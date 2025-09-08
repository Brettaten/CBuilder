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














































char *utilGetEx(char *name)
{
    if (name == NULL)
    {
        printf("[ERROR] : name is null | utilGetName \n");
        return NULL;
    }

    int length = strlen(name);
    char ex[length];
    bool isExt = false;

    char *str = stringCreate(NULL);

    for (int i = 0; i < length; i++)
    {
        if (isExt)
        {
            str = stringAdd(str, name[i]);
        }
        else if (name[i] == '.')
        {
            isExt = true;
            str = stringAdd(str, name[i]);
        }
    }

    return str;
}
