//
//  twoSum_ii.h
//  array
//
//  Created by junlongj on 2019/8/9.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef twoSum_ii_hpp
#define twoSum_ii_hpp

#include <stdio.h>
#include <vector>
/*
 给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。
 
 函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。
 
 说明:
 
 返回的下标值（index1 和 index2）不是从零开始的。
 你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。
 示例:
 
 输入: numbers = [2, 7, 11, 15], target = 9
 输出: [1,2]
 解释: 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    std::vector<int> twoSum_ii(std::vector<int>& numbers, int target) {
        if (numbers.empty()) return {};
        std::vector<int> result;
        for(int i=0,j=numbers.size()-1;i<j;){
            int value=numbers[i]+numbers[j];
            if (value == target){
                result.push_back(i+1);
                result.push_back(j+1);
                break;
            }else if (value < target){
                i++;
            }else{
                j--;
            }
        }
        return result;
    }
}
#endif /* twoSum_ii_hpp */
