//
//  sort.c
//  sort
//
//  Created by junl on 2020/12/1.
//  Copyright © 2020 junl. All rights reserved.
//

#include "sort.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
//统计算法完成时间
#define TIME_INIT \
clock_t start, end;
#define TIME_START \
start = clock();

#define TIME_END(msg) \
end = clock(); \
printf("%stime: %f s\n", msg, ((double)(end - start)) / CLOCKS_PER_SEC);

int check_sort(ItemType a[], int l, int r){
    for (; l < r; l++) {
        if (less(a[l+1], a[l])) {
            return 0;
        }
    }
    return 1;
}
void test_sort_drive(void){
    printf("-------------排序---------------------\n\n\n");
#define  N 10000
    ItemType items[N], i;
    ItemType sorts[N], rsorts[N], eqs[N],threes[N];
    for (i = 0; i < N ; i++) {
        items[i] = 1000 * (1.0 * rand() / RAND_MAX);
        sorts[i] = i;
        rsorts[i] = N - i;
        eqs[i] = 1;
        threes[i] = random() % 3;
    }
    void (*sortfunc)(ItemType items[], int l, int r);
    sortfunc = sort_heap;
    
    TIME_INIT;
    TIME_START;
    sortfunc(items, 0, N - 1);
    TIME_END("排序随机元素");
    
    TIME_START;
    sortfunc(sorts, 0, N - 1);
    TIME_END("排序已排序的数据源");
    
    TIME_START;
    sortfunc(rsorts, 0, N - 1);
    TIME_END("排序逆序的数据源");
    
    TIME_START;
    sortfunc(eqs, 0, N - 1);
    TIME_END("排序相同的数据源");
    
    TIME_START;
    sortfunc(threes, 0, N - 1);
    TIME_END("排序只有三种元素的数据源");
    
    assert(check_sort(items, 0, N-1) == 1);
    /*
     排序随机元素time: 0.021226 s
     排序已排序的数据源time: 0.001346 s
     排序逆序的数据源time: 0.012575 s
     */
}
