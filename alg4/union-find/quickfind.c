//
//  quickfind.c
//  alg4
//
//  Created by junl on 2020/8/18.
//  Copyright © 2020 junl. All rights reserved.
//
#include "unionfind.h"
//在p和q之间添加一条连接
void uf_union_quickfind(UF*uf, int p, int q){
    int pid = uf->id[p];
    int qid = uf->id[q];
    //代表已经相连
    if (pid == qid) return;
    
    //合并两个连通向量
    for (int i=0; i < uf->count; i++) {
        if (uf->id[i] == pid)
            uf->id[i] = qid;
    }
    uf->count--;
}
//找到p所在的连通分量的标识
int uf_find_quickfind(UF*uf, int p){
    return uf->id[p];
}
