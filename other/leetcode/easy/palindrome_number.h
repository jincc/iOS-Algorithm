//
//  palindrome_number.h
//  other
//
//  Created by junlongj on 2019/8/11.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef palindrome_number_hpp
#define palindrome_number_hpp

#include <stdio.h>
#include "reverse_integer.h"
/*
 9. 回文数
 判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 
 示例 1:
 
 输入: 121
 输出: true
 示例 2:
 
 输入: -121
 输出: false
 解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
 示例 3:
 
 输入: 10
 输出: false
 解释: 从右向左读, 为 01 。因此它不是一个回文数。
 进阶:
 
 你能不将整数转为字符串来解决这个问题吗？
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/palindrome-number
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路1:
     整体反转，然后判断是否相等
     */
    bool isPalindrome2(int x) {
        if (x<0) return false;
        return x == reverse(x);
    }
    /*
     思路2:
     我们只反转一半的数字，然后判断前后是否相等。
     那么怎么判断数字旋转了一半呢？
     */
    bool isPalindrome(int x) {
        if (x<0 || x % 10 == 0 && x!=0) return false;
        int revalue = 0;
        while(x > revalue){
            revalue = revalue*10+x%10;
            x/=10;
        }
        //判断前后是否相等有两种情况：
        //1.比如 : 1221 ,x=12,revalue=12
        //2.比如 : 12321,x=12,revalue=123
        return x == revalue || x == revalue/10;
    }
}
#endif /* palindrome_number_hpp */
