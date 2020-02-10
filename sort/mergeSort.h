//
//  mergeSort.h
//  sort
//
//  Created by junlongj on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef mergeSort_h
#define mergeSort_h


/*
 分治思想：如果要排序一个数组，我们先将数组分为两半，在分别对两半排序，再将两半合起来就是有序数组了。
 
 mergeSort(m,n)  = merge( mergeSort(m,q) , mergeSort(q+1,n))
 
 merge函数的实现里面，我们可以看出首先会N次循环构建一个temp临时排好序的数组，然后依次拷贝。所以归并排序的执行效率和要排序数组的有序程度是无关的，所以时间复杂度是非常稳定的，不管是最好，最坏，平均都是o(n*log(n))
 
 归并排序虽然如此稳定，但是也有缺点：
 
 那就是每次合并都会创建一个o(n)的临时数组，在任意时刻，CPU只会执行一个函数，所以空间复杂度为o(n).
 
 
 
 */

void merge(int nums[], int start, int mid ,int end);
void mergeSort(int nums[], int start, int end);
void mergeBySentry(int nums[], int start, int mid ,int end);

void mergeSort(int nums[], int n){
    mergeSort(nums, 0, n-1);
}

void mergeSort(int nums[], int start, int end){
    if (start >= end) {
        return;
    }
    int mid = (end - start) / 2 + start;
    mergeSort(nums, start, mid);
    mergeSort(nums, mid+1, end);
    merge(nums, start, mid, end);
}

void merge(int nums[], int start, int mid ,int end){
    /*
     数组1： nums[start....mid]
     数组2:  nums[mid+1....end]
     */
    int temp[end-start+1];
    int i,j,k;
    i=start;
    j=mid+1;
    k=0;
    while (i <= mid && j <= end) {
        if (nums[i] < nums[j]) {
            temp[k++] = nums[i++];
        }else{
//            std::cout << nums[i] << ", " << nums[j] << std::endl;
            temp[k++] = nums[j++];
        }
    }
    while (i <= mid) {
         temp[k++] = nums[i++];
    }
    while (j <= end) {
         temp[k++] = nums[j++];
    }
    for(i=start,k=0;i<=end;i++,k++){
        nums[i] = temp[k];
    }
    
}


void mergeBySentry(int nums[], int start, int mid ,int end){
    //利用哨兵对象，分别在左右数组末尾插入哨兵
    
    int leftarr[mid-start+2];
    int rightarr[end-mid+1];
    
    
    for (int i=start, k=0; i<=mid; i++, k++) {
        leftarr[k] = nums[i];
    }
    leftarr[mid-start+1] = INT_MAX;
    
    for (int i=mid+1,k=0; i<=end; i++,k++) {
        rightarr[k]=nums[i];
    }
    rightarr[end-mid] = INT_MAX;
    
    
    int index = start;
    int i = 0;
    int j = 0;
    while (index <= end) {
        if (leftarr[i] < rightarr[j]) {
            nums[index++] = leftarr[i++];
        }else{
            nums[index++] = rightarr[j++];
        }
    }
    
}



#endif /* mergeSort_h */
