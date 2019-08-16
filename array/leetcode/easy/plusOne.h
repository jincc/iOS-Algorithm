//
//  plusOne.h
//  array
//
//  Created by junlongj on 2019/7/28.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef plusOne_hpp
#define plusOne_hpp

#include <stdio.h>
#include <vector>

/*
 66.给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。
 
 最高位数字存放在数组的首位， 数组中每个元素只存储一个数字。
 
 你可以假设除了整数 0 之外，这个整数不会以零开头。
 
 示例 1:
 
 输入: [1,2,3]
 输出: [1,2,4]
 解释: 输入数组表示数字 123。
 示例 2:
 
 输入: [4,3,2,1]
 输出: [4,3,2,2]
 解释: 输入数组表示数字 4321。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/plus-one
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 
 */

std::vector<int> plusOne(std::vector<int>& digits) {
    std::vector<int> r;
    if (digits.empty()){
        return r;
    }
    int i=digits.size()-1;
    int carry = 1;
    while (i>=0) {
        int t = digits[i] + carry;
        carry = t/10;
        t = t % 10;
        r.insert(r.begin(), t);
        i--;
    }
    if (carry > 0) {
        r.insert(r.begin(), carry);
    }
    return r;
}
#endif /* plusOne_hpp */
