//
//  countingSort.h
//  sort
//
//  Created by junl on 2019/7/19.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef countingSort_hpp
#define countingSort_hpp

#include <stdio.h>
/*
 计数排序是一种更细粒度的桶排序.
 桶排序的核心思想是将要排序的数据分为几个桶，每个桶内部在单独进行排序，桶排完序之后，在把每个桶的数据按照顺序依次取出，组成的序列就是有序的。
 而计数排序，假设这些数的最大值为max，那么它就分成max+1个桶(0,1,2....max).这样每个桶内部就不用在排序了。

 */
//数组里面存储的是学生考试的分数
void countingSort(int nums[], int n){
    
    //1.先要分为max个桶,里面保存每个分数的人数
    //2.建立新数组,每个位置保存小于等于这个分数的人数
    //3.从后向前开始遍历，然后把数据放在正确的位置
    
    if (n <= 1) {
        return;
    }
    //先求出数值最大的分数
    int max = nums[0];
    for(int i=0;i<n;i++){
        if (nums[i] > max)
            max = nums[i];
    }
    //建立max+1个桶，idex为分数，value为该分数的个数
    int bucket[max+1];
    for(int i=0;i<=max;i++){
        bucket[i]=0;
    }
    for(int i=0;i<n;i++){
        bucket[nums[i]] += 1;
    }
    //建立max+1个桶，保存的是小于等于该分数的个数
    int scores2[max+1];
    scores2[0] = bucket[0];
    for (int i=1;i<=max; i++) {
        scores2[i] = scores2[i-1]+ bucket[i];
    }
    
    int temp[n];
    for (int i=n-1; i>=0; i--) {
        //分数小于等于i分的有a人
        int score = nums[i];
        int a = scores2[score];
        temp[a-1] = score;
        scores2[score]-=1;
    }
    
    for (int i=0; i<n; i++) {
        nums[i] = temp[i];
    }
    
}

#endif /* countingSort_hpp */
