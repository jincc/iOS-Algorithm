//
//  weightedQuickUnion.h
//  alg4
//
//  Created by junl on 2020/8/19.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef weightedQuickUnion_h
#define weightedQuickUnion_h

#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
/*
 动态连通性问题:
 当程序输入整数对p,q时，如果已知的整数对不能说明p和q是相连的，那么连接它们，并输出。
 如果已知信息能够证明p和q相连，那么忽略p和q
 */

typedef struct{
    int *id; //触点内容
    int *sz;//保存每个触点的深度
    int count; //触点容量
    int uf_len;//连通向量的个数
}wq_uf;

//以整数标识初始化Ne个触点
wq_uf* wq_uf_init(int n);
//在p和q之间添加一条连接
void wq_uf_union(wq_uf*, int p, int q);
//找到p所在的连通分量的标识
int wq_uf_find(wq_uf*, int p);
//如果p和q存在于同一个连通分量中则返回true
int wq_uf_connected(wq_uf*, int p, int q);
//连通分量的数量
int wq_uf_count(wq_uf*);

//驱动程序
void test_wq_unionfind(void);
#ifdef __cplusplus
}
#endif
#endif /* weightedQuickUnion_h */
