//
//  unionfind.c
//  alg4
//
//  Created by junl on 2020/8/18.
//  Copyright © 2020 junl. All rights reserved.
//

#include "unionfind.h"
#include <stdlib.h>
#include <stdio.h>
#include "csapp.h"

#define Dir "/Users/junl/Library/Mobile Documents/com~apple~CloudDocs/NOTE/alg/alg-cpp/alg4"
#define TinyUF "union-find/tinyUF.txt"

void uf_union_quickfind(UF*uf, int p, int q);
int uf_find_quickfind(UF*uf, int p);
void uf_union_quickuinon(UF*uf, int p, int q);
int uf_find_quickuinon(UF*uf, int p);



UF* uf_init(int n){
    UF *ctx = (UF*)malloc(sizeof(UF*));
    ctx->count = n;
    ctx->uf_len = n;
    ctx->id = (int *)malloc(sizeof(int) * n);
    int i;
    for (i=0; i<n; i++) {
        ctx->id[i] = i;
    }
    return ctx;
}

#define VERSION 1
//在p和q之间添加一条连接
void uf_union(UF*uf, int p, int q){
    void(*func)(UF*uf, int p, int q);
    if (VERSION == 1) {
        func = uf_union_quickfind;
    }else if (VERSION == 2) {
        func = uf_union_quickuinon;
    }
    func(uf, p, q);
}
//找到p所在的连通分量的标识
int uf_find(UF*uf, int p){
    int (*func)(UF*uf, int p);
    if (VERSION == 1) {
        func = uf_find_quickfind;
    }else if (VERSION == 2){
        func = uf_find_quickuinon;
    }
    return func(uf, p);
}
int uf_connected(UF* uf, int p, int q){
    //只要它们处于同一个连通分量中必定相连
    return uf_find(uf, p) == uf_find(uf, q);
}
int count(UF*uf){
    return uf->uf_len;
}
void test_unionfind(void){
    int n;
    char buf[MAXLINE];
    rio_t rio;
    int fd, p, q, N;
    UF *uf = NULL;
    N = -1;
    
    sprintf(buf, "%s/%s", Dir, TinyUF);
    fd = open(buf, O_RDONLY);
    Rio_readinitb(&rio, fd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        sscanf(buf,"%d %d",&p, &q);//把字符串s转换为整形数据并存入变量n中
        if (N == -1) {
            N = p;
            uf = uf_init(N);
            continue;
        }
        if (uf_connected(uf, p, q) == 1) continue;
        uf_union(uf, p, q);
        printf("%d %d\n",p, q);
    }
}
