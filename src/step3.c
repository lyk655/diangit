//
// Created by lyk12 on 24-10-7.
//
#include <command.h>
#include <stdio.h>
#include <tool.h>
#include <step2.h>
#include <stdlib.h>
#include <windows.h>
#include <sha1.h>
#include <string.h>

void Commit(int argc, char **argv) {
    if (argc < 4) {
        printf("Parameter is missing\n");
        return;
    }

    char buffer[100];
    gettime(buffer); // Read time

    char *temp = ".git\\caches\\committemp";
    if (strcmp("-m", argv[2]) != 0) {
        printf("Invalid flag for commit, expected `-m'\n");
        return;
    }

    FILE *fp = fopen(".git\\index", "rb");
    fseek(fp, 0, SEEK_END); // 移动到文件末尾
    long size = ftell(fp);   // 获取当前位置（文件大小）
    fseek(fp, 0, SEEK_SET);
    if (size == 0){
        fclose(fp);
        printf("No changes added to commit (use \"add\" to track)\n");
        return;
    }

    char hash[41] = {0};
    char *code = initobject(".git\\index", "tree", 1);
    char buf[100] = {0};
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        char hashcode[41] = {0};
        size_t len = strlen(buf);
        if (len > 0) {
            strncpy(hashcode, buf, 40);
            hashcode[40] = '\0';
            char *str = strchr(buf+41,' ');
            char mode=*(str+1);
            size_t le= str-buf-41;
            char cmp[256];
            strncpy(cmp, buf+41,le);
            cmp[le] = '\0';
            if(mode=='6') {
                linedelete(cmp);
            }
            else {
                updata(cmp, hashcode, ".git\\caches\\index",0);
            }
        }
    }
    fclose(fp);
    strcpy(hash, code);
    FILE *fp3 = fopen(temp, "wb");
    if (!fp3) {
        perror("Failed to open commit temp file");
        return;
    }

    char data[500];
    snprintf(data, sizeof(data), "tree %s\ncommit time %s\n%s\n", hash, buffer, argv[3]);
    fwrite(data, 1, strlen(data), fp3);
    fclose(fp3);

    char comhash[41] = {0};
    char *code1 = initobject(temp, "commit", 1);
    strcpy(comhash, code1);
    free(code1);

    char logdata[200];
    snprintf(logdata, sizeof(logdata), "%s\n%s\n%s\n", comhash, argv[3], buffer);
    FILE *fp2 = fopen(".git/logs", "a");
    if (fp2) {
        fwrite(logdata, 1, strlen(logdata), fp2);
        fclose(fp2);
        printf("Commit successfully!\n");
    } else {
        printf("Failed to write to log file!\n");
    }

    FILE *f1 = fopen(".git/index", "w");
    if (f1) {
        fclose(f1);
    }
    free(code);
}



void Log(int argc,char **argv) {
    FILE *fp = fopen(".git\\logs","rb");
    if(fp) {
        while (!feof(fp)) {
            char buffer[1024];
            size_t bytesRead = fread(buffer, 1, sizeof(buffer), fp);
            if (bytesRead > 0) {
                fwrite(buffer, 1, bytesRead, stdout);
            }
        }
        fclose(fp);
    }
}


void Ls_tree(int argc,char **argv) {
    if(argc<3) {
        printf("Parameter is missing\n");
    }
    else if(argc==3) {
        char type[10];
        littlecat(argv[2],".git\\caches\\checktree",type);
        FILE *fp=fopen(".git\\caches\\checktree","rb");
        if(fp) {
            char buffer[50];
            fgets(buffer, sizeof(buffer), fp);
            char hash[41];
            strncpy(hash,buffer+5,40);
            hash[40]='\0';
            char *cat[]={"git","cat",hash};
            Cat_file(3,cat);
            remove(".git\\caches\\checktree");
        }
        else {
            perror("Error");
        }
    }
}