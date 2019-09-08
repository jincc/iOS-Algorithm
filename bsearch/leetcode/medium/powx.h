//
//  powx.h
//  bsearch
//
//  Created by junl on 2019/9/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef powx_hpp
#define powx_hpp

#include <stdio.h>
/*
 实现 pow(x, n) ，即计算 x 的 n 次幂函数。
 
 示例 1:
 
 输入: 2.00000, 10
 输出: 1024.00000
 示例 2:
 
 输入: 2.10000, 3
 输出: 9.26100
 示例 3:
 
 输入: 2.00000, -2
 输出: 0.25000
 解释: 2-2 = 1/22 = 1/4 = 0.25
 说明:
 
 -100.0 < x < 100.0
 n 是 32 位有符号整数，其数值范围是 [−231, 231 − 1] 。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/powx-n
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路:
     常规思路，O(n)循环，每次乘以x,当n很大时，会超时.
     */
    //bad
    double myPow2(double x, int n){
        long  N = n; //这里用long来保存，因为-n可能会导致数据溢出。
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double ans = 1;
        for (long  i = 0; i < N; i++)
            ans = ans * x;
        return ans;
    }
    /*
     思路二:
     利用x^n * x^n = x^(2n)这个公式。如果我们已知x^(n/2)的话，那么我们可以直接计算出x^n了。那怎么求解x^(n/2)呢，又通过x^(n/4),这不就是递归吗?
     */
#pragma mark - 快速幂递归
    //good
    double fastPow(double x , long n){
        if (n == 0) {
            return 1.0;
        }
        double r = fastPow(x, n/ 2);
        if (n % 2 == 0) {
            //如果是偶数的话
            return r * r;
        }else{
            return r * r  * x;//比如5 = 2 * 2 + 1
        }
    }
    double myPow(double x, int n){
        long  N = n; //这里用long来保存，因为-n可能会导致数据溢出。
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        return fastPow(x, N);
    }
    #pragma mark - 快速幂循环
    /*
     思路:
     现在我们要计算x^n。我们把n看成二进制编码，那么N可以利用二进制运算计算得出。比如:
     
     x = 2 , n = 5， 0101
     那么 x^n =  x^1 *  x^4，即当二进制当前位i的值为1时，我们需要乘以x^(2^i).
     */
    double myPow3(double x, int n){
        long  N = n; //这里用long来保存，因为-n可能会导致数据溢出。
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double result = 1.0;
        double ctPositionValue = x;
        for (long i=n; i>0; i>>=1) {
            if (i & 1 ) {//如果末尾为1的话
                result *= ctPositionValue;
            }
            ctPositionValue*=ctPositionValue;//1,2,4,8,16
        }
        return result;
    }
    
    void test_pow(){
        std::cout << myPow3(2.0,INT32_MAX) << std::endl;
        std::cout << myPow3(2.0,20) << std::endl;
        std::cout << myPow2(2.0,20) << std::endl;
    }
}
#endif /* powx_hpp */
