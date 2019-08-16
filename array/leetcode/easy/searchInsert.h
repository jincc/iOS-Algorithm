//
//  searchInsert.h
//  array
//
//  Created by junlongj on 2019/8/7.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef searchInsert_hpp
#define searchInsert_hpp

#include <stdio.h>
#include <vector>
/*
 35. 搜索插入位置
 
 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 
 你可以假设数组中无重复元素。
 
 示例 1:
 
 输入: [1,3,5,6], 5
 输出: 2
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/search-insert-position
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    int searchInsert(std::vector<int>& nums, int target) {
        if (nums.empty())
            return 0;
        int l=0;
        int r=nums.size()-1;
        while(l<=r){
            int mid = l+(r-l)/2;
            if (nums[mid] == target){
                return mid;
            }else if (nums[mid] < target){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        return l;
    }
}
#endif /* searchInsert_hpp */
