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

int maxweight = INT_MIN;
void knapsack(const int weights[], int n, int limitweight, int ct,int ctweight){
    if (ctweight == limitweight || ct == n) {
        maxweight = std::max(maxweight, ctweight);
        return;
    }
    if (ctweight+weights[ct] <= limitweight) {
        knapsack(weights, n, limitweight, ct+1, ctweight+weights[ct]);
    }
    knapsack(weights, n, limitweight, ct+1, ctweight);
}

int knapsack(const int weights[], int n, int limit){
    knapsack(weights, n, limit, 0, 0);
    return maxweight;
}

#endif /* knapsack_hpp */
