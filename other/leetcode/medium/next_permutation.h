//
//  next_permutation.h
//  other
//
//  Created by junlongj on 2019/8/26.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef next_permutation_hpp
#define next_permutation_hpp

#include <stdio.h>
#include <vector>
/*
 31.下一个排列
 实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
 
 如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
 
 必须原地修改，只允许使用额外常数空间。
 
 以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
 1,2,3 → 1,3,2
 3,2,1 → 1,2,3
 1,1,5 → 1,5,1
 
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/next-permutation
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    void reverse(std::vector<int>& nums,int left ,int right){
        while (left < right){
            std::swap(nums[left++],nums[right--]);
        }
    }
    void nextPermutation(std::vector<int>& nums) {
        //什么情况下会存在比当前更大一点的序列？
        /*
         当nums[i-1] < nums[i]的话，肯定会存在一个比当前更大一点的序列.我们是从最右边遍历过来的，所以nums[i....n]这些数字是按照降序的方式排列的。我们从最右边开始寻找第一个比nums[i-1]大的数，交换它们的值。
         交换之后，最右边仍然是降序排列的。它不是比当前更大的最小的，需要将它翻转。
         */
        int size = nums.size();
        if (size <= 1) return ;
        int i=size-1;
        while (i >= 1 && nums[i-1] >= nums[i]){
            i--;
        }
        //nums[i-1] < nums[i]
        if (i == 0){
            //说明当前是最大的序列，需要翻转0...n
            reverse(nums,0, size-1);
        }else{
            int j = size-1;
            while (j >= i){
                if (nums[j] > nums[i-1]){
                    std::swap(nums[j],nums[i-1]);
                    break;
                }else{
                    j--;
                }
            }
            //需要翻转i...n的序列
            reverse(nums, i, size-1);
        }
    }
}
#endif /* next_permutation_hpp */
