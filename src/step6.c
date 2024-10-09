//
// Created by lyk12 on 24-10-7.
//
#include <command.h>
#include <dirent.h>
#include <step2.h>
#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sha1.h>
#include "tool.h"



void Add(int argc,char **argv) {
    if(argc<3) {
        printf("Parameter is missing\n");
    }
    if(isdirorfile(argv[2])==2) {
        char *code1 =initobject(argv[2],"blob",1);
        int ret=checkcode(code1,argv[2],".git\\caches\\index");
        if(ret!=3) {
            updata(argv[2],code1,".git\\index",ret);
        }
        free(code1);
    }
    else if(isdirorfile(argv[2])==1){
        if(strcmp(argv[2],".")==0)
            treemaker(argv[2],1);
        else
            treemaker(argv[2],0);
    }
    else {
        printf("File not found\n");
    }
}
void Rm(int argc,char **argv) {
    if(argc<3) {
        printf("Parameter is missing\n");
    }
    if(isdirorfile(argv[2])==2) {
        char *code1 =initobject(argv[2],"blob",1);
        if(checkcode(code1,argv[2],".git\\caches\\index")==0) {
            printf("File not found\n");
            return;
        }
        int ret=checkcode(code1,argv[2],".git\\caches\\index");
        if(ret==3||ret==2) {
            updata(argv[2],code1,".git\\index",6);
        }
        free(code1);
        remove(argv[2]);
    }
    else {
        printf("File not found\n");
    }
}
void Ls_files(int argc,char **argv) {
    FILE *fp = fopen(".git\\caches\\index", "rb");
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp)) {
        char *str = strchr(buffer+41,' ');
        size_t le= str-buffer-41;
        char cmp[256];
        strncpy(cmp, buffer+41,le);
        cmp[le] = '\0';
        printf("%s\n",cmp);
    }
    fclose(fp);
}
void Check_ignore(int argc,char **argv) {
    if(argc<3) {
        printf("Parameter is missing\n");
        return;
    }
    if(is_ignored(argv[2])==1) {
        printf("file is ignored by .gitignore\n");
    }
    else if(is_ignored(argv[2])==0){
        printf("file is not ignored\n");
    }
    else {
        printf(".gitignore file missing.\n");
    }
}
void check_files(const char *path,int flag) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_name[0] != '.'&&is_ignored(entry->d_name)) {  // 忽略隐藏文件
            char full_path[MAX_PATH];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

            struct stat statbuf;
            if (stat(full_path, &statbuf) == -1) {
                perror("stat");
                continue;
            }

            // 检查是否为目录，递归处理
            if (S_ISDIR(statbuf.st_mode)) {
                check_files(full_path,flag);
            } else {
                char *code1 = initobject(full_path,"blob",1);
                int re =checkcode(code1,full_path+2,".git\\caches\\index");
                if(checkcode(code1,full_path+2,".git\\index")!=3) {
                    if(flag==1) {
                        if (re!=0&&re!=3) {
                            printf("%s\n", full_path+2);
                        }
                    }
                    else
                        if ((re==1||re==0)) {
                            printf("%s\n", full_path+2);
                        }
                }
                free(code1);
            }
        }
    }
    closedir(dp);
}
void Status(int argc,char **argv) {
    printf("On branch: master\n");
    printf("Untracked files:\n");
    check_files(".",0);
    printf("Changes not staged for commit:\n");
    check_files(".",1);
    FILE *f=fopen(".git\\index","r");
    printf("Changes to be committed:\n");
    char buf[300];
    while (fgets(buf, sizeof(buf), f) != NULL) {
        char *type = strchr(buf+41,' ');
        if(strcmp(type," 2\n")==0)
            printf("modified ");
        else if(strcmp(type," 1\n")==0)
            printf("rename ");
        else if(strcmp(type," 0\n")==0)
            printf("new file ");
        else if(strcmp(type," 6\n")==0)
            printf("deleted ");
        *type='\0';
        printf("%s\n", buf+41);
    }
    fclose(f);
}