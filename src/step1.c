//
// Created by lyk12 on 24-10-7.
//
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <tool.h>
void Init(int argc,char **argv) {
    char path[260];
    //根据输入找到创建仓库的地址
    if(argc!=2) {
        strcpy(path,argv[2]);
    }else {
        char cwd[260];
        getcwd(cwd,sizeof(cwd));
        strcpy(path,cwd);
    }
    //判断仓库是否创建
    if(checkdir("",path)+checkdir("\\.git",path)+checkdir("\\.git\\branch",path)+checkdir("\\.git\\objects",path)+checkdir("\\.git\\refs",path)==5) {
        printf("Already existing repository,reinitialized?[Y/N]\n");
        char choice = getchar();
        if(choice == 'N') {
            return ;
        }
    }
    checkdir("\\.git\\caches",path);
    checkdir("\\.git\\refs\\tags",path);
    checkdir("\\.git\\refs\\heads",path);
    checkfile("\\.git\\refs\\heads\\master",path,"e0dc1f1ba1573497d82d4248e6d5064088a7f599");
    checkfile("\\.git\\description",path,"Unnamed repository; edit this file 'description' to name the repository.\n");
    checkfile("\\.git\\config",path,"repositoryformatversion=0\nfilemode=false\nbare=1\n");
    checkfile("\\.git\\ref",path,"ref: refs\\heads\\master\n");//创建所需文件
    checkfile("\\.git\\caches\\index",path,"");
    checkfile("\\.git\\index",path,"");
    printf("Initialized Git repository in %s\\.git\\\n",path);
}