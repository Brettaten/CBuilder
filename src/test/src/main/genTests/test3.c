#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util/cbuilderTest.h"
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
	if(isEnd && testExe > 0){
		printf("--------------------------------------------------\n");
		testPassedRel = (testPassed / testExe) * 100;
		testFailedRel = (testFailed / testExe) * 100;
		printf("Tests executed: %d | Total execution time: %d\n",testExe, executionTime);
		printf("Tests passed: %d | %.2f %\n",testPassed, testPassedRel);
		printf("Tests failed: %d | %.2f %\n",testFailed, testFailedRel);
		remove(path);
	} else if(isEnd && testExe == 0){
		printf("--------------------------------------------------\n");
		printf("No test was executed");
	}
	else{
		saveStats();
	}
}