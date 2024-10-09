//
// Created by lyk12 on 24-10-7.
//
#include <command.h>
#include <stdio.h>
#include <tool.h>
#include <step2.h>
#include <stdlib.h>
#include <windows.h>

void Checkout(int argc,char **argv) {

    if(argc<4) {
        printf("Parameter is missing\n");
        return;
    }
    if(strcmp(argv[2],"-f") == 0) {
        int rt = checkcode("",argv[3],".git\\caches\\index");
        if(rt==0) {
            printf("File does not exist\n");
            return ;
        }
        FILE *file = fopen(".git\\caches\\index", "r");
        char line[256];
        long pos = 0;
        // 遍历文件，查找是否存在
        while (fgets(line, sizeof(line), file)) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }
            char *str = strchr(line+41,' ');
            size_t le= str-line-41;
            char cmp[256];
            strncpy(cmp, line+41,le);
            cmp[le] = '\0';
            if(strcmp(cmp, argv[3])==0) {
                pos = ftell(file) - strlen(line);
                break;
            }
        }
        fseek(file, pos-2, SEEK_SET);
        char hash[41];
        char type[10];
        hash[40] = '\0';
        fread(hash, sizeof(char), 40, file);
        fclose(file);
        littlecat(hash, argv[3], type);
    }
    else if(strcmp(argv[2],"-v") == 0){
        char type[10];
        type[6] = '\0';
        littlecat(argv[3],".git\\caches\\temp1",type);
        if(strcmp(type,"commit")!=0) {
            printf("Unmatched type\n");
            return;
        }
        char hash[41];
        FILE *fp = fopen(".git\\caches\\temp1","r");
        fseek(fp, 5, SEEK_SET);
        fgets(hash,41, fp);
        hash[40] = '\0';
        fclose(fp);
        char tp[10];
        littlecat(hash, ".git\\caches\\temp1", tp);
        char buffer[200];
        FILE *fp1 = fopen(".git\\caches\\temp1","r");
        while(fgets(buffer, 200, fp1)) {
            char code[41];
            strncpy(code, buffer, 40);
            code[40] = '\0';
            char *str = strchr(buffer+41,' ');
            char t = *(str+1);
            if(t == '6') {
                continue;
            }
            size_t le= str-buffer-41;
            char name[256];
            strncpy(name, buffer+41,le);
            name[le] = '\0';
            littlecat(code, name, type);
        }
        fclose(fp1);
    }
    printf("changed successfully");
}