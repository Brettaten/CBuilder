#include "test.h"
#include <stdio.h>

void testPrintHappyFlow(){
    int x = 10;
    printf("%d", x);
}
#include <stdio.h>
#include <time.h>
int main(){
	printf("TEST 1 | testPrintHappyFlow");
	time_t before = time(NULL);
	testPrintHappyFlow();
	time_t after = time(NULL);
	time_t time = after - before;
	printf("%ld", time);
}