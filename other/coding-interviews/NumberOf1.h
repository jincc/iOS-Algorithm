//
//  NumberOf1.h
//  other
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef NumberOf1_hpp
#define NumberOf1_hpp

#include <stdio.h>
#include <string>
/*
 剑指Offer（十一）：二进制中1的个数
 输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
 
 https://www.nowcoder.com/practice/8ee967e43c2c4ec193b040ea7fbb10b8?tpId=13&tqId=11164&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    int  NumberOf1(long long  n) {
        int count = 0;
        while (n) {
            //N每次和1做&运算，计算出最右边的二进制是否为1.然后在右移一位.但是如果N为负数时，n右移会在最高位补1(为了保证数据为负数),所以会陷入死循环》
            if (n & 1)
                count++;
            n =  n >> 1;
        }
        return count;
    }
    //为了避免上面负数导致的死循环，我们现在通过左移的方式，移动临时变量flag(1)。但是这样操作的话，int 32位，就需要移动32次.
    int  NumberOf1_2(long long  n) {
        int count = 0;
        int flag = 1;
        while (flag) {
//            std::cout << flag << ", "<<std::endl;
            if (flag & n){
                count++;
            }
            flag <<= 1;
        }
        return count;
    }
    void test_NumberOf1(){
        std::cout << "test_NumberOf1 starting........." << std::endl;
        std::cout << NumberOf1_2(5) << std::endl;
    }
}

#endif /* NumberOf1_hpp */
