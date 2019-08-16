//
//  rotate.h
//  array
//
//  Created by junlongj on 2019/7/28.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef rotate_hpp
#define rotate_hpp

#include <stdio.h>
#include <vector>
/*
 189.给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。
 
 示例 1:
 
 输入: [1,2,3,4,5,6,7] 和 k = 3
 输出: [5,6,7,1,2,3,4]
 解释:
 向右旋转 1 步: [7,1,2,3,4,5,6]
 向右旋转 2 步: [6,7,1,2,3,4,5]
 向右旋转 3 步: [5,6,7,1,2,3,4]
 示例 2:
 
 输入: [-1,-100,3,99] 和 k = 2
 输出: [3,99,-1,-100]
 解释:
 向右旋转 1 步: [99,-1,-100,3]
 向右旋转 2 步: [3,99,-1,-100]
 
 尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
 要求使用空间复杂度为 O(1) 的 原地 算法。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/rotate-array
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

//方法一：依次向右旋转第1步，第2步.....
void rotate(std::vector<int>& nums, int k) {
    if (nums.size() <= 1)
        return;
    int i=0;
    while (i<k) {
        int tail = nums.back();
        size_t j= nums.size()-1;
        while (j>=1) {
            nums[j] = nums[j-1];
            j--;
        }
        nums[0] = tail;
        i++;
    }
}

void swaparray(std::vector<int>& nums,int start, int end){
    int i=start;
    int j=end;
    while (i < j) {
        std::swap(nums[i++], nums[j--]);
    }
}

void rotate2(std::vector<int>& nums, int k) {
    if (nums.size() <= 1)
        return;
    k = k % nums.size();
    swaparray(nums, 0, nums.size()-k-1);
    swaparray(nums, nums.size()-k, nums.size()-1);
    swaparray(nums, 0, nums.size()-1);
    
}


/*
 直接将nums[i]放到最终的位置,即比如nums[0]->nums[k].这样原本nums[i+k]的值就被替换了，我们用temp来保存之前的值，然后继续这样迭代。直到下标到达最初的位置，这里一共迭代了n/k个数字.如下:
 如果我们从下标0开始的话,nums[k],nums[2k],nums[3k].....nums[0]
 
 这样经过k轮，每轮替换掉n/k个数字，最终就替换完所有数字了。
 * 0,1,2,3,4,5
 * 1,2,3,4,5,6  k = 2
 第一轮: a[2] = a[0], a[4] = a[2], a[0] = a[4];  ====> 5,2,1,4,3,6
 第二轮: a[3] = a[1], a[5] = a[3], a[1] = a[5]   ====> 5,6,1,2,3,4,
 *
 *
 */
void rotate3(std::vector<int>& nums, int k) {
    if (nums.size()<=1) return;
    int size=nums.size();
    k=k%size;
    int count=0;
    for (int i=0; count<size; i++) {
        int oldvalue = nums[i];
        int ctindex=i;
        do {
            int next = (ctindex + k) % size;
            int newvlaue = nums[next];
            nums[next] = oldvalue;
            ctindex = next;
            oldvalue = newvlaue;
            count++;
        } while (ctindex != i);
    }
}

#endif /* rotate_hpp */
