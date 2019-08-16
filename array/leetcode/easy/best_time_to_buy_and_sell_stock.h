//
//  best_time_to_buy_and_sell_stock.h
//  array
//
//  Created by junlongj on 2019/8/8.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef best_time_to_buy_and_sell_stock_hpp
#define best_time_to_buy_and_sell_stock_hpp

#include <stdio.h>
#include <vector>
/*
121. 买卖股票的最佳时机
 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 
 如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。
 
 注意你不能在买入股票前卖出股票。
 
 示例 1:
 
 输入: [7,1,5,3,6,4]
 输出: 5
 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
 注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路：如果我们设立一个状态数组，里面states[i]存储的是在哪一天购买股票能够带来最大收益。
     那么根据前一天的状态是能计算出后一天的状态的.
     */
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) return 0;
        int max = 0;
        int buys[prices.size()];
        buys[0] = prices[0];
        for (int i = 1; i< prices.size();i++){
            if (prices[i]-buys[i-1] < 0){
                buys[i]=prices[i];
            }else{
                buys[i]=buys[i-1];
            }
            max = std::max(max,prices[i]-buys[i]);
        }
        return max;
    }
}
#endif /* best_time_to_buy_and_sell_stock_hpp */
