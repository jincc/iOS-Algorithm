//
//  best_time_to_buy_and_sell_stock_ii.h
//  array
//
//  Created by junlongj on 2019/8/9.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef best_time_to_buy_and_sell_stock_ii_hpp
#define best_time_to_buy_and_sell_stock_ii_hpp

#include <stdio.h>
#include <vector>
/*
 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 
 设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
 
 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 
 示例 1:
 
 输入: [7,1,5,3,6,4]
 输出: 7
 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
      随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    int maxProfit_II(std::vector<int>& prices) {
        //思路:寻找波峰后的上升区间，然后全部加起来，这样是最赚钱的。
        int low=-1;
        int max=0;
        for(int i=0;i+1<prices.size();i++){
            if (prices[i]<prices[i+1]&&low<0){
                low=i;
                continue;
            }
            if (prices[i]>prices[i+1] && low >= 0){
                max+=(prices[i]-prices[low]);
                low=-1;
            }
        }
        if (low>=0){
            max+=(prices[prices.size()-1]-prices[low]);
        }
        return max;
    }
    /*
     思路：分析上面那张找波峰和波谷的方法，我们可以知道，其实只要prices[i+1]>prices[i],那么每一截相加的值其实就等于波峰减去波谷。
     */
    int maxProfit_III(std::vector<int>& prices) {
        if (prices.empty()) return 0;
        int max=0;
        for(int i=0;i<prices.size()-1;i++){
            if (prices[i+1]>prices[i]){
                max+=prices[i+1]-prices[i];
            }
        }
        return max;
    }
}
#endif /* best_time_to_buy_and_sell_stock_ii_hpp */
