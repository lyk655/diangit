//
// Created by lyk12 on 24-9-19.
//
#include <stdio.h>
#include <stdlib.h>
#include "zlib.h"
#include"compress.h"


#define CHUNK 16384

int compressFile(const char *source, const char *dest) {
    FILE *src = fopen(source, "rb");
    if(!src) printf("1Failed to open files. %s\n",source);
    FILE *dst = fopen(dest, "wb");//打开源文件与目标文件
    if(!dst) printf("2Failed to open files. %s\n",dest);
    if (!src || !dst) {
        return -1;
    }
    z_stream strm;//初始化一个流式对象

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;//成员设置
    int ret = deflateInit(&strm, Z_BEST_COMPRESSION);
    if (ret != Z_OK) {
        fclose(src);
        fclose(dst);
        return ret;
    }
    int flush;
    do {
        unsigned char in[CHUNK];
        strm.avail_in = fread(in, 1, CHUNK, src);
        if (ferror(src)) {
            deflateEnd(&strm);
            fclose(src);
            fclose(dst);
            return Z_ERRNO;
        }
        flush = feof(src) ? Z_FINISH : Z_NO_FLUSH;

        strm.next_in = in;//从缓存区读取对象

        do {
            unsigned char out[CHUNK];
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);
            if (ret == Z_STREAM_ERROR) {
                deflateEnd(&strm);
                fclose(src);
                fclose(dst);
                return Z_STREAM_ERROR;
            }
            size_t have = CHUNK - strm.avail_out;
            fwrite(out, 1, have, dst);
            if (ferror(dst)) {
                deflateEnd(&strm);
                fclose(src);
                fclose(dst);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
    } while (flush != Z_FINISH);//循环压缩至结束
    deflateEnd(&strm);
    fclose(src);
    fclose(dst);

    return Z_OK;
}
int decompressFile(const char *source, const char *dest) {
    FILE *src = fopen(source, "rb");
    if(!src) printf("1Failed to open files. %s\n",source);
    FILE *dst = fopen(dest, "wb");//打开源文件与目标文件
    if(!dst) printf("2Failed to open files. %s\n",dest);
    if (!src || !dst) {
        return -1;
    }
    z_stream strm;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = inflateInit(&strm);
    if (ret != Z_OK) {
        fclose(src);
        fclose(dst);
        return ret;
    }
    do {
        unsigned char in[CHUNK];
        strm.avail_in = fread(in, 1, CHUNK, src);
        if (ferror(src)) {
            inflateEnd(&strm);
            fclose(src);
            fclose(dst);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        do {
            unsigned char out[CHUNK];
            strm.avail_out = CHUNK;
            strm.next_out = out;

            ret = inflate(&strm, Z_NO_FLUSH);
            if (ret == Z_STREAM_ERROR) {
                inflateEnd(&strm);
                fclose(src);
                fclose(dst);
                return Z_STREAM_ERROR;
            }

            size_t have = CHUNK - strm.avail_out;
            fwrite(out, 1, have, dst);
            if (ferror(dst)) {
                inflateEnd(&strm);
                fclose(src);
                fclose(dst);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
    } while (ret != Z_STREAM_END);
    inflateEnd(&strm);
    fclose(src);
    fclose(dst);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
