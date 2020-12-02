//
//  merge.c
//  sort
//
//  Created by junl on 2020/12/1.
//  Copyright © 2020 junl. All rights reserved.
//

#include "sort.h"
void _merge(ItemType a[], ItemType aux[], int l, int mid, int r);
void _sort_merge(ItemType a[], ItemType aux[], int l, int r);
void sort_merge(ItemType a[], int l, int r){
    int sz = r - l + 1;
    //利用辅助数组，避免频繁创建数组带来的消耗
    ItemType aux[sz];
    _sort_merge(a, aux, l, r);
}
void _sort_merge(ItemType a[], ItemType aux[], int l, int r){
    if (l >= r) return;
    int mid = l + (r - l)/2;
    //先将左右两半分别排序，然后将结果合并起来
    _sort_merge(a, aux, l, mid);
    _sort_merge(a, aux, mid+1, r);
    _merge(a, aux, l, mid, r);
}
void _merge(ItemType a[], ItemType aux[], int l, int mid, int r){
    int i = l, j = mid+1, k;
    for (k=l; k<=r; k++) {
        aux[k] = a[k];
    }
    //原地排序
    for (k=l; k<=r; k++) {
        if (i > mid) {
            a[k] = aux[j++];
        }else if (j > r){
            a[k] = aux[i++];
        }else if (less(aux[i], aux[j])) {
            a[k] = aux[i++];
        }else{
            a[k] = aux[j++];
        }
    }
}
