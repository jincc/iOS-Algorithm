//
//  sort.h
//  sort
//
//  Created by junl on 2020/12/1.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef sort_h
#define sort_h

#include <stdio.h>

typedef int ItemType;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {ItemType t = A; A = B; B = t;}
#define compexch(A, B) if (less(B, A)) exch(A, B)

#ifdef __cplusplus
extern "C" {
#endif
void sort_bubble(ItemType a[], int l, int r);
void sort_insert(ItemType a[], int l, int r);
void sort_select(ItemType a[], int l, int r);
void sort_merge(ItemType a[], int l, int r);
void sort_quick(ItemType a[], int l, int r);
void sort_heap(ItemType a[], int l, int r);

typedef int(*Compare)(ItemType a[], int i, int j);
//驱动程序
void test_sort_drive(void);
#ifdef __cplusplus
}
#endif
#endif /* sort_h */
