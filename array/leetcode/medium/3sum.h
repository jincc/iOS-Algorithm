//
//  3sum.h
//  array
//
//  Created by junlongj on 2019/8/19.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef _sum_hpp
#define _sum_hpp

#include <stdio.h>
#include <vector>
/*
 15.三数之和
 给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
 
 注意：答案中不可以包含重复的三元组。
 
 例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
 
 满足要求的三元组集合为：
 [
 [-1, 0, 1],
 [-1, -1, 2]
 ]
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/3sum
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路: 将三数问题降维到二数问题
     先将数组排好序, 比如:
              -1,0,1,2,-1,-4，
      排完序就是-4,-1,-1,0,1,2
     
      双层循环，外层固定第一个数，然后通过数组的有序性，将后两数之和和固定的数进行比较来挪动位置.
     
      这题提交了几次，关键在于异常情况没考虑到位，比如下面代码1.处。
     */
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        int size = nums.size();
        if (size < 3)
            return {};
        std::vector<std::vector<int>> results;
        std::sort(nums.begin(),nums.end());
        for (int i=0;i<size-2;i++){
            int a = nums[i];//先固定第一个数
            if (i >= 1 && a == nums[i-1])
                continue;
            for (int j=i+1,k =size-1;j < k ;){
                int b = nums[j];
                int c = nums[k];
                if (b + c == -a){
                    results.push_back({a,b,c});
                    //注意后面需要过滤掉重复的数字  1.
                    while (j < k && nums[j] == b)
                        j++;
                    while (j < k && nums[k] == c)
                        k--;
                }else if (b + c > -a){
                    k--;
                }else{
                    j++;
                }
            }
        }
        return results;
    }
}
#endif /* _sum_hpp */
