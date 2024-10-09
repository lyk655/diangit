//
// Created by lyk12 on 24-10-7.
//

#ifndef TOOL_H
#define TOOL_H
void gettime(char *buf);

int isdirorfile(const char* path);

int checkdir(const char *path,const char* dir);

int checkfile(const char *path,const char *gitdir,const char *data);

int updata(const char *filename, const char *hash,const char *dir,int mode);

void treemaker(const char *path,int mode);

int checkcode(const char *hash,const char *filename,const char *dir);

void linedelete(const char *filename);

int is_ignored(const char *filename);
#endif //TOOL_H
