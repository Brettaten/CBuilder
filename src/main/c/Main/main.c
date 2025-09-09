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

    else if (strcmp(mainCMD, "test_build") == 0)
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
                    printHelpTestBuild();
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
        testBuild(path);
    }

    else if (strcmp(mainCMD, "test_clear") == 0)
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
                    printHelpTestClear();
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
        testClear(path);
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
    printf(LINE, "build", "compiles and links the project to create an executable");
    printf(LINE, "clear", "deletes all files and directories in target/prod and target/debug");
    printf(LINE, "test_build", "builds all tests");
    printf(LINE, "test_clear", "deletes all copied c files from the project, all object files in test/ and all generated tests");
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
    printf(INFO, "By using this command, CBuilder compiles all c files into the src/main/c directory to object files.");
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

void printHelpTestBuild()
{
    printf(SEPERATOR);
    printf(HEADING, "T E S T _ B U I L D");
    printf(INFO, "By using this command, CBuilder copies all c files from the src/main/c directory into the test/src/project directory.");
    printf(INFO, "The c files are splitted into smaller c files, that contain just one function definition each and everything else");
    printf(INFO, "like function declarations will be the same for all split files. The static keyword will be removed.");
    printf(INFO, "Because of this process, problems can occur. For instance, a static function might share one name with another function, after the file was split.");
    printf(INFO, "Then the tests in test/src/main/c will be generated, thus there is no reason to add a main function in the test files.");
    printf(INFO, "Use the assert function at c/util/cbuilderTest.h .");
    printf(INFO, "Only files that start with \"test\" will be considered and only for functions that start with \"test\", a test will be generated.");
    printf(INFO, "functions that start with \"util\" will be ignored(copied), while every other function will be treated as a mock.");
    printf(INFO, "Then every test will be compiled and linked with the split files. Debug information will be enabled, always.");
    printf(INFO, "If a test contains a mock, cbuilder will look for a file that contains a function with that name among the split files");
    printf(INFO, "and if it finds it, this file will be excluded from linking. If the test does not contain a mock all files will be linked.");
    printf(INFO, "There will be an executable at test/bin that concatenates all tests to one and separate executables in test/bin/separate .");
    printf(INFO, "When calling tests separatly, use the argument \"1\" to signal that this will be the last test. This will ensure that the stats will be displayed and resetted");
    printf(EMPTY);
    printf(LIST, "CBuilder will go up the directory tree to find a CBuilder project. It wil start at -p or the CWD");
    printf(LIST, "When a project was found, CBuilder compiles all c files to object files");
    printf(LIST, "CBuilder will generate all tests and put the executables in test/bin/");
    printf(LIST, "Everything will be with debug information");
    printf(LIST, "CBuilder will check if the right object file of each c file already exists before compiling it");
    printf(LIST, "CBuilder will only compile it if no object file exists or if the object file was created before the c file was last modified");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-p [PATH]", "specifies a direct or indirect path");
    printf(SEPERATOR);
}

