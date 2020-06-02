//
//  main.cpp
//  recursion
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "Fibonacci.h"
#include "jumpFloor.h"
#include "jumpFloorII.h"
#include "rectCover.h"
#include "generateParenthesis.h"
#include "permutations.h"
#include "longestUnivaluePath.h"
#include <math.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void helper(double *nums, int len, int n, int ctsum);
double* twoSum(int n, int* returnSize){
    if (n == 0){
        if (returnSize) *returnSize = 0;
        return NULL;
    }
    
    int minSum = n;
    int maxSum = 6 * n;
    int len = maxSum - minSum + 1;
    int allPointCnts = pow(6, n);
    double *nums = (double *)malloc(sizeof(double) * len);
    for(int i=0; i < len; i++)
        nums[0] = 0;
    helper(nums, len, n, 0);
    for(int i=0; i < len;i++){
        nums[i] /= allPointCnts;
    }
    if (returnSize) *returnSize = len;
    return nums;
}
void helper(double *nums, int len, int n, int ctsum){
    if (n == 0){
        int idx = ctsum - n;
        nums[idx] += 1;
        return;
    }
    for(int i=0; i < 6;i++){
        helper(nums, len, n-1, ctsum+(i+1));
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    codinginterviews::test_Fibonacci();
    codinginterviews::test_jumpFloor();
    leetcode::test_generateParenthesis2();
    
    int s;
    double *r = twoSum(1, &s);
    for(int i=0;i<s;i++)
        printf("%f ", r[i]);
    return 0;
}
