#include "test.h"
#include <stdio.h>
#include <stdint.h>

void testPrintHappyFlow(){
    int z = 0;
    
    for(int64_t x = 0; x != 1000000000; x++){
        z++;
    }
    printf("%d\n", z);
}

void testsdfsdfsd(){
    int z = 0;
    
    for(int64_t x = 0; x != 1000000000; x++){
        z++;
    }
    printf("%d\n", z);
}

void testasgddsg(){
    int z = 0;
    
    for(int64_t x = 0; x != 1000000000; x++){
        z++;
    }
    printf("%d\n", z);
}

void testagdfsadf(){
    int z = 0;
    
    for(int64_t x = 0; x != 1000000000; x++){
        z++;
    }
    printf("%d\n", z);
}

void testasdgsdfsdf(){
    int z = 0;
    
    for(int64_t x = 0; x != 1000000000; x++){
        z++;
    }
    printf("%d\n", z);
}
#include <stdio.h>
#include "../util/executionTime/executionTime.h"
#include "../util/assert/assert.h"
int main(){
	int64_t before, after, time;
	printf("TEST 1 | testPrintHappyFlow\n");
	before = getTime();
	testPrintHappyFlow();
	after = getTime();
	time = after - before;
	printf("Execution time: %ld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	printf("TEST 2 | testsdfsdfsd\n");
	before = getTime();
	testsdfsdfsd();
	after = getTime();
	time = after - before;
	printf("Execution time: %ld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	printf("TEST 3 | testasgddsg\n");
	before = getTime();
	testasgddsg();
	after = getTime();
	time = after - before;
	printf("Execution time: %ld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	printf("TEST 4 | testagdfsadf\n");
	before = getTime();
	testagdfsadf();
	after = getTime();
	time = after - before;
	printf("Execution time: %ld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	printf("TEST 5 | testasdgsdfsdf\n");
	before = getTime();
	testasdgsdfsdf();
	after = getTime();
	time = after - before;
	printf("Execution time: %ld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	printf("--------------------------------------------------\n");
	testPassedRel = (testPassed / testExe) * 100;
	testFailedRel = (testFailed / testExe) * 100;
	printf("Tests executed: %d | Total execution time: %d\n",testExe, executionTime);
	printf("Tests passed: %d | %.2f %\n",testPassed, testPassedRel);
	printf("Tests failed: %d | %.2f %\n",testFailed, testFailedRel);
}