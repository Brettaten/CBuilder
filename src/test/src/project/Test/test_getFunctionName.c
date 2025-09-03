#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "test.h"
#include "../Util/String/string.h"
#include "../Util/List/list.h"
#include "../Util/Stack/stack.h"
#include "../Main/main.h"

enum TYPE
{
    MACRO,
    FUNCTION,
    COMMENT,
    MULTI_COMMENT,
    STRUCT,
    OTHER
};


/**
 * Function used to update the splited files by adding additional information
 *
 * @param splitFiles the list with the files
 * @param token the addition
 *
 * @return Success: 0 | Failure: -1
 */

int updateFiles(List *splitFiles, char *token);


/**
 * Function used to get the name of a function
 *
 * @param func the function
 *
 * @return Success: the name
 */

char *getFunctionName(char *func);


/**
 * Function used to concatenate two lists that contain strings
 *
 * @param dest the destination list
 * @param src the source list
 */

void utilConcatenateLists(List *dest, List *src);








char *getFunctionName(char *func)
{
    char *token = stringCreate(NULL);
    bool isName = false;
    int c;

    for (int i = 0; i < strlen(func); i++)
    {
        c = func[i];

        if (isName)
        {
            if (c == '*' && strlen(token) == 0)
            {
                continue;
            }
            else if (isspace(c) || c == '(')
            {
                break;
            }
            else
            {
                token = stringAdd(token, c);
            }
        }
        else
        {
            if (isspace(c))
            {
                if (strlen(token) != 0 && strcmp(token, "static") != 0 && strcmp(token, "extern") != 0 && strcmp(token, "inline") != 0 && strcmp(token, "_Noreturn") != 0)
                {
                    token = stringClear(token);
                    isName = true;
                }
                else if (strcmp(token, "static") == 0 || strcmp(token, "extern") == 0 || strcmp(token, "inline") == 0 || strcmp(token, "_Noreturn") == 0)
                {
                    token = stringClear(token);
                }
            }
            else
            {
                token = stringAdd(token, c);
            }
        }
    }

    return token;
}
