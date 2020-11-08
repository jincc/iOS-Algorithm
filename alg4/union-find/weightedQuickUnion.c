//
//  weightedQuickUnion.c
//  alg4
//
//  Created by junl on 2020/8/19.
//  Copyright © 2020 junl. All rights reserved.
//

#include "weightedQuickUnion.h"
#include <stdlib.h>
#include <stdio.h>
#include "csapp.h"

#define Dir "/Users/junl/Library/Mobile Documents/com~apple~CloudDocs/NOTE/alg/alg-cpp/alg4"
#define TinyUF "union-find/tinyUF.txt"
wq_uf* wq_uf_init(int n){
    wq_uf *ctx = (wq_uf*)malloc(sizeof(wq_uf*));
    ctx->count = n;
    ctx->uf_len = n;
    ctx->id = (int *)malloc(sizeof(int) * n);
    ctx->sz = (int *)malloc(sizeof(int) * n);
    int i;
    for (i=0; i<n; i++) {
        ctx->id[i] = i;
        ctx->sz[i] = 1;
    }
    return ctx;
}
//在p和q之间添加一条连接
void wq_uf_union(wq_uf*uf, int p, int q){
    int pRoot = wq_uf_find(uf, p);
    int qRoot = wq_uf_find(uf, q);
    if (pRoot == qRoot) return;
    
    //为了减少树的高度，始终将较小的树合并到较大的树，这样较小的树高度+1, 较大的树高度不变
    if (uf->sz[pRoot] < uf->sz[qRoot]){
        uf->id[pRoot] = qRoot;
        uf->sz[qRoot] += uf->sz[pRoot];
    }else{
        uf->id[qRoot] = pRoot;
        uf->sz[pRoot] += uf->sz[qRoot];
    }
    uf->count--;
}
//找到p所在的连通分量的标识
int wq_uf_find(wq_uf*uf, int p){
    while (uf->id[p] != p) {
        p = uf->id[p];
    }
    return p;
}
//如果p和q存在于同一个连通分量中则返回true
int wq_uf_connected(wq_uf*uf, int p, int q){
    return wq_uf_find(uf, p) == wq_uf_find(uf, q);
}
//连通分量的数量
int wq_uf_count(wq_uf*uf){
    return uf->count;
}

void test_wq_unionfind(void){
    int n;
    char buf[MAXLINE];
    rio_t rio;
    int fd, p, q, N;
    wq_uf *uf = NULL;
    N = -1;
    
    sprintf(buf, "%s/%s", Dir, TinyUF);
    fd = open(buf, O_RDONLY);
    Rio_readinitb(&rio, fd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        sscanf(buf,"%d %d",&p, &q);//把字符串s转换为整形数据并存入变量n中
        if (N == -1) {
            N = p;
            uf = wq_uf_init(N);
            continue;
        }
        if (wq_uf_connected(uf, p, q) == 1) continue;
        wq_uf_union(uf, p, q);
        printf("%d %d\n",p, q);
    }
}
