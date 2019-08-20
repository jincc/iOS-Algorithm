//
//  string_to_integer_atoi.h
//  string
//
//  Created by junlongj on 2019/8/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef string_to_integer_atoi_hpp
#define string_to_integer_atoi_hpp

#include <stdio.h>
#include <string>
/*
 8. 字符串转换整数 (atoi)
 请你来实现一个 atoi 函数，使其能将字符串转换成整数。
 
 首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。
 
 当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
 
 该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。
 
 注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
 
 在任何情况下，若函数不能进行有效的转换时，请返回 0。
 
 说明：
 
 假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 − 1]。如果数值超过这个范围，qing返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/string-to-integer-atoi
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    int myAtoi(std::string str) {
        if (str.empty()) return 0;
        //忽略起始位置空格
        //有正负号
        //连续数字
        int i=0;
        for (;i<str.length() && str[i] == ' ';i++){
        }
        if (i == str.length())
            return 0;//说明全是空格
        bool neg = false;
        if (str[i] == '-'){
            i++;
            neg = true;
        }else if (str[i] == '+'){
            i++;
            neg = false;
        }
        
        int   result=0;
        for (;i<str.length();i++){
            int num = str[i] - '0';
            if (num >=0 && num <= 9){
                //首先判断是否会越界
                if (neg){
                    if (result < (INT_MIN + num) / 10){
                        return INT_MIN;
                    }
                    result = result * 10 - num;
                }else{
                    if (result > (INT_MAX-num)/10){
                        return INT_MAX;
                    }
                    result = result * 10 + num;
                }
            }else{
                break;
            }
        }
        return result;
    }
    
    void test_myAtoi (){
        std::string s="-2147483648";
        std::cout << myAtoi(s) << std::endl;
    }
}
#endif /* string_to_integer_atoi_hpp */