void printHelpTestClear()
{
    printf(SEPERATOR);
    printf(HEADING, "T E S T _ C L E A R");
    printf(INFO, "By using this command, CBuilder deletes all copied c files from the project, all object files and all generated tests.");
    printf(EMPTY);
    printf(LIST, "CBuilder will go up the directory tree to find a CBuilder project. It wil start at -p or the CWD");
    printf(LIST, "When a project was found, CBuilder deletes all files as mentioned above");
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

        char pathBuilderfileDest[MAX_LENGTH_PATH];
        strcpy(pathBuilderfileDest, projectPath);
        strcat(pathBuilderfileDest, "/cbuilderfile");

        char pathBuilderfileSrc[MAX_LENGTH_PATH];
        strcpy(pathBuilderfileSrc, directoryGetPath(ressource));
        strcat(pathBuilderfileSrc, "/");
        strcat(pathBuilderfileSrc, entryGetName(template));

        if (!directoryCreate(projectPath, "bin") || !directoryCreate(projectPath, "src") || !directoryCreate(projectPath, "target") || !fileCreate(projectPath, "cbuilderfile") || !fileCopy(pathBuilderfileDest, pathBuilderfileSrc))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTarget[MAX_LENGTH_PATH];
        strcpy(pathTarget, projectPath);
        strcat(pathTarget, "/target");

        if (!directoryCreate(pathTarget, "prod") || !directoryCreate(pathTarget, "debug"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathSrc[MAX_LENGTH_PATH];
        strcpy(pathSrc, projectPath);
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

        char pathTest[MAX_LENGTH_PATH];
        strcpy(pathTest, pathSrc);
        strcat(pathTest, "/test");

        if (!directoryCreate(pathTest, "bin") || !directoryCreate(pathTest, "src") || !directoryCreate(pathTest, "target"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestSrc[MAX_LENGTH_PATH];
        strcpy(pathTestSrc, pathTest);
        strcat(pathTestSrc, "/src");

        if (!directoryCreate(pathTestSrc, "main") || !directoryCreate(pathTestSrc, "project"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestMain[MAX_LENGTH_PATH];
        strcpy(pathTestMain, pathTestSrc);
        strcat(pathTestMain, "/main");

        if (!directoryCreate(pathTestMain, "c") || !directoryCreate(pathTestMain, "genTests"))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestC[MAX_LENGTH_PATH];
        strcpy(pathTestC, pathTestMain);
        strcat(pathTestC, "/c");

        char pathTestUtilC[MAX_LENGTH_PATH];
        strcpy(pathTestUtilC, pathTestC);
        strcat(pathTestUtilC, "/util/cbuilderTest.c");

        char pathTestUtilH[MAX_LENGTH_PATH];
        strcpy(pathTestUtilH, pathTestC);
        strcat(pathTestUtilH, "/util/cbuilderTest.h");

        char pathRessourceUtilC[MAX_LENGTH_PATH];
        strcpy(pathRessourceUtilC, directoryGetPath(ressource));
        strcat(pathRessourceUtilC, "/util/cbuilderTest.c");

        char pathRessourceUtilH[MAX_LENGTH_PATH];
        strcpy(pathRessourceUtilH, directoryGetPath(ressource));
        strcat(pathRessourceUtilH, "/util/cbuilderTest.h");

        if (!directoryCreate(pathTestC, "util") || !fileCopy(pathTestUtilC, pathRessourceUtilC) || !fileCopy(pathTestUtilH, pathRessourceUtilH))
        {
            printf("[ERROR] : Something went wrong during project creation | create \n");
            return;
        }

        char pathTestTarget[MAX_LENGTH_PATH];
        strcpy(pathTestTarget, pathTest);
        strcat(pathTestTarget, "/target");

        if (!directoryCreate(pathTestTarget, "project") || !directoryCreate(pathTestTarget, "test"))
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

        char *binDirPath = stringCreate(entryGetPath(bin));

        Entry *builderFile = directoryGetEntry(dir, "cbuilderfile", TYPE_FILE);

        if (builderFile == NULL)
        {
            printf("[ERROR] : Entry for the specified directory was not found | build \n");
            return;
        }

        char builderFilePath[MAX_LENGTH_PATH];
        strcpy(builderFilePath, entryGetPath(builderFile));

        char relTarget[MAX_LENGTH_PATH];

        if (debug)
        {
            strcpy(relTarget, "/target/debug");
        }
        else
        {
            strcpy(relTarget, "/target/prod");
        }

        char srcPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcat(srcPath, "/src/main/c");

        char targetPath[MAX_LENGTH_PATH];
        strcpy(targetPath, projectPath);
        strcat(targetPath, relTarget);

        int fileCounter = 0;
        int alteredFiles = 0;

        char *oFileList = compile(targetPath, srcPath, projectPath, true, &fileCounter, &alteredFiles);

        directoryFree(dir);
        entryFree(bin);
        entryFree(builderFile);

        link(binDirPath, oFileList, builderFilePath);

        free(binDirPath);
        free(oFileList);

        char fileCounterC[16];
        char alteredFileCounterC[16];
        sprintf(fileCounterC, "%d", fileCounter);
        sprintf(alteredFileCounterC, "%d", alteredFiles);

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
        char prodPath[MAX_LENGTH_PATH];
        char debugPath[MAX_LENGTH_PATH];

        strcpy(prodPath, projectPath);
        strcpy(debugPath, projectPath);
        strcat(prodPath, "/target/prod");
        strcat(debugPath, "/target/debug");

        Directory *targetProd = directoryGet(prodPath);

        if (targetProd == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *targetDebug = directoryGet(debugPath);

        if (targetDebug == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        int fileCounterProd = directoryClear(targetProd);
        int fileCounterDebug = directoryClear(targetDebug);

        if (fileCounterProd == -1 || fileCounterDebug == -1)
        {
            printf("[ERROR] : Function directoryClear was not able to clear the directory | clear \n");
            return;
        }

        directoryFree(targetProd);
        directoryFree(targetDebug);

        char fileCounterProdC[16];
        char fileCounterDebugC[16];
        sprintf(fileCounterProdC, "%d", fileCounterProd);
        sprintf(fileCounterDebugC, "%d", fileCounterDebug);

        printf(SEPERATOR);
        printf(HEADING, "S U C C E S S");
        printf(LINE, "Files deleted in prod:", fileCounterProdC);
        printf(LINE, "Files deleted in debug:", fileCounterDebugC);
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

void testBuild(char *path)
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
        char builderFilePath[MAX_LENGTH_PATH];
        strcpy(builderFilePath, projectPath);
        strcat(builderFilePath, "/cbuilderfile");

        char binDirPath[MAX_LENGTH_PATH];
        strcpy(binDirPath, projectPath);
        strcat(binDirPath, "/src/test/bin");

        char srcPath[MAX_LENGTH_PATH];
        char destPath[MAX_LENGTH_PATH];
        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/main/c");
        strcat(destPath, "/src/test/src/project");

        copyProject(destPath, srcPath);

        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/test/src/main/c");
        strcat(destPath, "/src/test/src/main/genTests");

        List *mockList = generateTests(destPath, srcPath);

        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/test/src/project");
        strcat(destPath, "/src/test/target/project");

        int fileCounterProject = 0;
        int alteredFilesProject = 0;

        char *oFileListProject = compile(destPath, srcPath, projectPath, true, &fileCounterProject, &alteredFilesProject);

        strcpy(srcPath, projectPath);
        strcpy(destPath, projectPath);
        strcat(srcPath, "/src/test/src/main/genTests");
        strcat(destPath, "/src/test/target/test");

        int fileCounterTest = 0;
        int alteredFilesTest = 0;

        char *oFileListTest = compile(destPath, srcPath, projectPath, true, &fileCounterTest, &alteredFilesTest);

        List *tests = listCreate(sizeof(char *), &stringCopy, NULL);
        char *testOFiles = stringCreate(NULL);
        char *token = stringCreate(NULL);
        int c;

        for (int i = 0; i < strlen(oFileListTest); i++)
        {
            c = oFileListTest[i];

            if (isspace(c))
            {
                char *name = getFileNameWithPath(token);

                if (strlen(name) >= 6)
                {
                    char *sub = stringSub(name, 0, 3);

                    if (strcmp(sub, "test") == 0)
                    {
                        listAdd(tests, token);
                    }
                    else
                    {
                        testOFiles = stringCat(testOFiles, token);
                        testOFiles = stringCat(testOFiles, " ");
                    }

                    free(sub);
                }
                else
                {
                    testOFiles = stringCat(testOFiles, token);
                    testOFiles = stringCat(testOFiles, " ");
                }

                token = stringClear(token);

                free(name);
            }
            else
            {
                token = stringAdd(token, c);
            }
        }

        free(token);

        List *testExe = listCreate(sizeof(char *), &stringCopy, NULL);

        for (int i = 0; i < listLength(tests); i++)
        {
            char *testFile = listGet(tests, i);
            char *listFiles = stringCreate(testFile);

            listFiles = stringCat(listFiles, " ");
            listFiles = stringCat(listFiles, testOFiles);

            List *mockFiles = listGet(mockList, i);
            char *projectFiles = stringCreate(oFileListProject);

            for (int j = 0; j < listLength(mockFiles); j++)
            {
                char *mockName = listGet(mockFiles, j);
                char *token = stringCreate(NULL);
                int c;

                for (int k = 0; k < strlen(projectFiles); k++)
                {
                    c = projectFiles[k];

                    if (isspace(c))
                    {
                        char *name = getFileNameWithPathSplit(token);

                        if (name != NULL && strcmp(name, mockName) == 0)
                        {
                            projectFiles = stringReplace(projectFiles, token, "");
                        }

                        token = stringClear(token);

                        free(name);
                    }
                    else
                    {
                        token = stringAdd(token, c);
                    }
                }
                free(mockName);
                free(token);
            }

            listFiles = stringCat(listFiles, projectFiles);

            char *testName = getFileNameWithPath(testFile);
            testName = utilGetName(testName);

            char *binDirPathTemp = stringCreate(binDirPath);
            directoryCreate(binDirPathTemp, "separate");
            binDirPathTemp = stringCat(binDirPathTemp, "/separate");

            linkTest(binDirPathTemp, listFiles, builderFilePath, testName);

            binDirPathTemp = stringCat(binDirPathTemp, "/");
            binDirPathTemp = stringCat(binDirPathTemp, testName);
            listAdd(testExe, binDirPathTemp);

            free(testFile);
            free(listFiles);
            listFree(mockFiles);
            free(projectFiles);
            free(testName);
            free(binDirPathTemp);
        }

        free(testOFiles);
        listFree(tests);
        listFree(mockList);

        char pathExe[MAX_LENGTH_PATH];
        strcpy(pathExe, binDirPath);
        strcat(pathExe, "/test.c");

        FILE *file = fopen(pathExe, "w");

        char *baseFile = "#include <stdlib.h>\nint main(){\n\t";

        for (int i = 0; i < strlen(baseFile); i++)
        {
            c = baseFile[i];
            putc(c, file);
        }

        char *template = stringCreate("system(\"$PATH\");\n\t");
        char *templateLast = stringCreate("system(\"$PATH 1\");\n\t");

        for (int i = 0; i < listLength(testExe); i++)
        {
            char *testPath = listGet(testExe, i);
            char *templateTemp;
            if (i + 1 == listLength(testExe))
            {
                templateTemp = stringCreate(templateLast);
            }
            else
            {
                templateTemp = stringCreate(template);
            }
            templateTemp = stringReplace(templateTemp, "$PATH", testPath);

            for (int j = 0; j < strlen(templateTemp); j++)
            {
                c = templateTemp[j];
                putc(c, file);
            }

            free(testPath);
            free(templateTemp);
        }

        putc('\n', file);
        putc('}', file);

        fclose(file);
        listFree(testExe);
        free(template);
        free(templateLast);

        char oPath[MAX_LENGTH_PATH];
        strcpy(oPath, binDirPath);
        strcat(oPath, "/test.o");

        char *systemCommand = stringCreate(NULL);
        systemCommand = getCommand("debug", builderFilePath, systemCommand);
        systemCommand = stringReplace(systemCommand, "$CFILE", pathExe);
        systemCommand = stringReplace(systemCommand, "$OBJFILE", oPath);

        system(systemCommand);

        linkTest(binDirPath, oPath, builderFilePath, "test");

        remove(oPath);
        remove(pathExe);

        free(systemCommand);

        char fileCounterProjectC[16];
        char alteredFileCounterProjectC[16];
        sprintf(fileCounterProjectC, "%d", fileCounterProject);
        sprintf(alteredFileCounterProjectC, "%d", alteredFilesProject);

        char fileCounterTestC[16];
        char alteredFileCounterTestC[16];
        sprintf(fileCounterTestC, "%d", fileCounterTest);
        sprintf(alteredFileCounterTestC, "%d", alteredFilesTest);

        printf(SEPERATOR);
        printf(HEADING, "S U C C E S S");
        printf(LINE, "Files compiled (project):", alteredFileCounterProjectC);
        printf(LINE, "Files linked (project):", fileCounterProjectC);
        printf(LINE, "Files compiled (test):", alteredFileCounterTestC);
        printf(LINE, "Files linked (test):", fileCounterTestC);
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

void testClear(char *path)
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
        char targetProjectPath[MAX_LENGTH_PATH];
        char targetTestPath[MAX_LENGTH_PATH];
        char testProjectPath[MAX_LENGTH_PATH];
        char genTestPath[MAX_LENGTH_PATH];

        strcpy(targetProjectPath, projectPath);
        strcat(targetProjectPath, "/src/test/target/project");

        strcpy(targetTestPath, projectPath);
        strcat(targetTestPath, "/src/test/target/test");

        strcpy(testProjectPath, projectPath);
        strcat(testProjectPath, "/src/test/src/project");

        strcpy(genTestPath, projectPath);
        strcat(genTestPath, "/src/test/src/main/genTests");

        Directory *targetProjectPathDir = directoryGet(targetProjectPath);

        if (targetProjectPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *targetTestPathDir = directoryGet(targetTestPath);

        if (targetTestPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *testProjectPathDir = directoryGet(testProjectPath);

        if (testProjectPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        Directory *genTestPathDir = directoryGet(genTestPath);

        if (genTestPathDir == NULL)
        {
            printf("[ERROR] : Directory for the specified path was not found | clear \n");
            return;
        }

        int st1 = directoryClear(targetProjectPathDir);
        int st2 = directoryClear(targetTestPathDir);
        int st3 = directoryClear(testProjectPathDir);
        int st4 = directoryClear(genTestPathDir);

        if (st1 == -1 || st2 == -1 || st3 == -1 || st4 == -1)
        {
            printf("[ERROR] : Function directoryClear was not able to clear the directory | clear \n");
            return;
        }

        directoryFree(targetProjectPathDir);
        directoryFree(targetTestPathDir);
        directoryFree(testProjectPathDir);
        directoryFree(genTestPathDir);

        char st1C[16];
        char st2C[16];
        char st3C[16];
        char st4C[16];

        sprintf(st1C, "%d", st1);
        sprintf(st2C, "%d", st2);
        sprintf(st3C, "%d", st3);
        sprintf(st4C, "%d", st4);

        printf(SEPERATOR);
        printf(HEADING, "S U C C E S S");
        printf(LINE, "Files deleted in target/project:", st1C);
        printf(LINE, "Files deleted in target/test:", st2C);
        printf(LINE, "Files deleted in src/project:", st3C);
        printf(LINE, "Files deleted in main/genTests:", st4C);
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

char *getCommand(char *command, char *path, char *destCmd)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("[ERROR] : CBuilderfile could not be opened | getCommand \n");
        return NULL;
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
        return NULL;
    }

    destCmd = stringClear(destCmd);

    if (destCmd == NULL)
    {
        printf("[ERROR] : Function stringClear failed | getCommand \n");
        return NULL;
    }

    for (int i = 0; i < strlen(cmd); i++)
    {
        destCmd = stringAdd(destCmd, cmd[i]);

        if (destCmd == NULL)
        {
            printf("[ERROR] : Function stringAdd failed | getCommand \n");
            return NULL;
        }
    }

    free(cmd);
    free(tokenList);

    return destCmd;
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

    directoryFree(dirTarget);

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

    directoryFree(dirMain);

    Directory *dirTest = directoryGetSub(dirSrc, "test");

    if (dirTest == NULL)
    {
        directoryFree(dirSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTest, "bin", TYPE_DIRECTORY) || !directoryIsEntry(dirTest, "src", TYPE_DIRECTORY) || !directoryIsEntry(dirTest, "target", TYPE_DIRECTORY))
    {
        directoryFree(dirSrc);
        directoryFree(dirTest);
        return false;
    }

    directoryFree(dirSrc);

    Directory *dirTestSrc = directoryGetSub(dirTest, "src");

    if (dirTestSrc == NULL)
    {
        directoryFree(dirTest);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTestSrc, "main", TYPE_DIRECTORY) || !directoryIsEntry(dirTestSrc, "project", TYPE_DIRECTORY))
    {
        directoryFree(dirTest);
        directoryFree(dirTestSrc);
        return false;
    }

    Directory *dirTestMain = directoryGetSub(dirTestSrc, "main");

    if (dirTestMain == NULL)
    {
        directoryFree(dirTest);
        directoryFree(dirTestSrc);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTestMain, "c", TYPE_DIRECTORY) || !directoryIsEntry(dirTestMain, "genTests", TYPE_DIRECTORY))
    {
        directoryFree(dirTestMain);
        directoryFree(dirTest);
        directoryFree(dirTestSrc);
        return false;
    }

    directoryFree(dirTestMain);
    directoryFree(dirTestSrc);

    Directory *dirTestTarget = directoryGetSub(dirTest, "target");

    if (dirTestTarget == NULL)
    {
        directoryFree(dirTest);
        printf("[ERROR] : Could not find sub directory | isProject \n");
        return false;
    }

    if (!directoryIsEntry(dirTestTarget, "project", TYPE_DIRECTORY) || !directoryIsEntry(dirTestTarget, "test", TYPE_DIRECTORY))
    {
        directoryFree(dirTestTarget);
        directoryFree(dirTest);
        return false;
    }

    directoryFree(dirTest);
    directoryFree(dirTestTarget);

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

char *compile(char *destPath, char *srcPath, char *projectPath, bool debug, int *fileCounter, int *alteredFiles)
{
    Directory *dir = directoryGet(projectPath);

    if (dir == NULL)
    {
        printf("[ERROR] : Directory for the specified path was not found | build \n");
        return NULL;
    }

    Entry *builderFile = directoryGetEntry(dir, "cbuilderfile", TYPE_FILE);

    if (builderFile == NULL)
    {
        printf("[ERROR] : Entry for the specified directory was not found | build \n");
        return NULL;
    }

    char builderFilePath[MAX_LENGTH_PATH];
    strcpy(builderFilePath, entryGetPath(builderFile));

    char *systemCommand = stringCreate(NULL);
    char *cFile = stringCreate("$CFILE");
    char *objFile = stringCreate("$OBJFILE");

    char relTarget[MAX_LENGTH_PATH];

    char command[64];

    if (debug)
    {
        strcpy(command, "debug");
    }
    else
    {
        strcpy(command, "build");
    }

    systemCommand = getCommand(command, builderFilePath, systemCommand);

    char *commandBluePrint = stringCreate(systemCommand);

    directoryFree(dir);
    entryFree(builderFile);

    Directory *src = directoryGet(srcPath);

    if (src == NULL)
    {
        printf("[ERROR] : The c directory of the project was not found | build \n");
        return NULL;
    }

    Directory *target = directoryGet(destPath);

    if (target == NULL)
    {
        printf("[ERROR] : The %s directory of the project was not found | build \n", relTarget);
        return NULL;
    }

    Stack *stackSrc = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);
    Stack *stackTarget = stackCreate(directoryGetSize(), &directoryCopy, &directoryFree);

    if (stackSrc == NULL || stackTarget == NULL)
    {
        printf("[ERROR] : Function stackCreate failed | build \n");
        return NULL;
    }

    int st1 = stackPush(stackSrc, src);
    int st2 = stackPush(stackTarget, target);

    if (st1 == -1 || st2 == -1)
    {
        printf("[ERROR] : Function stackPush failed | build \n");
        return NULL;
    }

    *fileCounter = 0;
    *alteredFiles = 0;

    char *oFileList = stringCreate(NULL);

    char *delimiter = " ";
    char *objType = ".o";
    char *cType = ".c";
    char *slash = "/";

    while (stackLength(stackSrc) > 0)
    {
        Directory *tempSrc = stackPop(stackSrc);
        Directory *tempTarget = stackPop(stackTarget);

        if (tempSrc == NULL || tempTarget == NULL)
        {
            printf("[ERROR] : Function stackPop failed | build \n");
            return NULL;
        }

        for (int i = 0; i < directoryGetEntryAmount(tempSrc); i++)
        {
            Entry *tempEntrySrc = directoryGetEntryAt(tempSrc, i);

            if (tempEntrySrc == NULL)
            {
                printf("[ERROR] : Function directoryGetEntryAt failed | build \n");
                return NULL;
            }

            char *cPath = stringCreate(entryGetPath(tempEntrySrc));
            char *name = utilGetName(entryGetName(tempEntrySrc));
            char *type = utilGetEx(entryGetName(tempEntrySrc));
            char *objPath = stringCreate(directoryGetPath(tempTarget));
            char *objName = stringCreate(name);
            objName = stringCat(objName, objType);
            objPath = stringCat(objPath, slash);
            objPath = stringCat(objPath, name);
            objPath = stringCat(objPath, objType);

            if (entryGetType(tempEntrySrc) == TYPE_DIRECTORY)
            {
                Directory *newDirSrc = directoryGet(entryGetPath(tempEntrySrc));

                if (newDirSrc == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | build \n");
                    return NULL;
                }

                bool st3 = directoryCreate(directoryGetPath(tempTarget), entryGetName(tempEntrySrc));

                if (st3 == false)
                {
                    printf("[ERROR] : Function directoryCreate failed | build \n");
                    return NULL;
                }

                char temp[MAX_LENGTH_PATH];
                strcpy(temp, directoryGetPath(tempTarget));
                strcat(temp, slash);
                strcat(temp, entryGetName(tempEntrySrc));

                Directory *newDirTarget = directoryGet(temp);

                if (newDirTarget == NULL)
                {
                    printf("[ERROR] : Function directoryGet failed | build \n");
                    return NULL;
                }

                stackPush(stackSrc, newDirSrc);
                stackPush(stackTarget, newDirTarget);

                directoryFree(newDirSrc);
                directoryFree(newDirTarget);
            }

            else if (strcmp(type, cType) == 0)
            {
                (*fileCounter)++;

                Entry *tempEntryTarget = directoryGetEntry(tempTarget, objName, TYPE_FILE);

                systemCommand = stringReplace(systemCommand, cFile, cPath);
                systemCommand = stringReplace(systemCommand, objFile, objPath);

                if (tempEntryTarget != NULL && entryGetLastModified(tempEntryTarget) < entryGetLastModified(tempEntrySrc))
                {
                    (*alteredFiles)++;

                    int st4 = remove(entryGetPath(tempEntryTarget));

                    if (st4 != 0)
                    {
                        printf("[ERROR] : Function remove failed | build \n");
                        return NULL;
                    }
                    system(systemCommand);
                }
                else if (tempEntryTarget == NULL)
                {
                    (*alteredFiles)++;

                    system(systemCommand);
                }

                if (tempEntryTarget != NULL)
                {
                    entryFree(tempEntryTarget);
                }
                free(systemCommand);
                systemCommand = stringCreate(commandBluePrint);

                oFileList = stringCat(oFileList, objPath);
                oFileList = stringCat(oFileList, delimiter);
            }

            entryFree(tempEntrySrc);
            free(cPath);
            free(objPath);
            free(objName);
            free(type);
            free(name);
        }

        for (int i = 0; i < directoryGetEntryAmount(tempTarget); i++)
        {
            Entry *entryTarget = directoryGetEntryAt(tempTarget, i);
            bool doesExist = false;

            for (int j = 0; j < directoryGetEntryAmount(tempSrc); j++)
            {
                Entry *entrySrc = directoryGetEntryAt(tempSrc, j);

                if (entryGetType(entryTarget) == entryGetType(entrySrc))
                {
                    if ((entryGetType(entryTarget) == TYPE_DIRECTORY) && (strcmp(entryGetName(entryTarget), entryGetName(entrySrc)) == 0))
                    {
                        entryFree(entrySrc);
                        doesExist = true;
                        break;
                    }
                    else if ((entryGetType(entryTarget) == TYPE_FILE))
                    {
                        char *targetName = utilGetName(entryGetName(entryTarget));
                        char *targetEx = utilGetEx(entryGetName(entryTarget));
                        char *srcName = utilGetName(entryGetName(entrySrc));
                        char *srcEx = utilGetEx(entryGetName(entrySrc));

                        if (strcmp(targetName, srcName) == 0 && strcmp(targetEx, objType) == 0 && strcmp(srcEx, cType) == 0)
                        {
                            free(targetName);
                            free(targetEx);
                            free(srcName);
                            free(srcEx);
                            free(entrySrc);
                            doesExist = true;
                            break;
                        }
                        free(targetName);
                        free(targetEx);
                        free(srcName);
                        free(srcEx);
                    }
                }
                entryFree(entrySrc);
            }

            if (!doesExist)
            {
                if (entryGetType(entryTarget) == TYPE_DIRECTORY)
                {
                    Directory *tempDir = directoryGetSub(tempTarget, entryGetName(entryTarget));
                    directoryClear(tempDir);
                    directoryDelete(directoryGetPath(tempDir));

                    directoryFree(tempDir);
                }
                else
                {
                    remove(entryGetPath(entryTarget));
                }
            }

            entryFree(entryTarget);
        }

        directoryFree(tempSrc);
        directoryFree(tempTarget);
    }
    stackFree(stackSrc);
    stackFree(stackTarget);
    free(systemCommand);
    free(cFile);
    free(objFile);
    free(commandBluePrint);

    int fileCounterTemp = *fileCounter;
    int alteredFilesTemp = *alteredFiles;

    memcpy(fileCounter, &fileCounterTemp, sizeof(int));
    memcpy(alteredFiles, &alteredFilesTemp, sizeof(int));

    return oFileList;
}

char *getFileNameWithPath(char *path)
{
    char *name = stringCreate(NULL);
    int nameLength = 0;

    for (int i = strlen(path) - 1; i >= 0; i--)
    {
        if (path[i] != '/')
        {
            nameLength++;
        }
        else
        {
            break;
        }
    }

    for (int i = strlen(path) - nameLength, j = 0; i < strlen(path); i++, j++)
    {
        name = stringAdd(name, path[i]);
    }

    return name;
}

char *getFileNameWithPathSplit(char *path)
{
    char *name = stringCreate(NULL);
    int nameLength = 0;

    for (int i = strlen(path) - 1; i >= 0; i--)
    {
        if (path[i] != '_')
        {
            nameLength++;
        }
        else if (path[i] == '/')
        {
            free(name);
            return NULL;
        }
        else
        {
            break;
        }
    }

    for (int i = strlen(path) - nameLength, j = 0; i < strlen(path); i++, j++)
    {
        name = stringAdd(name, path[i]);
    }

    return name;
}

void link(char *destPath, char *files, char *builderFilePath)
{
    char *path = stringCreate(destPath);
    path = stringCat(path, "/temp.txt");
    FILE *file = fopen(path, "w");
    int c;

    for (int i = 0; i < strlen(files); i++)
    {
        c = files[i];

        putc(c, file);
    }

    char responseFile[4096];
    strcpy(responseFile, "@");
    strcat(responseFile, path);

    fclose(file);

    char linkCommand[] = "link";
    char *linkSystemCommand = stringCreate(NULL);
    char *objFiles = "$OBJFILES";
    char *binPath = "$BINPATH";
    char *permission = stringCreate("chmod a+x ");

    permission = stringCat(permission, destPath);

    linkSystemCommand = getCommand(linkCommand, builderFilePath, linkSystemCommand);

    linkSystemCommand = stringReplace(linkSystemCommand, objFiles, responseFile);
    linkSystemCommand = stringReplace(linkSystemCommand, binPath, destPath);

    system(linkSystemCommand);

#ifdef LINUX
    system(permission);
#elif defined(APPLE)
    system(permission);
#endif

    remove(path);

    free(linkSystemCommand);
    free(permission);
    free(path);
}

void linkTest(char *destPath, char *files, char *builderFilePath, char *name)
{
    char *path = stringCreate(destPath);
    path = stringCat(path, "/temp.txt");
    FILE *file = fopen(path, "w");
    int c;

    for (int i = 0; i < strlen(files); i++)
    {
        c = files[i];

        putc(c, file);
    }

    char responseFile[4096];
    strcpy(responseFile, "@");
    strcat(responseFile, path);

    fclose(file);

    char linkCommand[] = "linkTest";
    char *linkSystemCommand = stringCreate(NULL);
    char *objFiles = "$OBJFILES";
    char *binPath = "$BINPATH";
    char *permission = stringCreate("chmod a+x ");

    permission = stringCat(permission, destPath);

    linkSystemCommand = getCommand(linkCommand, builderFilePath, linkSystemCommand);

    destPath = stringCat(destPath, "/");
    destPath = stringCat(destPath, name);

    linkSystemCommand = stringReplace(linkSystemCommand, objFiles, responseFile);
    linkSystemCommand = stringReplace(linkSystemCommand, binPath, destPath);

    system(linkSystemCommand);

#ifdef LINUX
    system(permission);
#elif defined(APPLE)
    system(permission);
#endif

    remove(path);

    free(linkSystemCommand);
    free(permission);
    free(path);
}
