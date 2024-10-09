//
// Created by lyk12 on 24-10-7.
//
#include <command.h>
#include <dirent.h>
#include <stdio.h>
#include <tool.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/stat.h>
void refprintf(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_name[0] != '.') {
            // 忽略隐藏文件
            if(strcmp(entry->d_name,"master")==0) {
                printf("*");
            }
            printf(" %s\n",entry->d_name);
        }
    }
    closedir(dp);
}
void Branch(int argc,char **argv) {
    if(argc<2) {
        printf("Parameter is missing\n");
        return;
    }
    char path[260]=".git\\refs\\heads";
    if(argc==2) {
        refprintf(".git\\refs\\heads");
        return;
    }
    strcat(path,"\\");
    strcat(path,argv[2]);
    if(isdirorfile(path)!=0) {
        printf("A branch named '%s' already exists.\n",argv[2]);
        return ;
    }
    FILE *fp=fopen(".git\\refs\\heads\\master","rb");
    FILE *fp1=fopen(path,"wb");
    if(fp&&fp1) {
        char buffer[41];
        buffer[40]='\0';
        fread(buffer,1,40,fp);
        fwrite(buffer, 1, strlen(buffer), fp1);
        fclose(fp);
        fclose(fp1);
    }
    else {
        printf("Failed to create a new branch\n");
    }
}
void Tag(int argc,char **argv) {
    if(argc<2) {
        printf("Parameter is missing\n");
        return;
    }
    char path[260]=".git\\refs\\tags";
    if(argc==2) {
        refprintf(".git\\refs\\tags");
        return;
    }
    strcat(path,"\\");
    strcat(path,argv[2]);
    if(isdirorfile(path)!=0) {
        printf("A tag named '%s' already exists.\n",argv[2]);
        return ;
    }
    FILE *fp=fopen(".git\\refs\\heads\\master","rb");
    FILE *fp1=fopen(path,"wb");
    if(fp&&fp1) {
        char buffer[41];
        buffer[40]='\0';
        fread(buffer,1,40,fp);
        fwrite(buffer, 1, strlen(buffer), fp1);
        fclose(fp);
        fclose(fp1);
    }
    else {
        printf("Failed to create a new tag\n");
    }
}
void Show_ref(int argc,char **argv) {
    printf("Branch: \n");
    refprintf(".git\\refs\\heads");
    printf("Tag: \n");
    refprintf(".git\\refs\\tags");
}