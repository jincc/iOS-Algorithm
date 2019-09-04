//
//  bsearch_findFirstElement.h
//  bsearch
//
//  Created by junlongj on 2019/9/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bsearch_findFirstElement_hpp
#define bsearch_findFirstElement_hpp

#include <stdio.h>

/*
 有序数组中，存在着相同的元素，找到指定元素的第一个值.
 */

int bsearch_findFirstElement(int nums[], int n,int target){
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
            //找到了target，我们判断它是否是第一个
            if (mid == 0 || nums[mid-1] != target) {
                return mid;
            }
            right = mid-1;
        }
    }
    return -1;
}
#endif /* bsearch_findFirstElement_hpp */
