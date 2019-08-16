//
//  mySqrt.h
//  bsearch
//
//  Created by junl on 2019/7/19.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef mySqrt_hpp
#define mySqrt_hpp

#include <stdio.h>
/*
 69.实现 int sqrt(int x) 函数。
 
 计算并返回 x 的平方根，其中 x 是非负整数。
 
 由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。
 
 示例 1:
 
 输入: 4
 输出: 2
 示例 2:
 
 输入: 8
 输出: 2
 说明: 8 的平方根是 2.82842...,
      由于返回类型是整数，小数部分将被舍去。
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/sqrtx
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */

int mySqrt(int x) {
    if (x==1)
        return 1;
    int start=0;
    //the sqt is not greater than x/2+1
    int end=x/2+1;
    while (start <= end) {
        int mid = start + (end-start)/2;
        long long sq = (long long)mid * (long long)mid;
        if (sq == x) return mid;
        if (sq < x) {
            start = mid+1;
        }else{
            end = mid -1;
        }
    }
    return end;
}
#endif /* mySqrt_hpp */
