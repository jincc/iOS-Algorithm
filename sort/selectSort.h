//
//  selectSort.h
//  sort
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef selectSort_hpp
#define selectSort_hpp

#include <algorithm>
/*
 将整个序列分为排序区域和未排序区域，将未排序区域中最小的元素放在排序区域的末尾.
  最好:o(n^2)
  最坏:o(n^2)
  平均:o(n^2)
  因为使用要找未排序里面最小的，所以里层for避免不了
 
  非稳定排序
 */

void selectSort(int nums[], int n){
    for (int i=0; i<n; i++) {
        int min = i;
        for (int j=i+1; j<n; j++) {
            if (nums[j] < nums[min]) {
                min = j;
            }
        }
        if (min != i) {
            std::swap(nums[min], nums[i]);
        }
    }
}


#endif /* selectSort_hpp */
