//
//  quick.c
//  sort
//
//  Created by junl on 2020/12/2.
//  Copyright © 2020 junl. All rights reserved.
//

#include "sort.h"
int _partition(ItemType a[], int l, int r);
void sort_quick(ItemType a[], int l, int r){
    if (l >= r) return;
    int idx = _partition(a, l, r);
    sort_quick(a, l, idx-1);
    sort_quick(a, idx+1, r);
}
#if 1
void _setMid(ItemType a[], int l, int r){
    int min, mid = l + (r - l) / 2;
    if (less(a[l], a[r])){
        min = less(a[mid], a[r]) ? mid : r;
    }else{
        min = less(a[mid], a[l]) ? mid : l;
    }
    exch(a[r], a[min]);
}

int _partition(ItemType a[], int l, int r){
    _setMid(a, l, r);
    int t = a[r], i = l, j = l;//i代表比t小的数组的末尾
    for (; j < r; j++) {
        if (less(a[j], t)) {
            exch(a[j], a[i]);
            i++;
        }
    }
    exch(a[i], a[r]);
    return i;
}
#else
int _partition(ItemType a[], int l, int r){
    int t = a[l], i = l, j = r+1;
    while (1) {
        //从左边开始寻找第一个比t大的值
        for (; less(a[++i], t); )
            if (i == r) break;
        //从右边开始寻找第一个比t小的值
        for (; less(t, a[--j]); )
            if (j == l) break;
        if (i>=j) break;
        exch(a[i], a[j]);
    }
    exch(a[l], a[j]);
    return j;
}
#endif
