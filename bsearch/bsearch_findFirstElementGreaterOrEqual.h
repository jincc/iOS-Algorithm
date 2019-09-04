//
//  bsearch_findFirstElementGreaterOrEqual.h
//  bsearch
//
//  Created by junl on 2019/9/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bsearch_findFirstElementGreaterOrEqual_hpp
#define bsearch_findFirstElementGreaterOrEqual_hpp

#include <stdio.h>
/*
 有序数组中，存在着相同的元素, 查找第一个大于等于指定元素的值.
 */
int  bsearch_findFirstElementGreaterOrEqual(int nums[], int n,int target){
    //首先找到大于等于指定元素的值，然后判断它是否是第一个.
    if (n <= 0) return -1;
    int left = 0;
    int right = n-1;
    while(left<=right){
        int mid = left+((right-left)>>1);
        if (nums[mid] >= target){
            //已经是大于等于target的值了,找到第一个
            if (mid == 0 || nums[mid-1]  < target){
                return mid;
            }
            right = mid -1;
        }else{
            left = mid+1;
        }
    }
    return -1;
    
}



#endif /* bsearch_findFirstElementGreaterOrEqual_hpp */
