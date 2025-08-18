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
 * Function that strips the file ending and returns the file name as a string
 *
 * @param name the file name with file extension
 *
 * @return Success: the file name without extension | Failure: NULL
 */
String *utilGetName(char *name);

/**
 * Function that strips the file name and returns the file extension as a string
 *
 * @param name the file name with file extension
 *
 * @return Success: the file extension without name | Failure: NULL
 */
String *utilGetEx(char *name);

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
        char path[MAX_LENGTH_PATH] = ".";

        for (int i = 2; i < argc; i++)
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
                strcpy(path, argv[i + 1]);
                i++;
            }
            else
            {
                printInvalidCMD();
                return -1;
            }
        }

        create(path);
    }

    else if (strcmp(mainCMD, "build") == 0)
    {
        char path[MAX_LENGTH_PATH] = ".";
        bool debug = false;

        for (int i = 2; i < argc; i++)
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
                    printHelpBuild();
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
                strcpy(path, argv[i + 1]);
                i++;
            }

            else if (strcmp(argv[i], "-d") == 0)
            {
                debug = true;
            }
            else
            {
                printInvalidCMD();
                return -1;
            }
        }
        build(path, debug);
    }

    else if (strcmp(mainCMD, "clear") == 0)
    {
        char path[MAX_LENGTH_PATH] = ".";

        for (int i = 2; i < argc; i++)
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
                    printHelpClear();
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
                strcpy(path, argv[i + 1]);
                i++;
            }

            else
            {
                printInvalidCMD();
                return -1;
            }
        }
        clear(path);
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
    printf(LINE, "-p [PATH]", "specifies a direct or indirect path");
    printf(SEPERATOR);
}

void printHelpBuild()
{
    printf(SEPERATOR);
    printf(HEADING, "B U I L D");
    printf(INFO, "By using this command, CBuilder compiles all c files int the src/main/c directory to object files.");
    printf(INFO, "When using the -d flag, the object files are placed in target/debug when not in target/prod.");
    printf(INFO, "Lastly, the object files are linked and the executable is placed in the bin directory.");
    printf(EMPTY);
    printf(LIST, "CBuilder will go up the directory tree to find a CBuilder project. It wil start at -p or the CWD");
    printf(LIST, "When a project was found, CBuilder compiles all c files to object files");
    printf(LIST, "For debugging use the -d flag");
    printf(LIST, "CBuilder manages object files with or without debug information separatly in target/prod and target/debug");
    printf(LIST, "CBuilder will check if the right object file of each c file already exists before compiling it");
    printf(LIST, "CBuilder will only compile it if no object file exists or if the object file was created before the c file was last modified");
    printf(LIST, "Lastly, CBuilder will link the object files in target/prod or target/debug to an executable that is placed in the bin directory");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-p [PATH]", "specifies a direct or indirect path");
    printf(LINE, "-d", "adds debug information");
    printf(SEPERATOR);
}

