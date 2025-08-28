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




int updateFiles(List *splitFiles, String *token)
{
    if (splitFiles == NULL)
    {
        printf("[ERROR] : list can not be null | updateFiles \n");
        return -1;
    }

    if (token == NULL)
    {
        printf("[ERROR] : string can not be null | updateFiles \n");
        return -1;
    }

    for (int i = 0; i < listLength(splitFiles); i++)
    {
        String *temp = listGet(splitFiles, i);

        stringCat(temp, token);

        listSet(splitFiles, temp, i);

        stringFree(temp);
    }
    return 0;
}
