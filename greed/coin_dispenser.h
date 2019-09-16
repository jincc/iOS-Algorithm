//
//  coin_dispenser.h
//  greed
//
//  Created by junl on 2019/9/9.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef coin_dispenser_hpp
#define coin_dispenser_hpp

#include <stdio.h>
#include <vector>
using namespace std;

/**
 假设我们有100元，50，20，10，5，2，1这些面额的纸币，它们分别的张数为a1,a2,a3....张.
 题目是使用最少的纸币数目来支付K元.
 */
int coin_dispenser(vector<int> &cointypes,vector<int> &coincounts, int targetmoney){
    /*
     限制值：筹齐这targetmoney
     期望值: 纸币数量最小
     贪心思想：对于贡献一张纸币来说(期望值),我们肯定希望它的价值越大，因为这样意味着更少的张数.
     */
    int count=0;
    for (size_t i=cointypes.size()-1; i>=0;) {
        if (targetmoney <= 0 ) 
            break;
        
        if (targetmoney >= cointypes[i] && coincounts[i]>0) {
            count++;
            coincounts[i]--;
            targetmoney -= cointypes[i];
        }else{
            i--;
        }
    }
    if (targetmoney > 0) {
        throw "钱不够啊";
    }
    return count;
}

#endif /* coin_dispenser_hpp */