void printHelpClear()
{
    printf(SEPERATOR);
    printf(HEADING, "C L E A R");
    printf(INFO, "By using this command, CBuilder deletes all object files, located in the target directory.");
    printf(EMPTY);
    printf(LIST, "CBuilder will go up the directory tree to find a CBuilder project. It wil start at -p or the CWD");
    printf(LIST, "When a project was found, CBuilder deletes all obj files located in the target directory");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-p [PATH]", "specifies a direct or indirect path");
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

        char pathTarget[MAX_LENGTH_PATH];
        strcpy(pathTarget, path);
        strcat(pathTarget, "/target");

        if (!directoryCreate(pathTarget, "prod") || !directoryCreate(pathTarget, "debug"))
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

void build(char *path, bool debug)
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

    if (project)
    {
        Directory *dir = directoryGet(projectPath);

        if (dir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | build \n");
            return;
        }

        Entry *bin = directoryGetEntry(dir, "bin", TYPE_DIRECTORY);

        if (bin == NULL)
        {
            printf("[ERROR] : Bin directory was not found | build \n");
            return;
        }

        String *binDirPath = stringCreate(entryGetPath(bin));

        entryFree(bin);

        Entry *builderFile = directoryGetEntry(dir, "cbuilderfile", TYPE_FILE);

        if (builderFile == NULL)
        {
            printf("[ERROR] : Entry for the specified directory was not found | build \n");
            return;
        }

        char builderFilePath[MAX_LENGTH_PATH];
        strcpy(builderFilePath, entryGetPath(builderFile));

        String *systemCommand = stringCreate(NULL);
        String *cFile = stringCreate("$CFILE");
        String *objFile = stringCreate("$OBJFILE");

        char relTarget[MAX_LENGTH_PATH];

        char command[64];

        if (debug)
        {
            strcpy(command, "debug");
            strcpy(relTarget, "/target/debug");
        }
        else
        {
            strcpy(command, "build");
            strcpy(relTarget, "/target/prod");
        }

        getCommand(command, builderFilePath, systemCommand);

        char *commandBluePrint = stringToArr(systemCommand);

        char filePath[MAX_LENGTH_PATH];

        directoryFree(dir);
        entryFree(builderFile);

        char srcPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcat(srcPath, "/src/main/c");
        Directory *src = directoryGet(srcPath);

        if (src == NULL)
        {
            printf("[ERROR] : The c directory of the project was not found | build \n");
            return;
        }

        char targetPath[MAX_LENGTH_PATH];
        strcpy(targetPath, projectPath);
        strcat(targetPath, relTarget);
        Directory *target = directoryGet(targetPath);

        if (target == NULL)
        {
            printf("[ERROR] : The %s directory of the project was not found | build \n", relTarget);
            return;
        }

        Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
        Stack *stackTarget = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

        if (stackSrc == NULL || stackTarget == NULL)
        {
            printf("[ERROR] : Function stackCreate failed | build \n");
            return;
        }

        int st1 = stackPush(stackSrc, src);
        int st2 = stackPush(stackTarget, target);

        if (st1 == -1 || st2 == -1)
        {
            printf("[ERROR] : Function stackPush failed | build \n");
            return;
        }

        String *oFileList = stringCreate(NULL);
        String *delimiter = stringCreate(" ");

        String *objType = stringCreate(".o");
        String *cType = stringCreate(".c");

        int fileCounter = 0;
        int alteredFileCounter = 0;

        while (stackLength(stackSrc) > 0)
        {
            Directory *tempSrc = stackPop(stackSrc);
            Directory *tempTarget = stackPop(stackTarget);

            if (tempSrc == NULL || tempTarget == NULL)
            {
                printf("[ERROR] : Function stackPop failed | build \n");
                return;
            }

            for (int i = 0; i < directoryGetEntryAmount(tempSrc); i++)
            {
                Entry *tempEntrySrc = directoryGetEntryAt(tempSrc, i);

                String *cPath = stringCreate(entryGetPath(tempEntrySrc));
                String *name = utilGetName(entryGetName(tempEntrySrc));
                String *type = utilGetEx(entryGetName(tempEntrySrc));
                String *objPath = stringCreate(directoryGetPath(tempTarget));
                String *objName = stringCopy(name);
                stringCat(objName, objType);
                String *slash = stringCreate("/");
                stringCat(objPath, slash);
                stringCat(objPath, name);
                stringCat(objPath, objType);

                if (tempEntrySrc == NULL)
                {
                    printf("[ERROR] : Function directoryGetEntryAt failed | build \n");
                    return;
                }

                if (entryGetType(tempEntrySrc) == TYPE_DIRECTORY)
                {
                    Directory *newDirSrc = directoryGet(entryGetPath(tempEntrySrc));

                    if (newDirSrc == NULL)
                    {
                        printf("[ERROR] : Function directoryGet failed | build \n");
                        return;
                    }

                    bool st3 = directoryCreate(directoryGetPath(tempTarget), entryGetName(tempEntrySrc));

                    if (st3 == false)
                    {
                        printf("[ERROR] : Function directoryCreate failed | build \n");
                        return;
                    }

                    char temp[MAX_LENGTH_PATH];
                    strcpy(temp, directoryGetPath(tempTarget));
                    strcat(temp, "/");
                    strcat(temp, entryGetName(tempEntrySrc));

                    Directory *newDirTarget = directoryGet(temp);

                    if (newDirTarget == NULL)
                    {
                        printf("[ERROR] : Function directoryGet failed | build \n");
                        return;
                    }

                    stackPush(stackSrc, newDirSrc);
                    stackPush(stackTarget, newDirTarget);

                    directoryFree(newDirSrc);
                    directoryFree(newDirTarget);
                }

                else if (stringEquals(type, cType))
                {
                    fileCounter++;

                    char *tempObjName = stringToArr(objName);
                    Entry *tempEntryTarget = directoryGetEntry(tempTarget, tempObjName, TYPE_FILE);
                    free(tempObjName);

                    stringReplace(systemCommand, cFile, cPath);
                    stringReplace(systemCommand, objFile, objPath);

                    if (tempEntryTarget != NULL && entryGetLastModified(tempEntryTarget) < entryGetLastModified(tempEntrySrc))
                    {
                        alteredFileCounter++;

                        int st4 = remove(entryGetPath(tempEntryTarget));

                        if (st4 != 0)
                        {
                            printf("[ERROR] : Function remove failed | build \n");
                            return;
                        }
                        char *tempCmd = stringToArr(systemCommand);
                        system(tempCmd);
                        free(tempCmd);
                    }
                    else if (tempEntryTarget == NULL)
                    {
                        alteredFileCounter++;

                        char *tempCmd = stringToArr(systemCommand);
                        system(tempCmd);
                        free(tempCmd);
                    }

                    if (tempEntryTarget != NULL)
                    {
                        entryFree(tempEntryTarget);
                    }
                    stringFree(systemCommand);
                    systemCommand = stringCreate(commandBluePrint);

                    stringCat(oFileList, objPath);
                    stringCat(oFileList, delimiter);
                }

                entryFree(tempEntrySrc);
                stringFree(cPath);
                stringFree(objPath);
                stringFree(objName);
                stringFree(type);
                stringFree(name);
                stringFree(slash);
            }
            directoryFree(tempSrc);
            directoryFree(tempTarget);
        }
        stackFree(stackSrc);
        stackFree(stackTarget);
        stringFree(systemCommand);
        stringFree(cFile);
        stringFree(objFile);
        stringFree(objType);
        stringFree(cType);
        stringFree(delimiter);
        free(commandBluePrint);

        char linkCommand[] = "link";
        String *linkSystemCommand = stringCreate(NULL);
        String *objFiles = stringCreate("$OBJFILES");
        String *binPath = stringCreate("$BINPATH");
        String *permission = stringCreate("chmod a+x ");

        stringCat(permission, binDirPath);

        getCommand(linkCommand, builderFilePath, linkSystemCommand);

        stringReplace(linkSystemCommand, objFiles, oFileList);
        stringReplace(linkSystemCommand, binPath, binDirPath);

        char *tempLinkCmd = stringToArr(linkSystemCommand);
        system(tempLinkCmd);

#ifdef LINUX
        char *tempPermissionCmd = stringToArr(permission);
        system(tempPermissionCmd);
        free(tempPermissionCmd);
#endif
        free(tempLinkCmd);

        stringFree(linkSystemCommand);
        stringFree(objFiles);
        stringFree(oFileList);
        stringFree(binPath);
        stringFree(binDirPath);
        stringFree(permission);

        char fileCounterC[16];
        char alteredFileCounterC[16];
        sprintf(fileCounterC, "%d", fileCounter);
        sprintf(alteredFileCounterC, "%d", alteredFileCounter);

        printf(SEPERATOR);
        printf(HEADING, "S U C C E S S");
        printf(LINE, "Files compiled:", alteredFileCounterC);
        printf(LINE, "Files linked:", fileCounterC);
        printf(SEPERATOR);
    }
    else
    {
        printf(SEPERATOR);
        printf(HEADING, "E R R O R");
        printf(LINE, "No CBuilder project was found at:", projectPath);
        printf(SEPERATOR);
        return;
    }
}

