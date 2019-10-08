//
//  double11advance.h
//  dp
//
//  Created by junl on 2019/9/30.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef double11advance_hpp
#define double11advance_hpp

#include <stdio.h>
/*
 双11打折优惠，比如满200元减50，我们的目的是挑选出购物车的某些商品，竟可能的贴近200元，这样就可以极大限度的薅羊毛。
 */
class double11advance {
public:
    int double11advance_backtracking(const int values[], int n, int discountValue){
        double11advance_backtracking(values, n, discountValue, 0, 0);
        return result;
    }
private:
    int result = INT_MAX;
    void  double11advance_backtracking(const int values[], int n, int discountValue, int shopCartValue, int shopIndex){
        //如果所以商品数量都测试过，或者当前购物车的总价已经超过了discountValue，直接退出.
        if (shopIndex == n || shopCartValue >= discountValue) {
            if (shopCartValue >= discountValue) {
                result = std::min(result, shopCartValue);
            }
            return ;
        }
        double11advance_backtracking(values, n , discountValue, shopCartValue, shopIndex+1);
        double11advance_backtracking(values, n,  discountValue, shopCartValue+values[shopIndex], shopIndex+1);
    }
};

class double11advance_dp{
public:
    int solve(const int values[], int n, int discountValue){
        //其实这个问题和0-1背包基本上求解是相似的.
        int maxinputvalue = discountValue * 2;//如果超过这个价格，那么这个羊毛就没价值去hao了.
        bool st[n][maxinputvalue];
        memset(st, false, sizeof(st));
        
        //第一个物品
        st[0][0] = true;
        if (values[0] <= maxinputvalue) {
            st[0][values[0]] = true;
        }
        
        for (int i=1; i<n; i++) {
            for (int j=0; j<=maxinputvalue; j++) {
                if (st[i-1][j]) {
                    st[i][j] = true;
                }
            }
            
            for (int j=maxinputvalue-values[i]; j>=0; j--) {
                if (st[i-1][j]) {
                    st[i][j+values[i]] = true;
                }
            }
        }
        
        //获取最接近discountValue的购物车商品总价格
        int ctvalue = -1;
        for (int i=discountValue; i<=maxinputvalue; i++) {
            if (st[n-1][i]) {
                ctvalue = i;
                break;
            }
        }
        if (ctvalue == maxinputvalue) {
            return -1;
        }
        int result = ctvalue;
        //获取之前购买了哪些商品.
        //这些商品的总价值为ctvalue. 购买过的状态都保存在st里面.
    //st[i][j]是由st[i-1][j]或者st[i-1][j-values[i]]推到出来的，所以如果st[i-1][j-values[i]]为true的话，那么该商品就被购买过.
        std::cout << "购买的商品为: "<<std::endl;
        for (int i=n-1; i>=1; i--) {
            if (ctvalue - values[i] >= 0  && st[i-1][ctvalue - values[i]] == true ) {
                std::cout << values[i] << ", ";
                ctvalue-=values[i];
            }
        }
        
        if (ctvalue == values[0]) {
            std::cout << values[0];
        }
        std::cout << std::endl;
        return result;
    }
    
};

static const int SHOPCART[6] = {40,30,60,70,70,90};

void test_double11advance(){
    std::cout << "双11怎么才可以最大限度的薅羊毛: \n" << std::endl;
    class double11advance so;
    class double11advance_dp so_dp;
    int result = so.double11advance_backtracking(SHOPCART, 6, 200);
    std::cout << "购物车的价值为: " << result << std::endl;
    
    std::cout << "\n------动态规划求解-------\n" << std::endl;
    result = so_dp.solve(SHOPCART, 6, 200);
    std::cout << "购物车的价值为: " << result << std::endl;
}





#endif /* double11advance_hpp */
