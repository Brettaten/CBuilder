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