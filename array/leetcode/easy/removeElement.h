//
//  removeElement.h
//  array
//
//  Created by junlongj on 2019/8/7.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef removeElement_hpp
#define removeElement_hpp

#include <stdio.h>
#include <vector>
/*
 27.给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。
 
 不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
 
 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
 
 示例 1:
 
 给定 nums = [3,2,2,3], val = 3,
 
 函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。
 
 你不需要考虑数组中超出新长度后面的元素。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/remove-element
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 https://leetcode-cn.com/problems/remove-element/
 */

namespace leetcode {
    /*
     思路:双指针,始终指针有效数组的末尾，然后遍历j,如果nums[j] != val，那么将nums[j]放在有效数组的末尾，即:
     nums[i] = nums[j];
     i++;
     */
    int removeElement(std::vector<int>& nums, int val) {
        int i=0;
        for(int j=0;j<nums.size();j++){
            if (nums[j] != val){
                nums[i++] = nums[j];
            }
        }
        return i;
    }
    /*
     思路: 上面的解法，比如遇到【1，2，3，4，5】，5会有4次无意义的拷贝。通过下面的解法，可以使拷贝的次数减少为删除元素的个数那么多次。
     依次遍历，只要遇到nums[j] ==val，则证明它是需要删除的值，我们将末尾元素赋给它，然后再次遍历。
     */
    int removeElement2(std::vector<int>& nums, int val) {
        int n=nums.size();
        int j=0;
        while(j < n){
            if (nums[j] == val){//主要遇到了val这个值,就将末尾元素赋给nums[j],注意新的末尾元素可能是有效值
                nums[j] = nums[n-1];
                n--;
            }else{
                j++;
            }
        }
        return n;
    }
}
#endif /* removeElement_hpp */
