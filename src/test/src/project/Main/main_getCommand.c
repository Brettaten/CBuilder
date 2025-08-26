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



























int getCommand(char *command, char *path, String *destCmd)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("[ERROR] : CBuilderfile could not be opened | getCommand \n");
        return -1;
    }

    int c;
    char token[1024] = "";
    List *tokenList = listCreate(1024, NULL, NULL);

    char specialTokens[] = {'{', '}', ':'};
    int length = 3;

    bool isString = false;

    while ((c = getc(file)) != EOF)
    {

        char temp[2];
        temp[0] = c;
        temp[1] = '\0';

        if (isspace(c) && isString == false)
        {
            if (strcmp(token, "") != 0)
            {
                listAdd(tokenList, token);
                strcpy(token, "");
            }
        }
        else if (utilIsInArray(specialTokens, length, c) && isString == false)
        {
            if (strcmp(token, "") == 0)
            {
                strcat(token, temp);
                listAdd(tokenList, token);
                strcpy(token, "");
            }
            else
            {
                listAdd(tokenList, token);
                strcpy(token, "");
                strcat(token, temp);
                listAdd(tokenList, token);
                strcpy(token, "");
            }
        }
        else if (strcmp(temp, "\"") == 0)
        {
            if (strcmp(token, "") != 0)
            {
                listAdd(tokenList, token);
                strcpy(token, "");
            }
            if (isString)
            {
                isString = false;
            }
            else
            {
                isString = true;
            }
        }
        else
        {
            strcat(token, temp);
        }
    }

    fclose(file);

    bool isCommand = false;
    char *cmd = NULL;

    for (int i = 0; i < listLength(tokenList); i++)
    {
        char *tkn = listGet(tokenList, i);

        if (strcmp(tkn, command) == 0 && isCommand == false)
        {
            char *nextToken = listGet(tokenList, i + 1);

            if (nextToken != NULL && strcmp(nextToken, "{") == 0)
            {
                isCommand = true;
                free(nextToken);
                i++;
            }
            else
            {
                free(nextToken);
            }
        }

        else if (strcmp(tkn, "cmd") == 0 && isCommand)
        {
            char *nextToken = listGet(tokenList, i + 1);

            if (nextToken != NULL && strcmp(nextToken, ":") == 0)
            {
                free(nextToken);
                cmd = listGet(tokenList, i + 2);
                i += 2;
            }
            else
            {
                free(nextToken);
            }
        }

        else if (strcmp(tkn, "}") == 0 && isCommand)
        {
            free(tkn);
            break;
        }
        free(tkn);
    }

    if (cmd == NULL)
    {
        free(cmd);
        free(tokenList);
        printf("[ERROR] : Could not read command from cbuilderfile | getCommand \n");
        return -1;
    }

    int st1 = stringClear(destCmd);

    if (st1 == -1)
    {
        printf("[ERROR] : Function stringClear failed | getCommand \n");
        return -1;
    }

    for (int i = 0; i < strlen(cmd); i++)
    {
        int st2 = stringAdd(destCmd, cmd[i]);

        if (st2 == -1)
        {
            printf("[ERROR] : Function stringAdd failed | getCommand \n");
            return -1;
        }
    }

    free(cmd);
    free(tokenList);

    return 0;
}