void clear(char *path)
{
}

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

    Directory *dirTarget = directoryGetSub(dir, "target");

    if (dirTarget == NULL)
    {
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTarget, "prod", TYPE_DIRECTORY) || !directoryIsEntry(dirTarget, "debug", TYPE_DIRECTORY))
    {
        directoryFree(dirTarget);
        return false;
    }

    Directory *dirSrc = directoryGetSub(dir, "src");

    if (dirSrc == NULL)
    {
        directoryFree(dirTarget);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirSrc, "main", TYPE_DIRECTORY) || !directoryIsEntry(dirSrc, "test", TYPE_DIRECTORY))
    {
        directoryFree(dirTarget);
        directoryFree(dirSrc);
        return false;
    }

    Directory *dirMain = directoryGetSub(dirSrc, "main");

    if (dirMain == NULL)
    {
        directoryFree(dirTarget);
        directoryFree(dirSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirMain, "c", TYPE_DIRECTORY) || !directoryIsEntry(dirMain, "ressources", TYPE_DIRECTORY))
    {
        directoryFree(dirTarget);
        directoryFree(dirSrc);
        directoryFree(dirMain);
        return false;
    }

    directoryFree(dirTarget);
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
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == c)
        {
            return true;
        }
    }
    return false;
}

String *utilGetName(char *name)
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
    String *str = stringCreate(cpy);

    return str;
}

String *utilGetEx(char *name)
{
    if (name == NULL)
    {
        printf("[ERROR] : name is null | utilGetName \n");
        return NULL;
    }

    int length = strlen(name);
    char ex[length];
    bool isExt = false;

    String *str = stringCreate(NULL);

    for (int i = 0; i < length; i++)
    {
        if (isExt)
        {
            stringAdd(str, name[i]);
        }
        else if (name[i] == '.')
        {
            isExt = true;
            stringAdd(str, name[i]);
        }
    }

    return str;
}
