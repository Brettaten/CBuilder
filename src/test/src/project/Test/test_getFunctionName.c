#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "test.h"
#include "../Util/String/string.h"
#include "../Util/List/list.h"
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

int updateFiles(List *splitFiles, String *token);


/**
 * Function used to get the name of a function
 *
 * @param func the function
 *
 * @return Success: the name
 */

String *getFunctionName(String *func);






String *getFunctionName(String *func)
{
    String *token = stringCreate(NULL);
    bool isName = false;
    int c;

    for (int i = 0; i < stringLength(func); i++)
    {
        c = stringGet(func, i);

        if (isName)
        {
            if (c == '*' && stringLength(token) == 0)
            {
                continue;
            }
            else if (isspace(c) || c == '(')
            {
                break;
            }
            else
            {
                stringAdd(token, c);
            }
        }
        else
        {
            if (isspace(c))
            {
                if (stringLength(token) != 0)
                {
                    stringClear(token);
                    isName = true;
                }
            }
            else
            {
                stringAdd(token, c);
            }
        }
    }

    return token;

    return 0;
}
