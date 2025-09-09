#include "test.h"
#include <stdio.h>
#include <stdint.h>

void testP1(){
    int z = 0;
    
    for(int64_t x = 0; x != 1000000000; x++){
        z++;
    }
    printf("%d\n", z);
}

void test2(){
    int z = 0;
    
    for(int64_t x = 0; x != 1000000000; x++){
        z++;
    }
    printf("%d\n", z);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "C:/Users/richt/Programmieren/C/CBuilder/src/test/src/main/genTests/util/cbuilderTest.h"
int main(int argc, char *argv[]){
	int64_t before, after, time;
	strcpy(path,"C:/Users/richt/Programmieren/C/CBuilder/src/test/src/main/genTests/util/temp.txt");
	bool isEnd = false;
	if(argc == 2){
		int end = atoi(argv[1]);
		if(end == 1){
			isEnd = true;
		}
	}
	getStats();
	passed = true;
	printf("TEST 6 | testP1\n");
	before = getTime();
	testP1();
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