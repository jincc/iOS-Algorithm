//
//  Power.h
//  other
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef Power_hpp
#define Power_hpp

#include <stdio.h>
/*
 剑指Offer（十二）：数值的整数次方
 给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
https://www.nowcoder.com/practice/1a834e5e3e1a4b7ba251417554e07c00?tpId=13&tqId=11165&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */

namespace codinginterviews {
    //注意exponent的取值，可正可负
    double Power(double base, int exponent) {
        if (exponent == 0) {
            return 1;
        }
        bool neg = false;
        if (exponent < 0 ){
            exponent = -exponent;
            neg = true;
        }
        double value = 1;
        for (int i=1; i<=exponent; i++) {
            value *= base;
        }
        return neg ? 1/value : value;
    }
    
    void test_Power(){
        std::cout << "Power starting......." <<std::endl;
        std::cout << Power(2, 3) << std::endl;
    }
}

#endif /* Power_hpp */
