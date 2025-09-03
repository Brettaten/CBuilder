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


 int x = 10;








































char *utilGetName(char *name)
{
    if (name == NULL)
    {
        printf("[ERROR] : name is null | utilGetName \n");
        return NULL;
    }

    int length = strlen(name);
    char cpy[length];

    for (int i = 0; i < length; i++)
    {
        if (name[i] == '.')
        {
            cpy[i] = '\0';
            break;
        }
        cpy[i] = name[i];
    }
    cpy[length] = '\0';

    char *str = stringCreate(cpy);

    return str;
}
