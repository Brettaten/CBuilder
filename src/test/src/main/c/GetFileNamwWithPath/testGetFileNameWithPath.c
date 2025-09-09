#include "testGetFileNameWithPath.h"
#include "../util/cbuilderTest.h"
#include "../../../../../main/c/Main/main.h"

#include <string.h>
#include <stdlib.h>

void testGetFileWithPathHappyFlow()
{
    char *path = "foo/test";

    char *res = getFileNameWithPath(path);

    assert(strcmp(res, "test") == 0);
}

char *stringCreate(char *value){
    char *temp = (char *) malloc(sizeof(char) * 10);

    strcpy(temp, "foo");

    return temp;
}
