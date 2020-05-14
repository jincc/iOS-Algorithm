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
    double myPowWithSignedExponent(double x, int n);
    int equal(double x, double y);
    double myPow(double x, int n){
        if (equal(x, 0) && n < 0){
            return 0;//输入无效
        }
        //指数存在正数和负数
        signed int absN = n > 0 ? -n : n;
        double res = myPowWithSignedExponent(x, absN);
        if (n < 0){
            res = 1.0 / res;
        }
        return res;
    }
    int equal(double x, double y){
        if (x - y <= 0.0000001 && x - y >= -0.0000001){
            return 1;
        }
        return 0;
    }
    double myPowWithSignedExponent(double x, int n){
        if (n == 0) return 1;
        if (n == -1) return x;
        double val = myPowWithSignedExponent(x, n >> 1);
        val *= val;
        if (n % 2 == -1)
            val *= x;
        return val;
    }
    
    void test_Power(){
        std::cout << "Power starting......." <<std::endl;
        std::cout << myPow(2, 3) << std::endl;
    }
}

#endif /* Power_hpp */
