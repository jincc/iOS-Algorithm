//
//  bubbleSort.h
//  sort
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bubbleSort_hpp
#define bubbleSort_hpp

#include <stdio.h>
/*
  1. 通过一次排序，将一个元素（比如最大元素）移动到正确的位置
  2. 重复N次
 
 Tip：
    为了保证稳定性，当两个元素相等时，不交换位置.
    设置标记位，如果有效，直接退出
 效率:
 最好：o(n)，比如 待排序数组 1,2,3,4,5，循环一次change=false直接退出
 最坏 o(n^2),比如 待排序数组 5，4，3，2，1
 平均 o(n^2)
 
 交换的次数 = 逆序度 = 满有序度 - 有序度
 
 
 
 冒泡、插入、选择排序都有一个共同点，将待排序数列分为已排序和未排序两部分。在未排序的部分中查找一个最值，放到已排序数列的恰当位置。
 
 具体到代码层面，外层循环的变量用于分割已排序和未排序数，内层循环的变量用于在未排序数中查找。从思路上看，这三种算法其实是一样的，所以时间复杂度也相同。
 */
void bubbleSort(int nums[] ,int n ){
    if (n <= 1) {
        return;
    }

    for (int i=0;i<n;i++){
        bool change = false;
        for (int j=0; j<n-i-1; j++) {
            if (nums[j] > nums[j+1]) {
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
                change = true;
            }
        }
        if (!change) break;
    }
}


#endif /* bubbleSort_hpp */
