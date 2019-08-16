//
//  jumpFloorII.h
//  recursion
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef jumpFloorII_hpp
#define jumpFloorII_hpp

#include <stdio.h>
/*
 剑指Offer（九）：变态跳台阶
 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
https://www.nowcoder.com/practice/22243d016f6b47f2a6928b4313c85387?tpId=13&tqId=11162&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking

 */
namespace codinginterviews {
    /*
     n == 1  1
     n == 2  2
     n == 3  4
     .....
     */
    int jumpFloorII(int number) {
        if (number == 0)return 0;
        int step = 1;
        for (int i= 1; i<number; i++) {
            step *=2;
        }
        return step;
    }
}

#endif /* jumpFloorII_hpp */
