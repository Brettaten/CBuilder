#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "main.h"
#include "../Util/display.h"
#include "../Util/List/list.h"
#include "../Directory/directory.h"

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
        int lengthAct = 0;
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

    else if(strcmp(mainCMD, "build") == 0){
        
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

void printNoProjectFound()
{
    printf(SEPERATOR);
    printf(HEADING, "E R R O R");
    printf(INFO, "No CBuilder project was found");
    printf(SEPERATOR);
}

void create(char *path)
{
    char projectPath[MAX_LENGTH_PATH];
    bool project = false;

    int st1 = findProject(path, projectPath);

    if (st1 == -1)
    {
        directoryNormalizePath(projectPath, path);
        project = false;
    }
    else
    {
        project = true;
    }

    if (projectPath)

        if (project)
        {
            printf(SEPERATOR);
            printf(HEADING, "I N F O");
            printf(LINE, "A CBuilder project exists at:", projectPath);
            printf(SEPERATOR);
            return;
        }
        else
        {
            Directory *ressource = getRessourceDirectory();

            if (ressource == NULL)
            {
                printf("[ERROR] : Ressource directory was not found | create");
                return;
            }

            Entry *template = directoryGetEntry(ressource, "cbuilderfile", TYPE_FILE);

            if (template == NULL)
            {
                printf("[ERROR] : CBuilderfile template was not found | create");
            }

            if (!directoryCreate(path, "bin") || !directoryCreate(path, "src") || !directoryCreate(path, "target") || !fileCreate(path, "cbuilderfile") || !fileCopy(path, "cbuilderfile", directoryGetPath(ressource), entryGetName(template)))
            {
                printf("[ERROR] : Something went wrong during project creation | create \n");
                return;
            }

            char pathSrc[MAX_LENGTH_PATH];
            strcpy(pathSrc, path);
            strcat(pathSrc, "/src");

            if (!directoryCreate(pathSrc, "main") || !directoryCreate(pathSrc, "test"))
            {
                printf("[ERROR] : Something went wrong during project creation | create \n");
                return;
            }

            char pathMain[MAX_LENGTH_PATH];
            strcpy(pathMain, pathSrc);
            strcat(pathMain, "/main");

            if (!directoryCreate(pathMain, "c") || !directoryCreate(pathMain, "ressources"))
            {
                printf("[ERROR] : Something went wrong during project creation | create \n");
                return;
            }

            printf(SEPERATOR);
            printf(HEADING, "S U C E S S S");
            printf(LINE, "CBuilder project created at:", projectPath);
            printf(SEPERATOR);

            directoryFree(ressource);
            entryFree(template);
        }
}

void getCommand(char *command, char *path, char *dest)
{
    char projectPath[MAX_LENGTH_PATH];
    int st1 = findProject(path, projectPath);

    if (st1 == -1)
    {
        printNoProjectFound();
        return;
    }

    Directory *dir = directoryGet(projectPath);

    if(dir == NULL){
        printf("[ERROR] : Directory for the specified path was not found | getCommand \n");
        return;
    }

    Entry *builderFile = directoryGetEntry(dir, "cbuilderfile", TYPE_FILE);

    if(builderFile == NULL){
        printf("[ERROR] : Entry for the specified directory was not found | getCommand \n");
        return;
    }

    FILE *file = fopen(entryGetPath(builderFile), "r");

    if(file == NULL){
        printf("[ERROR] : CBuilderfile could not be opened | getCommand \n");
        return;
    }

    int c;
    char token[1024] = "";
    List *tokenList = listCreate(sizeof(char *));

    char specialTokens = {'{', '}', ':'};
    int length = 3;

    while((c = getc(file)) != EOF){
        if(isspace(c) && strcmp(token, "") != 0){
            listAdd(tokenList, token);
            strcpy(token, "");
        }
        else if(utilIsInArray(specialTokens, length, c)){
            if(strcmp(token, "") == 0){
                strcat(token, c);
                listAdd(tokenList, token);
                strcpy(token, "");
            }
            else{
                listAdd(tokenList, token);
                strcpy(token, "");
                strcat(token, c);
                listAdd(tokenList, token);
                strcpy(token, "");
            }
        }
        else{
            strcat(token, c);
        }
    }

    directoryFree(dir);
    entryFree(builderFile);
    fclose(file);
}

bool isProject(Directory *dir)
{
    if (dir == NULL)
    {
        printf("[ERROR] : Directory is null | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dir, "cbuilderfile", TYPE_FILE) || !directoryIsEntry(dir, "bin", TYPE_DIRECTORY) || !directoryIsEntry(dir, "src", TYPE_DIRECTORY) || !directoryIsEntry(dir, "target", TYPE_DIRECTORY))
    {
        return false;
    }

    Directory *dirSrc = directoryGetSub(dir, "src");

    if (dirSrc == NULL)
    {
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirSrc, "main", TYPE_DIRECTORY) || !directoryIsEntry(dirSrc, "test", TYPE_DIRECTORY))
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

    if (!directoryIsEntry(dirMain, "c", TYPE_DIRECTORY) || !directoryIsEntry(dirMain, "ressources", TYPE_DIRECTORY))
    {
        directoryFree(dirSrc);
        directoryFree(dirMain);
        return false;
    }

    directoryFree(dirSrc);
    directoryFree(dirMain);

    return true;
}

int findProject(char *path, char *dest)
{
    char projectPath[MAX_LENGTH_PATH];
    bool project = false;

    Directory *dir = directoryGet(path);

    if (dir == NULL)
    {
        printf("[ERROR] : Wrong path passed | findProject \n");
        dest = NULL;
        return -1;
    }

    strcpy(projectPath, directoryGetPath(dir));

    if (isProject(dir))
    {
        strcpy(projectPath, directoryGetPath(dir));
        project = true;
        directoryFree(dir);
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
            directoryFree(dir);
            break;
        }
    }

    if (project)
    {
        strcpy(dest, projectPath);
        return 0;
    }
    else
    {
        return -1;
    }
}

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

bool utilIsInArray(char *arr, int length, int c)
{
    for(int i = 0; i < length; i++){
        if(arr[i] == 'c'){
            return true;
        }
    }
    return false;
}
