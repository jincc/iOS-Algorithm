//
//  main.cpp
//  dp
//
//  Created by junlongj on 2019/7/23.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "knapsack.h"
#include "minPathSum.h"
#include "climbStairs.h"
static const int KNAPSACK[5]={2,2,4,6,3};
static const int VALUE[5]   ={3,4,8,9,6};
static const int SHOPCART[5] = {40,50,60,70,80};
static const int COINS[3] = {1,3,5};
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    cout << "0-1背包问题" << endl;
    cout << knapsack(KNAPSACK, 5, 9) << endl;
    cout << knapsack(KNAPSACK, VALUE, 5, 9) << endl;
    cout << "购物车打折问题： " << double11advance(SHOPCART, 5, 200) << endl;
    cout << "硬币找零问题，1,3,5的面值，目标9元：" << endl;
//    cout << coinChange(COINS, 3, 9, 0) << endl;
    cout << coinChange2(COINS, 3, 9, 0) << endl;
    return 0;
}
