#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "../Util/display.h"
#include "../Directory/directory.h"

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        printHelpGeneral();
        return 0;
    }

    char *mainCMD = argv[1];

    if (strcmp(mainCMD, "create") == 0)
    {
        int length = 1;
        int lengthAct;
        char *params[length];
        int st1 = setArrayToNull((void **)params, length);

        if (st1 == -1)
        {
            printf("[ERROR] : Function setArrayToNull failed! | main \n");
            return -1;
        }

        for (int i = 2; i < argc; i += 2)
        {
            if (strcmp(argv[i], "-h") == 0)
            {
                if (argc != 3)
                {
                    printInvalidCMD();
                    return -1;
                }
                else
                {
                    printHelpCreate();
                    return 0;
                }
            }

            else if (strcmp(argv[i], "-p") == 0)
            {
                if (argc <= i + 1)
                {
                    printInvalidCMD();
                    return -1;
                }
                params[0] = argv[i + 1];
                lengthAct++;
            }
            else
            {
                printInvalidCMD();
                return -1;
            }
        }

        if (lengthAct == 0)
        {
            create(".");
        }
        else
        {
            create(params[0]);
        }
    }

    else if (strcmp(mainCMD, "-h") == 0)
    {
        if (argv[argc - 1] != mainCMD)
        {
            printInvalidCMD();
            return -1;
        }

        printHelpGeneral();
        return 0;
    }

    else if (strcmp(mainCMD, "-v") == 0)
    {
        if (argv[argc - 1] != mainCMD)
        {
            printInvalidCMD();
            return -1;
        }

        printVersion();
        return 0;
    }
    else
    {
        printInvalidCMD();
        return -1;
    }
}

void printHelpGeneral()
{
    printf(SEPERATOR);
    printf(HEADING, "U S A G E");
    printf(LINE, "For general properties", "cbuilder [ARGUMENT]");
    printf(LINE, "For a specific command", "cbuilder [COMMAND] [ARGUMENTS]");
    printf(SEPERATOR);
    printf(HEADING, "C O M M A N D S");
    printf(LINE, "create", "creates the project structure and the cbuilder file");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-v", "displays the version of cbuilder on this machine");
    printf(LINE, "-h", "displays the general commands that cbuilder offers");
    printf(SEPERATOR);
}

void printHelpCreate()
{
    printf(SEPERATOR);
    printf(HEADING, "C R E A T E");
    printf(INFO, "By using this command, CBuilder creates the project structure with the cbuilder file,");
    printf(INFO, "which is necessary for CBuilder to function properly. Before creating the project structure");
    printf(INFO, "at the specified path, CBuilder is going up the directory tree to check if it is already in a CBuilder project.");
    printf(EMPTY);
    printf(LIST, "CBuilder will only create files and folders, it will not delete existing files or folders");
    printf(LIST, "CBuilder will use the current working directory if no path is specified");
    printf(LIST, "The create command can be used to check if the project structure is valid or not");
    printf(LIST, "CBuilder will create the project at the specified path if no CBuilder project in this dirctory was found");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-p", "specifies a direct or indirect path");
    printf(SEPERATOR);
}

void printInvalidCMD()
{
    printf(SEPERATOR);
    printf(HEADING, "I N V A L I D  C O M M A N D");
    printf(LINE, "For general properties", "cbuilder [ARGUMENT]");
    printf(LINE, "For a specific command", "cbuilder [COMMAND] [ARGUMENTS]");
    printf(SEPERATOR);
    printf(HEADING, "H E L P");
    printf(LINE, "cbuilder, cbuilder -h", "displays all commands and basic arguments");
    printf(LINE, "cbuilder [COMMAND] -h", "displays specifc information and arguments about a specific command");
    printf(SEPERATOR);
}

void printVersion()
{
    printf(SEPERATOR);
    printf(HEADING, "V E R S I O N");
    printf(LINE, "Version:", VERSION);
    printf(SEPERATOR);
}

void create(char *path)
{
    char projectPath[MAX_LENGTH_PATH];
    bool project = false;

    Directory *dir = directoryGet(path);

    if (dir == NULL)
    {
        printf("[ERROR] : Wrong path passed | create \n");
        return;
    }

    if (isProject(dir))
    {
        strcpy(projectPath, directoryGetPath(dir));
        project = true;
    }

    while (!project)
    {
        Directory *dirParent = directoryGetParent(dir);

        directoryFree(dir);
        dir = dirParent;

        if (dirParent == NULL)
        {
            break;
        }

        if (isProject(dirParent))
        {
            project = true;
            strcpy(projectPath, directoryGetPath(dirParent));
            break;
        }
    }

    if (project)
    {
        printf(SEPERATOR);
        printf(LINE, "A CBuilder projects exists at:", projectPath);
        printf(SEPERATOR);
        return;
    }
    else
    {
        directoryCreate(path, "bin");
        directoryCreate(path, "src");
        directoryCreate(path, "target");

        char pathSrc[MAX_LENGTH_PATH];
        strcpy(pathSrc, path);
        strcat(pathSrc, "/src");

        directoryCreate(pathSrc, "main");
        directoryCreate(pathSrc, "test");

        char pathMain[MAX_LENGTH_PATH];
        strcpy(pathMain, pathSrc);
        strcat(pathMain, "/main");
        
        directoryCreate(pathMain, "c");
        directoryCreate(pathMain, "ressources");
    }

    directoryFree(dir);
}

bool isProject(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dir, "cbuilderfile", FILE) || !directoryIsEntry(dir, "bin", DIRECTORY) || !directoryIsEntry(dir, "src", DIRECTORY) || !directoryIsEntry(dir, "target", DIRECTORY))
    {
        return false;
    }

    Directory *dirSrc = directoryGetSub(dir, "src");

    if (dirSrc == NULL)
    {
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirSrc, "main", DIRECTORY) || !directoryIsEntry(dirSrc, "test", DIRECTORY))
    {
        directoryFree(dirSrc);
        return false;
    }

    Directory *dirMain = directoryGetSub(dirSrc, "main");

    if (dirMain == NULL)
    {
        directoryFree(dirSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirMain, "c", DIRECTORY) || !directoryIsEntry(dirMain, "ressources", DIRECTORY))
    {
        directoryFree(dirSrc);
        directoryFree(dirMain);
        return false;
    }

    directoryFree(dirSrc);
    directoryFree(dirMain);

    return true;
}

int setArrayToNull(void **p, int length)
{
    if (p == NULL)
    {
        printf("[ERROR] : List is Null | setArrayToNull \n");
        return -1;
    }

    if (length == 0)
    {
        printf("[INFO] : List has a length of zero | setArrayToNull \n");
    }

    for (int i = 0; i < length; i++)
    {
        p[i] = NULL;
    }

    return 0;
}

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
