//
//  reversedOrderPairs.h
//  divideConquer
//
//  Created by junlongj on 2019/7/25.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef reversedOrderPairs_hpp
#define reversedOrderPairs_hpp

#include <stdio.h>

/*
 求一组数据里面的逆序对。
 思路：分治算法. 我们将数组分为前半部分A和后半部分B，分别计算A和B的逆序对个数，然后计算A和B之间的逆序对个数，三个数相加就是结果。
     因为左右都是有序数组，所以问题就转化为求A和B之间的l逆序对.
 */
int paircount = 0;
void merge(int nums[], int n, int left, int mid, int right){
    int i=left;
    int j=mid+1;
    int temp[right-left+1];
    int k=0;
    while (i<=mid && j<=right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        }else{
            temp[k++] = nums[j++];
            //如果nums[i] > nums[j],那么nums[i.....mid]都比nums[j]大.
            paircount += (mid-i+1);
        }
    }
    while (i <= mid) {
        temp[k++] = nums[i++];
    }
    while (j <= right) {
        temp[k++] = nums[j++];
    }
    for(i=left,k=0;i<=right;i++,k++){
        nums[i] = temp[k];
    }
    
}

void reversedOrderPairs(int nums[], int n, int left, int right){
    if (left >= right)
        return;
    int mid = left + (right-left)/2;
    reversedOrderPairs(nums, n, left, mid);
    reversedOrderPairs(nums, n, mid+1, right);
    merge(nums, n, left, mid, right);
}

int reversedOrderPairs(int nums[], int n){
    reversedOrderPairs(nums, 6, 0, 5);
    return paircount;
}




int invertPairCore(int *nums, int start, int end);
int reversePairs(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 0)
        return 0;
    return invertPairCore(nums, 0 , numsSize - 1);
}
int invertPairCore(int *nums, int start, int end){
    if (start >= end){
        return 0;
    }
    int middle = start + (end - start) / 2;
    int leftcnt = invertPairCore(nums, start, middle);
    int rightcnt = invertPairCore(nums, middle+1, end);
    int cnt = 0;
    int temp[end - start +1];
    int p1, p2, p3;
    p1 = middle;
    p2 = end;
    p3 = end - start;
    while(p1 >= start && p2 >= middle+1){
        if (nums[p1] > nums[p2]){
            cnt = p2 - middle;
            temp[p3--] = nums[p1--];
        }else{
            temp[p3--] = nums[p2--];
        }
    }
    while(p1 >= start){
        temp[p3--] = nums[p1--];
    }
    while(p2 >= middle+1){
        temp[p3--] = nums[p2--];
    }
    for(p1=start, p2 = 0;p1 <= end; p1++, p2++){
        nums[p1] = temp[p2];
    }
    return leftcnt + rightcnt + cnt;
}


#endif /* reversedOrderPairs_hpp */
