#include <stdio.h>

#include "executionTime.h"

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
