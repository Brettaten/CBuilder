#include "test.h"
#include <stdio.h>
#include <stdint.h>
#include "util/cbuilderTest.h"

int listAdd(){
    return 0;
}

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
    assert(1 == 0);
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
#include <string.h>
#include <stdlib.h>
#include "/home/elivagar/Programs/C/CBuilder/src/test/src/main/genTests/util/cbuilderTest.h"
int main(int argc, char *argv[]){
	int64_t before, after, time;
	strcpy(path,"/home/elivagar/Programs/C/CBuilder/src/test/src/main/genTests/util/temp.txt");
	bool isEnd = false;
	if(argc == 2){
		int end = atoi(argv[1]);
		if(end == 1){
			isEnd = true;
		}
	}
	getStats();
	passed = true;
	printf("TEST 1 | testPrintHappyFlow\n");
	before = getTime();
	testPrintHappyFlow();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	passed = true;
	printf("TEST 2 | testsdfsdfsd\n");
	before = getTime();
	testsdfsdfsd();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	passed = true;
	printf("TEST 3 | testasgddsg\n");
	before = getTime();
	testasgddsg();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	passed = true;
	printf("TEST 4 | testagdfsadf\n");
	before = getTime();
	testagdfsadf();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	passed = true;
	printf("TEST 5 | testasdgsdfsdf\n");
	before = getTime();
	testasdgsdfsdf();
	after = getTime();
	time = after - before;
	printf("Execution time: %lld ms", time);
	executionTime += time;
	testExe++;
	if(passed){
		printf(" | PASSED\n");
		testPassed++;
	} else{
		printf(" | FAILED\n");
		testFailed++;
	}
	if(isEnd && testExe > 0){
		printf("--------------------------------------------------\n");
		testPassedRel = ((double)testPassed / (double)testExe) * 100.0;
		testFailedRel = ((double)testFailed / (double)testExe) * 100.0;
		printf("Tests executed: %d | Total execution time: %d ms\n",testExe, executionTime);
		printf("Tests passed: %d | %.2f %%\n",testPassed, testPassedRel);
		printf("Tests failed: %d | %.2f %%\n",testFailed, testFailedRel);
		remove(path);
	} else if(isEnd && testExe == 0){
		printf("--------------------------------------------------\n");
		printf("No test was executed");
	}
	else{
		saveStats();
	}
}