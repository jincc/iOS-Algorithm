//
//  heapSort.h
//  sort
//
//  Created by junl on 2019/7/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef heapSort_hpp
#define heapSort_hpp

#include <stdio.h>

/*
  堆排序
  1. 建立堆结构
  2. 将最大元素移到数组末尾，那么堆结构就被破坏了，需要重新调整堆结构。
 */


void heapify(int nums[], int n, int i){
    //确保当前节点是子树里面最大的节点
    while (true) {
        int lc = 2*i+1;
        if (lc+1<n && nums[lc] < nums[lc+1]) {
            lc++;
        }
        if (lc<n && nums[lc] > nums[i]) {
            std::swap(nums[i], nums[lc]);
            i=lc;
        }else{
            break;
        }
    }
}

void heapSort(int nums[], int n){
    for (int i= n/2 - 1; i>=0;i--) {
        heapify(nums, n, i);
    }

    int j =n-1;
    while (j>0) {
        std::swap(nums[0], nums[j]);
        heapify(nums, j, 0);
        j--;
    }
}



#endif /* heapSort_hpp */
