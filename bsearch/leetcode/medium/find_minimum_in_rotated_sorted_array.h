//
//  find_minimum_in_rotated_sorted_array.h
//  bsearch
//
//  Created by junl on 2019/9/7.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef find_minimum_in_rotated_sorted_array_hpp
#define find_minimum_in_rotated_sorted_array_hpp

#include <stdio.h>
/*
 153.寻找旋转排序数组中的最小值
 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
 
 ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
 
 请找出其中最小的元素。
 
 你可以假设数组中不存在重复元素。
 
 示例 1:
 
 输入: [3,4,5,1,2]
 输出: 1
 示例 2:
 
 输入: [4,5,6,7,0,1,2]
 输出: 0
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    using namespace std;
    /*
     思路：
     寻找波谷，即寻找数组相邻两个元素，前一个元素比后一个元素大的位置.
     
     1.我们首先判断[left....right]这部分是否已经是有序数组了，如果是有序数组，那么直接返回左边的数。
     2.如果不是有序的，那么久存在旋转的部分，最小数字肯定出现在旋转部分。
     
     note：注意寻找波谷的条件nums[mid-1] > nums[mid] || nums[mid] > nums[mid+1]
     */
    int findMin(vector<int>& nums) {
        if (nums.empty()) return -1;
        if (nums.size()==1) return nums[0];
        
        int left=0;
        int right=nums.size()-1;
        while(left<=right){
            int mid = left+((right-left)>>1);
            //如果已经是有序部分，返回左节点
            if (nums[left] <= nums[mid] && nums[mid] <= nums[right]){
                return nums[left];
            }
            //寻找波谷
            if (mid >0 &&  nums[mid-1] > nums[mid]){
                return nums[mid];
            }
            if (mid +1 <nums.size() && nums[mid] > nums[mid+1]) {
                return nums[mid+1];
            }
            //查找哪半边是有序的
            if (nums[mid] > nums[left]){
                //左边是有序的
                left = mid + 1;
            }else{
                //右边是有序的
                right = mid - 1;
            }
        }
        return -1;
    }
}
#endif /* find_minimum_in_rotated_sorted_array_hpp */
