//
//  reverse_integer.h
//  other
//
//  Created by junlongj on 2019/8/11.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef reverse_integer_hpp
#define reverse_integer_hpp

#include <stdio.h>
/*
 7. 整数反转
 
 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
 
 示例 1:
 
 输入: 123
 输出: 321
  示例 2:
 
 输入: -123
 输出: -321
 示例 3:
 
 输入: 120
 输出: 21
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/reverse-integer
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    //这个题提交失败了多次，关键在于如何确保数据不会溢出。
    int reverse(int x) {
        int result=0;
        while(x){
            int v=x%10;
            //int最大值是2147483647，最小值是-2147483648
            if (result > INT_MAX/10){
                return 0;
            }
            if (result < INT_MIN/10){
                return 0;
            }
            result=result*10+v;
            x/=10;
        }
        return result;
    }
}
#endif /* reverse_integer_hpp */
