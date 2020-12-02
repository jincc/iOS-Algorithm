//
//  insert.c
//  sort
//
//  Created by junl on 2020/12/1.
//  Copyright © 2020 junl. All rights reserved.
//

#include "sort.h"
//依次将未排序数组中的元素插入到已排序数组中的指定位置
void sort_insert(ItemType a[], int l, int r){
    int i, j, min = l, v;
    for (i = l+1; i <= r; i++) {
        if (less(a[i], a[min])) min = i;
    }
    //数组a的第一个元素为最小元素, 避免内层循环的判断
    exch(a[min], a[l]);

    for (i = l + 2; i <= r ; i++) {
        v = a[i];
        for (j = i; less(v, a[j-1]); j--) {
            a[j] = a[j-1];//如果v比前一个元素小，向后移动一位
        }
        a[j] = v;
    }
}
