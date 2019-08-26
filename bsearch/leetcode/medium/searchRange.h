//
//  searchRange.h
//  bsearch
//
//  Created by junlongj on 2019/8/26.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef searchRange_hpp
#define searchRange_hpp

#include <stdio.h>
#include <vector>
/*
 34.在排序数组中查找元素的第一个和最后一个位置
 
 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
 
 你的算法时间复杂度必须是 O(log n) 级别。
 
 如果数组中不存在目标值，返回 [-1, -1]。
 
 示例 1:
 
 输入: nums = [5,7,7,8,8,10], target = 8
 输出: [3,4]
 示例 2:
 
 输入: nums = [5,7,7,8,8,10], target = 6
 输出: [-1,-1]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */

namespace leetcod {
    using namespace std;
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return {-1,-1};
        int size = nums.size();
        int left=0;
        int right=size-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if (nums[mid] == target){
                int s,e;
                s = e = mid;
                while(s >= 1 &&nums[s-1] == nums[s]){
                    s--;
                }
                while(e+1 < size  &&nums[e] == nums[e+1]){
                    e++;
                }
                return {s,e};
            }else if (nums[mid] < target){
                left=mid+1;
            }else{
                right=mid-1;
            }
        }
        return {-1,-1};
    }
}
#endif /* searchRange_hpp */
