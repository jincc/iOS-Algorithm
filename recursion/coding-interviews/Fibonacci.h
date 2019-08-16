//
//  Fibonacci.h
//  recursion
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef Fibonacci_hpp
#define Fibonacci_hpp

#include <stdio.h>
/*
 剑指Offer（七）：裴波那契数列
 https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=13&tqId=11160&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */
namespace codinginterviews {
    int Fibonacci(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return Fibonacci(n-2) + Fibonacci(n-1);
    }
    long long Fibonacci2(int n) {
        long long  dp[n+1];
        memset(dp, 0, sizeof(dp));
        dp[0]=0;
        dp[1]=1;
        for (int i=2; i<=n; i++) {
            dp[i] = dp[i-2]+dp[i-1];
        }
        return dp[n];
    }
    int Fibonacci3(int n) {
        int f0,f1,f2;
        f0 = 0;
        f1 = 1;
        if (n == 0) return f0;
        if (n == 1) return f1;
        for (int i=2; i<=n; i++) {
            f2 = f0+f1;
            f0 = f1;
            f1 = f2;
        }
        return f2;
    }
    void test_Fibonacci(){
        std::cout << "Fibonacci starting......" << std::endl;
        std::cout << Fibonacci2(39) << std::endl;//63245986 63245986
    }
}
#endif /* Fibonacci_hpp */
