//
//  quickSort.h
//  sort
//
//  Created by junlongj on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef quickSort_h
#define quickSort_h

/*
 也是利用分治思想：
 
 将大问题化解为小问题,而这个小问题我们的目标就是将nums[i...j]，选择一个数作为分区点pivot,比如它的下标为k,
 那么nums[i...k-1]的值都比pivot小，nums[k+1...j]都比pivot大.因为每一次递归里面都是左小右大，所以它们合起来的时候整个就有序了。
 
 
 怎么解决数组里面，小的都放在左边，大的都放在右边？
 
 这里我们选择最右边的点作为pivot,然后把数组分为两部分，i之前的都是比pivot小的，之后的都是比它大的。
 我们从左向右开始寻找，如果发现nums[j]比较小，那么交换nums[i]，nums[j],然后向右移动一位。
 
 平均o(n*log(n))
 最坏o(n^2)
 
 */
#ifdef __cplusplus
extern "C" {
#endif
void swap(int nums[], int idx1, int idx2){
    int tmp = nums[idx1];
    nums[idx1] = nums[idx2];
    nums[idx2] = tmp;
}
int partition(int nums[], int len){
    int target = nums[len-1];
    int i, j;
    
    i = j = 0;
    for(; j < len ; j++){
        if (nums[j] < target){
            swap(nums, i++, j);
        }
    }
    swap(nums, i, len-1);
    return i;
}
void fqsort(int nums[], int size){
    if (size <= 1) return;
    int idx = partition(nums, size);
    if (idx > 0)
        fqsort(nums, idx);
    if (size - idx - 1 > 0)
        fqsort(nums+idx+1, size - idx - 1);
}
#ifdef __cplusplus
}
#endif

#endif /* quickSort_h */
