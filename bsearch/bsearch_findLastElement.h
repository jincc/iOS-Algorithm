//
//  bsearch_findLastElement.h
//  bsearch
//
//  Created by junl on 2019/9/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bsearch_findLastElement_hpp
#define bsearch_findLastElement_hpp

#include <stdio.h>
/*
 有序数组中，存在着相同的元素，找到最后一个值等于指定元素的位置
 */

int  bsearch_findLastElement(int nums[], int n,int target){
    if (n <= 0) {
        return -1;
    }
    int left=0;
    int right=n-1;
    while (left<=right) {
        int mid = left+((right-left)>>1);
        if (nums[mid] < target) {
            left = mid+1;
        }else if (nums[mid] > target){
            right=mid-1;
        }else{
            //找到了target，我们判断它是否是最后一个
            if (mid == n-1 || nums[mid+1] !=target) {
                return mid;
            }
            left=mid+1;
        }
    }
    return -1;
}

#endif /* bsearch_findLastElement_hpp */
