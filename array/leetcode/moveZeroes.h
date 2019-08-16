//
//  moveZeroes.h
//  array
//
//  Created by junl on 2019/7/29.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef moveZeroes_hpp
#define moveZeroes_hpp

#include <stdio.h>
#include <vector>
/*
 283.给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 
 示例:
 
 输入: [0,1,0,3,12]
 输出: [1,3,12,0,0]
 说明:
 
 必须在原数组上操作，不能拷贝额外的数组。
 尽量减少操作次数。
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/move-zeroes
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

//方法1 ： i表示非零数组的末尾
void moveZeroes(std::vector<int>& nums) {
    size_t n = nums.size();
    if (n <= 1)
        return;
    int i=0;
    for(int j=1;j<n;j++){
        if (nums[i] ==0) {
            if (nums[j] != 0) {
                std::swap(nums[i], nums[j]);
                i++;
            }
        }else{
            i++;
        }
    }
    
}

//方法二：i表示非0数组的末尾.
void moveZeroes2(std::vector<int>& nums) {
    int i = 0;
    for (int j=0; j < nums.size(); j++) {
        //只要当前元素不为0，就保存到数组末尾.
        if (nums[j] != 0) {
            nums[i++] = nums[j]; //这个方法会有大量浪费浪费操作.
        }
    }
    //后面部分填0
    while (i<nums.size()) {
        nums[i++] = 0;
    }
}

void moveZeroes3(std::vector<int>& nums) {
    int i=0;
    //找到第一个为0的位置
    for (; i<nums.size() && nums[i] != 0; i++) {
    }
    //只要当前元素不为0，就保存到数组末尾.
    for(int j=i;j<nums.size();j++){
        if (nums[j] != 0) {
            nums[i++] = nums[j]; 
        }
    }
    //后面部分填0
    while (i<nums.size()) {
        nums[i++] = 0;
    }
    
}

#endif /* moveZeroes_hpp */
