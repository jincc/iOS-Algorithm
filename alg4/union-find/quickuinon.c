//
//  quickuinon.c
//  alg4
//
//  Created by junl on 2020/8/18.
//  Copyright © 2020 junl. All rights reserved.
//

#include <stdio.h>
#include "unionfind.h"
int uf_find_quickuinon(UF*uf, int p){
    while (uf->id[p] != p) {
        p = uf->id[p];
    }
    return p;
}

void uf_union_quickuinon(UF*uf, int p, int q){
    int pRoot, qRoot;
    pRoot = uf_find_quickuinon(uf, p);
    qRoot = uf_find_quickuinon(uf, q);
    if (pRoot == qRoot) return;
    //合并: 将p连通区域的根节点合并到q连通区域中
    uf->id[pRoot] = qRoot;
    uf->count--;
}
