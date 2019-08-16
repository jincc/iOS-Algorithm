//
//  StrToInt.h
//  string
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef StrToInt_hpp
#define StrToInt_hpp

#include <stdio.h>
#include <string>

/*
 剑指Offer（四十九）：把字符串转换成整数
 
 将一个字符串转换成一个整数(实现Integer.valueOf(string)的功能，但是string不符合数字要求时返回0)，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0。
 输入描述:
 输入一个字符串,包括数字字母符号,可以为空
 输出描述:
 如果是合法的数值表达则返回该数字，否则返回0
 https://www.nowcoder.com/practice/1277c681251b4372bdef344468e4f26e?tpId=13&tqId=11202&tPage=3&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 
 */

namespace codinginterviews {
    int StrToInt(std::string &str) {
        if (str.empty()) {
            return 0;
        }
        bool negative = false;
        std::string vaildStr;
        for (int i=0; i<str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                vaildStr += str[i];
            }else{
                if (i == 0 && str[i] == '+') {
                    negative = false;
                }else if (i == 0 && str[i] == '-'){
                    negative = true;
                }else{
                    return 0;
                }
            }
        }
        if (vaildStr.empty()) {
            return 0;
        }
        long long  num=0;
        for (int i=0; i<vaildStr.length(); i++) {
            num = num*10+(vaildStr[i]-'0');
        }
        if (negative) {
            num = -num;
        }
        return num;
    }
    
    void test_StrToInt(){
        std::string s("123");
        std::cout << "test_StrToInt starting........" << std::endl;
        std::cout << StrToInt(s) << std::endl;
    }
    
}

#endif /* StrToInt_hpp */
