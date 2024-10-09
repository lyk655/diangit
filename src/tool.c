//
// Created by lyk12 on 24-10-7.
//
#include <direct.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <step2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <sys/stat.h>
void gettime(char *buf) {
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    strftime(buf, 100*sizeof(char), "%Y-%m-%d %H:%M:%S", local);
}


int isdirorfile(const char* path) {
    struct stat statbuf;
    if(stat(path,&statbuf)) {
        return 0;
    }
    return   S_ISDIR(statbuf.st_mode)==1 ?1:2;
}


int checkdir(const char *path,const char* dir) {
    char newpath[260];
    strcpy(newpath, dir);
    strcat(newpath,path);
    if(isdirorfile(newpath)==1) {
        return 1;
    }
    _mkdir(newpath);
    return 0;
}


int is_ignored(const char *filename) {
    FILE *fp = fopen(".git\\.gitignore", "r");
    if (!fp) {
        return -1;
    }
    char buf[50]={0};
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        int len = strlen(buf);
        if (len != 0) {
            // 移除换行符
            if (buf[len - 1] == '\n') {
                buf[len - 1] = '\0';
            }
            // 检查是否匹配
            if (strcmp(buf, filename) == 0) {
                fclose(fp);
                return 1;
            }
        }
        memset(buf, 0, sizeof(buf));
    }
    fclose(fp);
    return 0;  // 文件未被忽略
}


int checkfile(const char *path,const char *gitdir,const char *data) {
    char newpath[256];
    strcpy(newpath,gitdir);
    strcat(newpath,path);
    int state=isdirorfile(newpath);
    if(state==0) {
        FILE *fp = fopen(newpath,"wb");
        if(fp) {
            fprintf(fp,data);
            fclose(fp);
        }
    }
    return state;
}

void updata(const char *filename, const char *hash,const char *dir,int mode) {
    FILE *file = fopen(dir, "r+");
    char line[256];
    int found = 0;
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
        if (strcmp(cmp, filename) == 0) {
            found = 1;
            pos = ftell(file) - strlen(line);
            break;
        }
    }
    if (found) {
        fseek(file, pos-2, SEEK_SET);
        fprintf(file, "%s %s %d\n", hash,filename,mode);
    } else {
        fprintf(file, "%s %s %d\n", hash,filename,mode);
    }
    fclose(file);
}


int checkcode(const char *hash,const char *filename,const char *dir) {
    FILE *file = fopen(dir, "r+");
    char line[256];
    int found = 0;
    int found1 = 0;
    // 遍历文件，查找是否存在
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0)
            line[len - 1] = '\0';
        char *str = strchr(line+41,' ');
        size_t le= str-line-41;
        char cmp[256];
        strncpy(cmp, line+41,le);
        cmp[le] = '\0';
        if(strcmp(filename, cmp) == 0)
            found1 = 1;
        char buffer[41];
        buffer[40]='\0';
        strncpy(buffer, line, 40);
        if (strcmp(buffer, hash) == 0) {
            found=1;
            break;
        }
    }
    fclose(file);
    if (found == 1 && found1 == 1) {
        return 3;
    }
    if (found == 1) {
        return 1;
    }
    if (found1 == 1) {
        return 2;
    }
    return 0;

}


void treemaker(const char *path,int mode) {
    struct dirent *entry;
    DIR *dp = opendir(path);
    while ((entry = readdir(dp))) {
        if (entry->d_name[0] != '.'&&is_ignored(entry->d_name)!=1) {  // 忽略隐藏文件
            char full_path[256];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            struct stat statbuf;
            if (stat(full_path, &statbuf) == -1) {
                perror("stat");
                continue;
            }
            // 检查是否为目录，递归处理
            if (S_ISDIR(statbuf.st_mode)) {
                treemaker(full_path,mode);
            } else {
                char *code1 =initobject(full_path,"blob",1);
                int rt=checkcode(code1,full_path+2,".git\\caches\\index");
                if(mode==1) {
                    if(rt!=3) {
                        updata(full_path+2,code1,".git\\index",rt);
                    }
                }
                else {
                    if(rt!=3) {
                        updata(full_path,code1,".git\\index",rt);
                    }
                }
                free(code1);
            }
        }
    }
    closedir(dp);
}

void linedelete(const char *filename) {
    FILE *fp=fopen(".git\\caches\\tempindex","w");
    FILE *fp1=fopen(".git\\caches\\index","r");
    if(fp&&fp1) {
        char buf[300];

        while (fgets(buf, sizeof(buf), fp1) != NULL) {
            // 移除换行符
            size_t len = strlen(buf);
            if (len > 0 && buf[len - 1] == '\n') {
                buf[len - 1] = '\0';
            }
            char *str = strchr(buf+41,' ');
            size_t le= str-buf-41;
            char cmp[256];
            strncpy(cmp, buf+41,le);
            cmp[le] = '\0';
            if (strcmp(cmp, filename) != 0) {
                fputs(buf, fp);
                fputs("\n", fp);
            }
        }
    }
    fclose(fp1);
    fclose(fp);
    remove(".git\\caches\\index");
    rename(".git\\caches\\tempindex", ".git\\caches\\index");
}