//
//  unionfind.h
//  alg4
//
//  Created by junl on 2020/8/18.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef unionfind_h
#define unionfind_h
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
    int count; //触点容量
    int uf_len;//连通向量的个数
}UF;

//以整数标识初始化Ne个触点
UF* uf_init(int n);
//在p和q之间添加一条连接
void uf_union(UF*, int p, int q);
//找到p所在的连通分量的标识
int uf_find(UF*, int p);
//如果p和q存在于同一个连通分量中则返回true
int uf_connected(UF*, int p, int q);
//连通分量的数量
int count(UF*);

//驱动程序
void test_unionfind(void);
#ifdef __cplusplus
}
#endif
#endif /* unionfind_h */
