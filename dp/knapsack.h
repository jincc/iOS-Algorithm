//
//  knapsack.h
//  dp
//
//  Created by junlongj on 2019/7/23.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef knapsack_h
#define knapsack_h
#include <memory>
#include <iostream>
/*
   ************************** DP ****************************
    DP思想就是将整个过程分为N个阶段，每个阶段都会有一次决策，决策完之后，将当前状态保存，然后计算下一次状态时，利用上一次的状态推算出当前新的状态.
 */

/**
 0-1背包问题. 对于一组不同质量，不可分割的物品，我们需要选择一些放入背包中，在满足最大重量限制的条件下，背包中所能放入的最大值是多少?

 @param weights 里面存放着不同物品的重量
 @param n 物品的个数
 @param limitweight 背包限制的重要
 @return 背包所能存放的最大值
 */
int knapsack(const int weights[], int n, int limitweight){
    
    bool states[limitweight+1];
    //对于第0个物品，可以放入背包，也可以不放入
    states[0] = true;
    if (weights[0] < limitweight) {
        states[weights[0]] = true;
    }
    
    for (int i=1; i<n; i++) {
        //第i个物品能不能放入背包呢?
        for (int j=limitweight-weights[i]; j>=0; j--) {
            //如果质量为j的已经放进去过，那么j+weight[i]也能放进去
            if (states[j]){
                states[j+weights[i]] = true;
            }
        }
    }
    
    for (int i=limitweight; i>=0; i--) {
        if (states[i]) return i;
    }
    
    return 0;
}


/**
 0-1背包变体。对于一组不同质量，不同价格,不可分割的物品，我们需要选择一些放入背包中，在满足最大重量限制的条件下，背包中物品的总价值的最大值是多少?

 @param weights 里面存放着不同物品的重量
 @param values 里面存放着不同物品的价值
 @param n 物品的个数
 @param limitweight 背包限制的重要
 @return 背包物品总价值的最大值
 */
int knapsack(const int weights[], const int values[], int n, int limitweight){
    int states[n][limitweight+1];//里面保存的是第一个物品在XX重量下的最大价格
    for (int i=0; i<n; i++) {
        for (int j=0; j<=limitweight; j++) {
            states[i][j]=-1;
        }
    }
    states[0][0]=0;
    states[0][weights[0]] = values[0];
    
    for (int i=1; i<n; i++) {
        for (int j=0; j<=limitweight; j++) {
            //如果当前物品不放在背包中，那么状态等于上一次的.
            if (states[i-1][j]>=0){
                states[i][j]=states[i-1][j];
            }
        }
        
        for (int j=0; j<=limitweight-weights[i]; j++) {
            if (states[i-1][j]>=0) {
                int newvalue = states[i-1][j]+values[i];
                states[i][j+weights[i]]= std::max(newvalue, states[i][j+weights[i]]);
            }
        }
    }
    
    int maxvalue =0;
    for (int i=limitweight; i>=0; i--) {
//        printf("i=%i,value=%i\n",i,states[n-1][i]);
        if (states[n-1][i]>maxvalue) {
            maxvalue = states[n-1][i];
        }
    }
    
    return maxvalue;
}


/**
 双11打折优惠，满200元减50，我们的目的是挑选出购物车的某些商品，竟可能的贴近200元.

 @param values <#values description#>
 @param n <#n description#>
 @param discountValue <#discountValue description#>
 */
int  double11advance(const int values[], int n, int discountValue){
    int maxValue = discountValue*2;//如果超过了这个价值，这个羊毛就没意义了
    int states[n][maxValue+1];//这里存储了两个信息，第几个商品，和当前的总价值
    states[0][0]=true;
    if (values[0] <= maxValue) {
        states[0][values[0]] = true;
    }
    for (int i=1; i<n; i++) {
        for (int j=0; j<=maxValue; j++) {
            if (states[i-1][j]) {
                states[i][j]=states[i-1][j];
            }
        }
        for (int j=maxValue-values[i]; j>=0; j--) {
            if (states[i-1][j]) {
                states[i][j+values[i]] = true;
            }
        }
    }
    int i;//表示当前的价值
    for (i=discountValue; i<=maxValue; i++) {
        if (states[n-1][i]) {
            break;
        }
    }
    if (i == maxValue+1) {
        return -1;
    }
    int ctvalue = i;
    for (int i=n-1; i>=1; --i) {
        if (ctvalue-values[i] >=0 && states[i-1][ctvalue-values[i]]==true) {
            ctvalue = ctvalue-values[i];
             std::cout << values[i] << ", ";
        }
    }
    if (ctvalue != 0 ) {
         std::cout << values[0] << std::endl;
    }
    std::cout << std::endl;
    return i;
}

int minCoinCount = INT_MAX;

/**
 硬币找零问题.

 @param coins 硬币种类
 @param n 种类数量
 @param money 需要找零的money数
 @param currentCoinCount 当前以及使用的硬币数
 @return 最小的硬币数
 */
int coinChange(const int coins[], int n, int money, int currentCoinCount){
    if (money == 0) {
        //找零结束
        minCoinCount = std::min(minCoinCount, currentCoinCount);
    }
    for (int i=n-1; i>=0; i--) {
        if (money >= coins[i]) {
            coinChange(coins, n, money-coins[i], currentCoinCount+1);
        }
    }
    return minCoinCount;
}

/*
 动态规划来解决:两个关键点:
    1. 怎么描述每个阶段状态？这里状态值得是使用第一枚硬币后的状态，所以状态至少要包含当前硬币数，当前金额数
    2. 怎么从之前的状态得到下一阶段的状态？
 
 就这个题来说，状态需要描述为二维数组，里面存储的是经过xx轮，money已经被硬币拼凑出来了。有了这个状态，就可以推导出下一轮的状态了.见下面代码1.
 */
int coinChange2(const int coins[], int n, int money, int currentCoinCount){
    int maxcoin = money;//比如用9个1元硬币
    bool  states[maxcoin][money+1];
    memset(states,false,sizeof(bool) * maxcoin * (money+1));
    //设置第一枚硬币的状态
    for (int i=0; i<n; i++) {
        if (money >= coins[i]) {
            states[0][coins[i]]=true;
        }
    }
    for (int i=1; i<maxcoin; i++) {
        for (int j=1; j<=money; j++) {
            //如果前一轮已经计算出money所需要的最小银币数的话
            if (states[i-1][j]) {
                for (int k=0; k<n; k++) {
                    if (money >= coins[k] + j) { // 1.
                        states[i][coins[k] + j] = true;
                    }
                }
                if (states[i][money] == true) {
                    return i+1;
                }
            }
        }
    }
    return money;
}



#endif /* knapsack_h */
