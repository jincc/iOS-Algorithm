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

class coinChange_dp {
public:
    int solve(const int coins[], int n, int money){
      //这个找零问题，每次决策后有几个状态变量，第一个是当前的money，第二个是当前使用的硬币数量.所以状态里面至少要包含这两个变量
        
        int  max_coin_count = money; //n个1元
        bool st[max_coin_count][money+1];
        memset(st, false, sizeof(st));
        
        //选择第一个硬币的初始状态
        for (int i=0; i<n; i++) {
            if (coins[i] <= money) {
                st[0][coins[i]] = true;
            }
        }
        
        for (int index=1; index <= max_coin_count; index++) { //使用第index个硬币的状态
            for (int last_money = 1; last_money <= money; last_money++) {//计算出使用index个硬币所有可达的状态
                if (st[index-1][last_money]) { //如果last_money是可达状态，即可以通过硬币筹出来，那么计算下一个阶段的状态
                    for (int k=n-1; k>=0; k--) {
                        if (last_money + coins[k] <= money) {
                            st[index][last_money + coins[k]] = true;
                        }
                    }
                }
                
                if (st[index][money]) {
                    return index+1;
                }
            }
        }
        return -1;
        
    };
};





void test_coinChange(){
    std::cout << "------------硬币找零问题----------\n" << std::endl;
    class coinChange so;
    class coinChange_dp so_dp;
    int coins[] = {1,3,5};
    std::cout << so.solve(coins, 3, 9) << std::endl;
    std::cout << so_dp.solve(coins, 3, 9) << std::endl;
}


#endif /* coinChange_hpp */
