//
//  majorityElement.h
//  array
//
//  Created by junlongj on 2019/8/9.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef majorityElement_hpp
#define majorityElement_hpp

#include <stdio.h>
#include <vector>
/*
 给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
 
 你可以假设数组是非空的，并且给定的数组总是存在众数。
 
 示例 1:
 
 输入: [3,2,3]
 输出: 3
 示例 2:
 
 输入: [2,2,1,1,1,2,2]
 输出: 2
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/majority-element
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路:利用压栈和出栈的方式，只要和栈顶元素一样就进栈，不一样的话就出栈，栈为空时重新加入新元素来比较，这样栈里面最后的元素肯定是个数最多的那个.
    */
    int majorityElement(std::vector<int>& nums) {
        if (nums.empty()) return -1;
        int lastelement = nums[0];
        int count = 1;
        for (int i=1;i<nums.size();i++){
            if (count == 0){
                lastelement = nums[i];
                count = 1;
                continue;
            }
            if (nums[i] == lastelement){
                count++;
            }else{
                count--;
            }
            if (count > nums.size()/2) return lastelement;
        }
        return count > 0 ? lastelement : -1;
    }
}
#endif /* majorityElement_hpp */
