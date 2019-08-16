//
//  kthSmallest.h
//  sort
//
//  Created by junlongj on 2019/7/19.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef kthSmallest_h
#define kthSmallest_h

/*
如何在o(n)内查找一个无序数组中的第K大元素.利用快排的思想，将数组一分为3，然后再次分割，最终定位到kth.
 
 */

int _partition(int nums[], int start, int end){
    int i=start;
    int j=start;
    for (; j<end; j++) {
        if (nums[j] < nums[end]) {
            std::swap(nums[j], nums[i++]);
        }
    }
    std::swap(nums[i], nums[end]);
    return i;
}


int kthSmallest(int nums[], int n,int start, int end, int kth){
    //数组分为了三部分,nums[start....pivot-1], nums[pivot], nums[pivot+1,end]
    //2...5 k=1
    int pivot = _partition(nums, start, end);
    if (pivot == kth-1) {
        //find
        return nums[pivot];
    }else if (pivot < kth-1){
        //说明在右边
        return kthSmallest(nums, n, pivot+1, end, kth-pivot-1);
    }else{
        //说明在左边
        return kthSmallest(nums, n, start, pivot-1, kth);
    }
}



#endif /* kthSmallest_h */
