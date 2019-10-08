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
 0-1背包问题. 对于一组不同质量，不可分割的物品，我们需要选择一些放入背包中，在满足最大重量限制的条件下，背包中所能放入的最大值是多少?
 
 回溯思路：将问题的求解分成N个阶段，每个阶段的商品选择，我们可以选择加入背包，也可以选择不加入背包。加入背包时，必须要满足不能超过wkg的限制.
 动态规划思路：将问题的求解分成N个阶段，每个阶段对应一次选择，每次选择后，会产生不同的状态，我们记录每一个阶段的状态集合，然后通过当前的状态集合来推导出下一阶段的状态集合，动态的向前推进。
 */

#pragma mark - 0-1回溯
class knapsack {
public:
    int backtrack(const int weights[], int n, int limitweight){
        backtrack(weights, n, limitweight, 0, 0);
        return result;
    }
private:
    int result = INT_MIN;
    void backtrack(const int weights[], int n, int limitweight, int ctweight, int index){
        if (index == n || ctweight >= limitweight){
            result = std::max(result, ctweight);
            return;
        }
        backtrack(weights, n, limitweight, ctweight, index+1);
        if (ctweight + weights[index] <= limitweight) {
            backtrack(weights, n, limitweight, ctweight + weights[index], index+1);
        }
    }
};

#pragma mark - 0-1动态规划
class knapsack_dp{
public:
    int backtrack(const int weights[], int n, int limitweight){
        bool st[n][limitweight+1];
        memset(st, false, sizeof(st));
        //第一个物品
        st[0][0]=true;//不放
        if (weights[0] <= limitweight) {
            st[0][weights[0]] = true; //放
        }
        //对于后面的状态，动态的推导
        for (int i=1; i<n; i++) {
            //对于前面已经选择过的状态st[i-1][.......]，我们可以推算出st[i][.......]
            for (int j=0; j<=limitweight; j++) { //不放
                if (st[i-1][j]) {
                    st[i][j]=st[i-1][j];
                }
            }
            
            for (int j=0; j<=limitweight-weights[i]; j++) {//放
                if (st[i-1][j]) {
                    st[i][j+weights[i]] = true;
                }
            }
        }
        
        for (int i=limitweight; i>=0; i--) {
            if (st[n-1][i]) {
                return i;
            }
        }
        return 0;
    };
};

#pragma mark - 0-1升级版
/*
 对于一组不同质量，不同价值，不可分割的物品，我们选择将某些物品加入到背包中，在满足最大重量限制的条件下，背包中可转入物品的总价值最大是多少?
 */
class knapsack2{
public:
    //回溯法，穷举出所有的解法，然后保存最大值
    int knapsack(const int weights[], const int values[], int n, int limitweight){
        knapsack(weights, values, n, limitweight, 0, 0, 0);
        return maxValue;
    }
    
private:
    int maxValue = INT_MIN;
    void knapsack(const int weights[], const int values[], int n, int limitweight, int ctindex, int ctweight, int ctvalue){
        
        if (ctindex == n || ctweight >= limitweight){
            maxValue = std::max(maxValue, ctvalue);
            return;
        }
        
        knapsack(weights, values, n, limitweight, ctindex+1, ctweight, ctvalue);
        if (ctweight+weights[ctindex] <= limitweight) {
            knapsack(weights, values, n, limitweight, ctindex+1, weights[ctindex]+ctweight, ctvalue+values[ctindex]);
        }
    }
};

class knapsack_dp2 {
public:
    /*
     动态规划：
     问题的求解，分成N个阶段，每个阶段对应一次抉择，每次抉择之后，背包中物品的重量和价值都会发生变化，我们合并这些状态，在同等重量的物品组合中，我们使用高价值的物品组合。然后基于这些状态来推导出下一层的状态.
     */
    int knapsack(const int weights[], const int values[], int n, int limitweight){
        
        int states[n][limitweight+1];
        memset(states, -1, sizeof(states));
        //第一个物品
        states[0][0] = 0;
        if (weights[0] <= limitweight) {
            states[0][weights[0]] = values[0];
        }
        
        for (int i=1; i<n; i++) {
            for (int j=0; j<=limitweight; j++) {
                if (states[i-1][j] != -1) {
                    states[i][j] = states[i-1][j];
                }
            }
            
            for (int j=limitweight-weights[i]; j>=0; j--) {
                if (states[i-1][j] != -1) {
                    states[i][j+weights[i]] = std::max(states[i][j+weights[i]], states[i-1][j]+values[i]);
                }
            }
        }
        
        int maxvalue = -1;
        for (int i=0; i<=limitweight; i++) {
            if (states[n-1][i] != -1) {
                maxvalue = std::max(maxvalue, states[n-1][i]);
            }
        }
        return maxvalue;
    }
};




static const int KNAPSACK_[5]={2,2,4,6,3};
static const int VALUE_[5]   ={3,4,8,9,6};
void test_knapsack(){
    
    class knapsack so;
    class knapsack_dp so_dp;
    int result = so.backtrack(KNAPSACK_, 5, 5);
    std::cout << "---------------\n" << "0-1背包问题,回溯:" << std::endl;
    std::cout << result << std::endl;
    
    std::cout << "0-1背包问题,动态规划:" << std::endl;
    std::cout << so_dp.backtrack(KNAPSACK_, 5, 5) << std::endl;
    
    
    class knapsack2 so2;
    class knapsack_dp2 so_dp2;
    int maxvalue = so2.knapsack(KNAPSACK_, VALUE_, 5, 9);
    std::cout << "0-1背包升级问题, 回溯: " << std::endl;
    std::cout << maxvalue << std::endl;
    
    maxvalue = so_dp2.knapsack(KNAPSACK_, VALUE_, 5, 9);
    std::cout << "0-1背包升级问题, 动态规划: " << std::endl;
    std::cout << maxvalue << std::endl;
}



#endif /* knapsack_h */
