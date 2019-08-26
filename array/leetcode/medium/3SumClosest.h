//
//  3SumClosest.h
//  array
//
//  Created by junlongj on 2019/8/20.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef _SumClosest_hpp
#define _SumClosest_hpp

#include <stdio.h>
#include <vector>
/*
 16. 最接近的三数之和
 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
 
 例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.
 
 与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/3sum-closest
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路：和上一题3sum一模一样.先排好序构成有序数组，
     然后双层循环，第一层固定第一个数，第二层里面两指针，一个指向数组里面最小的值，一个指向数组里面最大的值，通过三数的和与target的关系来移动两指针的位置。
     
     总时间复杂度：O(nlogn) + O(n^2) =  O(n^2)
     */
    int threeSumClosest(std::vector<int>& nums, int target) {
        if (nums.size()< 3) return 0;
        std::sort(nums.begin(),nums.end());//从小到大排好序
        int size = nums.size();
        int result = 0;
        //设置result初始值为数组前三数和
        for(int i=0;i<3;i++){
            result+=nums[i];
        }
        for (int i=0;i<size-2;i++){
            int a = nums[i];
            int j=i+1;
            int k=size-1;
            while(j<k){
                int b = nums[j];
                int c = nums[k];
                int sum = a+b+c;
                if (abs(sum-target) < abs(result - target)){
                    result = sum;
                }
                if (sum == target){
                    return target;
                }else if (sum < target){
                    //需要过滤掉重复的
                    do{
                        j++;
                    }while(j<k && nums[j] == nums[j-1]);
                }else{
                    //需要过滤掉重复的
                    do{
                        k--;
                    }while(j<k && nums[k] == nums[k+1]);
                }
            }
        }
        return result;
    }
}
#endif /* _SumClosest_hpp */
