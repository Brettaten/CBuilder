#include <stdio.h>

#include "main.h"
#include "display.h"

int main(int argc, char *argv[]){

    if(argc == 1){
        printHelpGeneral();
    }
}

void printHelpGeneral()
{
    printf(SEPERATOR);
    printf(HEADING, "U S A G E");
    printf(LINE, "For general properties", "cbuilder [ARGUMENT]");
    printf(LINE, "For a specific command", "cbuilder [COMMAND] [ARGUMENTS]");
    printf(SEPERATOR);
    printf(HEADING, "C O M M A N D S");
    printf(LINE, "build");
    printf(SEPERATOR);
    printf(HEADING, "A R G U M E N T S");
    printf(LINE, "-V, --version", "displays the version of cbuilder on this machine");
    printf(SEPERATOR);
}
