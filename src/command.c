//
// Created by lyk12 on 24-9-19.
//
#include<command.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

command commands[100] = {
    {"init",Init},
    {"cat-file",Cat_file},
    {"hash-object",Hash_object},
    {"commit",Commit},
    {"log",Log},
    {"checkout",Checkout},
    {"ls-tree",Ls_tree},
    {"branch",Branch},
    {"tag",Tag},
    {"show-ref",Show_ref},
    {"add",Add},
    {"rm",Rm},
    {"ls-files",Ls_files},
    {"status",Status},
    {"check-ignore",Check_ignore},
    {NULL,NULL}
};//利用一个数组来存储命令


void execute_command(int argc, char **argv) {
    if (argc == 0) return;
    int state=0;
    //遍历寻找命令
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(argv[1], commands[i].name) == 0) {
            commands[i].handler(argc, argv);
            state=1;
        }
    }
    if(state==0) {
        printf("Command not found\n");
    }
}

