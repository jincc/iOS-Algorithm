//
//  maximizingXor.h
//  bit
//
//  Created by junl on 2020/5/14.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef maximizingXor_h
#define maximizingXor_h

/*
 题目：https://www.hackerrank.com/challenges/maximizing-xor/problem
 先通过异或运算求出a和b有哪些位不一样，这样我们就知道最左边的1位于什么位置了，通过不断的右移，这样就可以定位到最左边的位置. 那么最大值就为最左位为0，后面全为1. 因为
 
 LxorR可以知道不变位。从L到R的范围内，任意两个整数异或的结果可能都不一样，但是必然存在前几位相同的特性。例如：L= 11110，R=11010.在其范围内的AxorB的结果一定是00xxx的模式
 */

int maxXor(int a, int b){
    int value = a ^ b, result = 1;
    while(value){
        value = value >> 1;
        result = result << 1;
    }
    return result - 1;
}
#endif /* maximizingXor_h */
