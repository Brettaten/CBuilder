#include <stdio.h>
#include <stdlib.h>

#include "cbuilderTest.h"

#ifdef _WIN32
#include <windows.h>
int64_t getTime()
{
    int64_t ms = GetTickCount64();

    return ms;
}
#elif defined(__linux__)
#include <time.h>
int64_t getTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    int64_t milliseconds = ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;

    return milliseconds;
}
#elif defined(__APPLE__)
#include <time.h>
int64_t getTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    int64_t milliseconds = ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;

    return milliseconds;
}
#endif

bool passed = true;
int testExe = 0;
int testPassed = 0;
int testFailed = 0;
double testPassedRel = 0;
double testFailedRel = 0;
int executionTime = 0;
char path[4096];

void saveStats()
{
    char testExeChar[16];
    char testPassedChar[16];
    char testFailedChar[16];
    char executionTimeChar[16];

    sprintf(testExeChar, "%d", testExe);
    sprintf(testPassedChar, "%d", testPassed);
    sprintf(testFailedChar, "%d", testFailed);
    sprintf(executionTimeChar, "%d", executionTime);

    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        printf("[ERROR] : function fopen failed | saveStats \n");
        return;
    }

    fprintf(file, "%s\n", testExeChar);
    fprintf(file, "%s\n", testPassedChar);
    fprintf(file, "%s\n", testFailedChar);
    fprintf(file, "%s\n", executionTimeChar);

    fclose(file);
}

void getStats()
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        return;
    }

    int values[4];
    char token[1024];
    int counter = 0;

    while (fgets(token, sizeof(token), file) != NULL)
    {
        values[counter] = atoi(token);
        counter++;
    }

    testExe = values[0];
    testPassed = values[1];
    testFailed = values[2];
    executionTime = values[3];

    fclose(file);
}

void assert(bool condition)
{
    if(!condition){
        passed = false;
    }
}