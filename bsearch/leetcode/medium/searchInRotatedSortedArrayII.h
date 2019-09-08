//
//  searchInRotatedSortedArrayII.h
//  bsearch
//
//  Created by junl on 2019/9/6.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef searchInRotatedSortedArrayII_hpp
#define searchInRotatedSortedArrayII_hpp

#include <stdio.h>
#include <vector>
/*
81. 搜索旋转排序数组 II
 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
 
 ( 例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2] )。
 
 编写一个函数来判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。
 
 示例 1:
 
 输入: nums = [2,5,6,0,0,1,2], target = 0
 输出: true
 示例 2:
 
 输入: nums = [2,5,6,0,0,1,2], target = 3
 输出: false
 进阶:
 
 这是 搜索旋转排序数组 的延伸题目，本题中的 nums  可能包含重复元素。
 这会影响到程序的时间复杂度吗？会有怎样的影响，为什么？
 在真实的面试中遇到过这道题？
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    using namespace std;
    /*
     这个题和旋转数组那道题的区别之处就在于，这里数组包含了重复的元素.
     如果旋转数组里面不包含重复元素，那么我们可以通过nums[mid], nums[left] , nums[right]来判断那半边是有序的，那半边是旋转的。
     但是现在包含重复元素，所以nums[mid], nums[left] , nums[right]这三个值可能会相等，比如当nums[mid] == nums[left]时，我们让left++过滤掉重复的，当过滤掉重复的值后，那么旋转数组一定有一半边有序，我们可以用之前的方法来查找.
     */
    bool searchii(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        if (nums.size() == 1) return nums[0] == target;
        int left=0;
        int right=nums.size()-1;
        while(left<=right){
            int mid = left+((right-left)>>1);
            if (nums[mid] == target){
                return true;
            }
//            if (nums[left] == nums[mid] && nums[right] == nums[mid]){
            if (nums[left] == nums[mid]){//过滤掉重复数字
                left++;
//                right--;
            }else if (nums[left] <= nums[mid]){
                //左边有序的
                if (target >= nums[left] && target < nums[mid]){
                    right = mid -1;
                }else{
                    left = mid + 1;
                }
            }else{
                //右边有序的
                if (target > nums[mid] && target <= nums[right]){
                    left = mid+1;
                }else{
                    right = mid-1;
                }
            }
            
        }
        return false;
    }
}
#endif /* searchInRotatedSortedArrayII_hpp */
