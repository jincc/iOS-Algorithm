//
//  bsearch.h
//  bsearch
//
//  Created by junl on 2019/7/19.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bsearch_hpp
#define bsearch_hpp

#include <stdio.h>

/*
 二分查找又叫折半查找，每次都通过跟区间的中位数作比较，将待查找的区间缩小为之前的一半，直到找到要查找的元素。二分查找是一种十分高效的查找方式，时间复杂度为o(log(n)).这种查找速度是很恐怖的，试想一下在区间0-2^32的范围内查找一个数，最多需要32次比较就能找到。
 
 二分查找的局限性:
 
 1. 只适用于数组，因为需要数组的随机访问能力
 2. 二分查找针对的是有序数据。如果是静态数据呢，我们可以一次排序，N次查找，来均摊排序所花费的时间。但是如果是动态数据的话，即中途还有可能会向数组插入/删除元素的话，那么就不适用于二分了，因为每次改变都需要重新排序。
 3. 数据量太小不适合用二分查找，比如10次以内的循环，其实直接顺序遍历时间也差不多。但是如果涉及到元素比较比较耗时(比如长字符串直接的比较)，那么比较次数越少越好。
 4. 数据量太大也不适用于二分查找。因为二分需要依靠数组，而数组是无法存储大数据的。
 
 
 下面的几个变种问题，关键点在于：***********如果在已经满足条件的情况下，进一步的去锁定当前是不是第一个或者最后一个元素.*********
 
 
 二分查找的变种问题写起来是比较费脑的，我们需要注意终止条件，区间上下界更新，返回值选择。二分查找更适合处理一些<font size=5 color=red>“近似查找”</font>问题上，比如练习里面的:
 
 1. 查找第一个等于定值的元素.
 2. 查找最后一个值等于给定值的元素.
 3. 查找第一个大于等于指定元素的值.
 4. 查找最后一个小于等于给定值的元素.
 
 而仅仅是查找某个具体的值，我们也可以使用散列表或二叉查找树来实现。
 */
int  bsearch_f1(int nums[], int n,int target){
    int left = 0;
    int right = n-1;
    while (left<=right) {
        int mid = left + (right - left)/2;
        if (nums[mid] == target) {
            return mid;
        }else if (nums[mid] < target){
            left = mid+1;
        }else{
            right = mid-1;
        }
    }
    return -1;
}


int  bsearch_f2(int nums[], int n,int left, int right, int target){
    if (left>right) {
        return -1;
    }
    
    int mid = left + (right - left)/2;
    if (nums[mid] == target) {
        return mid;
    }else if (nums[mid] < target){
        return bsearch_f2(nums, n, mid+1, right, target);
    }else{
        return bsearch_f2(nums, n, left, mid-1, target);
    }
}
#endif /* bsearch_hpp */
