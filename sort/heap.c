//
//  heap.c
//  sort
//
//  Created by junl on 2020/12/2.
//  Copyright © 2020 junl. All rights reserved.
//

#include "sort.h"

int cmp(ItemType a[], int i, int j) {
    return less(a[i], a[j]);
}
//上浮操作，将制定元素上浮到它应该在的位置
 void swim(ItemType a[], int n, int idx, Compare cmp){
    while (idx > 1 && cmp(a, idx/2, idx)) {
        exch(a[idx/2], a[idx]);
        idx /= 2;
    }
}
//下沉操作，将制定元素下沉到它应该在的位置
 void sink(ItemType a[], int n, int idx, Compare cmp){
    while (2 * idx <= n) {
        int j = 2 * idx;
        if (j+1 <= n && cmp(a, j, j+1)) {
            j++;
        }
        if (cmp(a, idx, j)) {
            //swap
            exch(a[idx], a[j]);
            idx = j;
        }else break;
    }
}
void sort_heap(ItemType a[], int l, int r){
    //构建初始堆
    int k, n;
    n = r - l + 1;
    for (k = n / 2; k >= 1; k--) {
        sink(a, n, k, cmp);
    }
    //依次将堆首的最大元素放到数组末尾，并将堆的大小缩短，直到堆被缩短完成
    for (k = n-1; k>1; ) {
        exch(a[1], a[k]);
        k--;
        sink(a, k, 1, cmp);
    }
}
