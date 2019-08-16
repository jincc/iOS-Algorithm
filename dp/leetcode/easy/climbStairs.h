//
//  climbStairs.h
//  dp
//
//  Created by junlongj on 2019/8/14.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef climbStairs_hpp
#define climbStairs_hpp

#include <stdio.h>
/*
 70.爬楼梯
 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 
 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
 
 注意：给定 n 是一个正整数。
 
 示例 1：
 
 输入： 2
 输出： 2
 解释： 有两种方法可以爬到楼顶。
 1.  1 阶 + 1 阶
 2.  2 阶
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/climbing-stairs
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    int climbStairs(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        if (n == 2) return 2;
        int dp[n];
        dp[0] = 1;
        dp[1] = 2;
        for (int i=2;i<n;i++){
            dp[i]=dp[i-2]+dp[i-1];
        }
        return dp[n-1];
    }
}
#endif /* climbStairs_hpp */
