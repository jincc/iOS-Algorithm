//
//  jumpFloor.h
//  recursion
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef jumpFloor_hpp
#define jumpFloor_hpp

#include <stdio.h>
/*
 剑指Offer（八）：跳台阶
 一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。
 https://www.nowcoder.com/practice/8c82a5b80378478f9484d87d1c5f12a4?tpId=13&tqId=11161&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    int jumpFloor(int number) {
        if (number == 0) return 0;
        if (number == 1) return 1;
        if (number == 2) return 2;
        return jumpFloor(number-1) + jumpFloor(number-2);
    }
    
    int jumpFloor2(int number) {
        if (number == 0) return 0;
        if (number == 1) return 1;
        if (number == 2) return 2;
        int dp[number];
        memset(dp, 0, sizeof(dp));
        dp[0]=1;
        dp[1]=2;
        for (int i=2; i<number; i++) {
            dp[i]=dp[i-2]+dp[i-1];
        }
        return dp[number-1];
    }
    void test_jumpFloor(){
        std::cout << "test_jumpFloor starting........" << std::endl;
        std::cout << jumpFloor(10) << std::endl;//89
    }
}
#endif /* jumpFloor_hpp */
