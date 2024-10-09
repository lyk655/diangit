#include <command.h>
#include <stdio.h>

int main(int argc,char *argv[]) {
    if(argc!=1) {
        execute_command(argc,argv);
    }
    else {
         printf("Please input a string\n");
    }
     return 0;
}