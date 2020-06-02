//
//  coinChange.h
//  dp
//
//  Created by junl on 2019/10/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef coinChange_hpp
#define coinChange_hpp

#include <stdio.h>
/*
 硬币找零问题。比如我们现在有硬币1元，3元，5元，我们需要支付w元，那么最少需要多少个硬币.
 思路：
    1. 贪心法，每次首先尝试最大面值的币种
 */
class coinChange {
public:
    //贪心法，首先尝试最大面值的币种
    void solve(const int coins[], int n, int money, int currentCoinCount){
        if (money == 0 || currentCoinCount == n) {
            result = std::min(result, currentCoinCount);
            return;
        }
        for (int i=n-1; i>=0; i--) {
            if (money >= coins[i]) {
                solve(coins, n, money - coins[i], currentCoinCount+1);
            }
        }
        
    }
    int solve(const int coins[], int n, int money){
        solve(coins, n, money, 0);
        return result;
    }
private:
    int result = INT_MAX;
};

int min(int x, int y){ return x < y ? x : y;}
int coinChange(int* coins, int coinsSize, int amount){
    if (coins == NULL || coinsSize <= 0) return 0;
    int st[amount+1];
    memset(st, 0, sizeof(st));
    
    for(int i = 1; i <= amount; i++){
        int m_coin = INT_MAX;
        for(int j=0; j < coinsSize; j++){
            if (i >= coins[j] && st[i-coins[j]]!= -1){
                m_coin = min(m_coin, st[i-coins[j]] + 1);
            }
        }
        st[i] = m_coin == INT_MAX ? -1 : m_coin;
    }
    return st[amount];
}





void test_coinChange(){
    std::cout << "------------硬币找零问题----------" << std::endl;
    class coinChange so;
    int coins[] = {1,3,5};
    std::cout << so.solve(coins, 3, 9) << std::endl;
    std::cout << coinChange(coins, 3, 9) << std::endl;
}


#endif /* coinChange_hpp */
