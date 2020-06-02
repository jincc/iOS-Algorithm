//
//  knapsack.h
//  backtracking
//
//  Created by junl on 2019/7/25.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef knapsack_hpp
#define knapsack_hpp

#include <stdio.h>
/**
 0-1背包问题. 对于一组不同质量，不可分割的物品，我们需要选择一些放入背包中，在满足最大重量限制的条件下，背包中所能放入的最大值是多少?
 */

void backpack01_bt(int weights[], int n, int level, int ctweight,int limitweight, int *result);
int backpack01(int weights[], int n, int limitweight){
    int result = 0;
    backpack01_bt(weights, n, 0, 0, limitweight, &result);
    return result;
}
void backpack01_bt(int weights[], int n,int level, int ctweight,int limitweight, int *result){
    if (level == n || *result == limitweight){
        if (*result < ctweight){
            *result = ctweight;
        }
        return;
    }
    
    backpack01_bt(weights, n, level+1, ctweight, limitweight, result);
    if (ctweight + weights[level] <= limitweight)
        backpack01_bt(weights, n, level+1, ctweight + weights[level], limitweight, result);
    
}
#endif /* knapsack_hpp */
