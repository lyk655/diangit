//
// Created by lyk12 on 24-10-7.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sha1.h>
#include <compress.h>
#include <tool.h>
char *initobject(char *filepath, char *fmt,int flag) {
    char *temppath = ".git\\caches\\temp";

    // 打开源文件
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) {
        printf("Error opening file %s\n", filepath);
        return NULL;
    }

    // 获取文件大小并分配内存
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);  // 重置文件指针

    char *tmp = malloc((file_size + 1) * sizeof(char));
    if (tmp == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    // 读取文件内容
    fread(tmp, sizeof(char), file_size, fp);
    fclose(fp);
    tmp[file_size] = '\0';  // 确保末尾有 null 终止符

    // 构造 Git 对象格式，格式化文件大小
    char path[256];
    snprintf(path, sizeof(path), "%s %d %s", fmt, file_size, tmp);
    free(tmp);
    // 计算 SHA1 哈希值
    unsigned char hash[20];
    char *output_hex = malloc(41 * sizeof(char));
    if (output_hex == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    SHA1(hash, path, strlen(path));
    for (int i = 0; i < 20; i++) {
        sprintf(output_hex + (i * 2), "%02x", hash[i]);
    }
    output_hex[40] = '\0';  // 计算哈希值字符串
    if(flag==0) {
        return output_hex;
    }
    // 创建 Git 对象的存储路径
    char *head = malloc(sizeof(char) * 3);
    if (head == NULL) {
        printf("Memory allocation failed\n");
        free(output_hex);
        return NULL;
    }

    char *name = strdup(output_hex + 2);
    if (name == NULL) {
        printf("Memory allocation failed\n");
        free(output_hex);
        free(head);
        return NULL;
    }
    strncpy(head, output_hex, 2);
    head[2] = '\0';
    char newpath[256] = ".git\\objects\\";
    strcat(newpath, head);
    checkdir("", newpath);  // 检查目录
    snprintf(newpath, sizeof(newpath), ".git\\objects\\%s\\%s", head, name);
    free(head);
    free(name);

    // 将对象内容写入临时文件
    FILE *fp2 = fopen(temppath, "wb");
    if (fp2) {
        fwrite(path, sizeof(char), strlen(path), fp2);
        fclose(fp2);
    } else {
        printf("Error opening temp file for writing\n");
        free(output_hex);
        return NULL;
    }

    // 压缩临时文件并将其写入对象目录
    if (compressFile(temppath, newpath) != -1) {// 释放临时分配的内存
        return output_hex;
    }

    // 失败则清理内存
    free(output_hex);
    return NULL;
}
void Hash_object(int argc,char **argv) {
    if(argc<4) {
        printf("Parameter is missing\n");
        return;
    }
    char *hash=initobject(argv[3],argv[2],1);
    printf("%s\n",hash);
    free(hash);
}

void littlecat(const char *hashcode, const char *writepath,char *type) {
    char *head=malloc(sizeof(char)*3);
    char *name =strdup(hashcode+2);
    strncpy(head, hashcode, 2);
    head[2] = '\0';
    char path[256];
    snprintf(path,sizeof(path),".git\\objects\\%s\\%s",head,name);
    free(head);
    free(name);
    char *destpath = ".git\\caches\\temp";
    int result = decompressFile(path, destpath);  // 解压对象文件
    if (result == -1) {
        printf("Decompress failed\n");
        return;
    }

    FILE *fp = fopen(destpath, "rb");
    FILE *fp3 = fopen(writepath, "wb");

    if (fp) {
        char buffer[1024];

        int bytesRead = fread(buffer, 1, sizeof(buffer), fp);  // 读取头部

        // 找到缓冲区中的空格位置
        char *space_pos = memchr(buffer, ' ', bytesRead);
        char *null_pos = memchr(space_pos + 1, ' ', bytesRead);

        int x = space_pos - buffer;
        int y = null_pos - buffer;

        strncpy(type,buffer,x);  // 提取对象类型

        fseek(fp, y + 1, SEEK_SET);  // 将文件指针移动到第二个空格之后

        // 循环读取并写入内容
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            if (fp3) {
                fwrite(buffer, 1, bytesRead, fp3);  // 写入文件
            } else {
                fwrite(buffer, 1, bytesRead, stdout);  // 输出到控制台
            }
        }
    } else {
        printf("Error opening file %s\n", destpath);
    }

    fclose(fp3);
    fclose(fp);
}


void Cat_file(int argc, char **argv) {
    if (argc < 3) {
        printf("Parameter is missing\n");
        return;
    }
    char type[6];
    littlecat(argv[2], NULL,type);
}