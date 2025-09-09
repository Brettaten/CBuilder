#include <stdint.h>
#include <stdbool.h>

/**
 * Function used to test a function. If just one assert per test is false, it will fail
 * 
 * @param condition
 */
void assert(bool condition);

/**
 * Platform independent function that returns the time in milliseconds
 */
int64_t getTime();

/**
 * Function used to save stats between multiple test files
 */
void saveStats();

/**
 * Function used to save stats between multiple test files
 */
void getStats();

extern bool passed;
extern int testExe;
extern int testPassed;
extern int testFailed;
extern double testPassedRel;
extern double testFailedRel;
extern int executionTime;
extern char path[4096];