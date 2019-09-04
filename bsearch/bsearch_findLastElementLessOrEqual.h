//
//  bsearch_findLastElementLessOrEqual.h
//  bsearch
//
//  Created by junl on 2019/9/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bsearch_findLastElementLessOrEqual_hpp
#define bsearch_findLastElementLessOrEqual_hpp

#include <stdio.h>
/*
 查找最后一个小于等于给定值的元素
 */
int  bsearch_findLastElementLessOrEqual(int nums[], int n,int target){
    if (n <= 0) return -1;
    int left = 0;
    int right = n-1;
    while(left<=right){
        int mid = left+((right-left)>>1);
        if (nums[mid] <= target){
            //已经是小于等于给定值的元素,找到最后一个
            if (mid == n-1 || nums[mid+1]  > target){
                return mid;
            }
            left = mid + 1;
        }else{
            right = mid -1;
        }
    }
    return -1;
}

#endif /* bsearch_findLastElementLessOrEqual_hpp */
