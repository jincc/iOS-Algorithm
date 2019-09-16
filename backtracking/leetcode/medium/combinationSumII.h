//
//  combinationSumII.h
//  backtracking
//
//  Created by junl on 2019/9/12.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef combinationSumII_hpp
#define combinationSumII_hpp

#include <stdio.h>
#include <vector>
/*
 40.组合总和II
 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 
 candidates 中的每个数字在每个组合中只能使用一次。
 
 说明：
 
 所有数字（包括目标数）都是正整数。
 解集不能包含重复的组合。
 示例 1:
 
 输入: candidates = [10,1,2,7,6,1,5], target = 8,
 所求解集为:
 [
 [1, 7],
 [1, 2, 5],
 [2, 6],
 [1, 1, 6]
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/combination-sum-ii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */

namespace leetcode {
    using namespace std;
    /*
     我们要在数组中选N个数，它们的和为target.每个元素不能重复使用.
     拿到这种题型， ”在一组可能的解中，寻找满足期望的解“，首先联想到回溯算法.我们把每一个元素拿到集合里面试一试，不行的话换下一个试试。
     */
    vector<vector<int>> results;
    void combinationSumII(vector<int>& candidates, vector<int> elements, int target, int ctindex){
        //终止条件
        if (target < 0)
            return;
        if (target == 0){
            results.push_back(elements);
            return;
        }
        //分解过程，逐一击破
        for (int i=ctindex;i < candidates.size(); i++){
            if (target < candidates[i])
                continue;
            //TODO:重点怎么去跳过重复的值
            if (i > ctindex && candidates[i] == candidates[i-1])//跳过重复的值
                continue;
            
            elements.push_back(candidates[i]);
            combinationSumII(candidates, elements, target-candidates[i], i+1);
            elements.pop_back();
        }
        
    }
    vector<vector<int>> combinationSumII(vector<int>& candidates, int target) {
        vector<int> elements;
        sort(candidates.begin(), candidates.end());
        combinationSumII(candidates, elements, target, 0);
        return results;
    }
    
    void test_combinationSumII(){
        vector<int> a{10,1,2,7,6,1,5};
        auto x = combinationSumII(a, 8);
        cout << "combinationSumII starting......." << endl;
        for (auto &v :x ){
            for (auto i : v){
                cout << i << ",";
            }
            cout << endl;
        }
    }
}
#endif /* combinationSumII_hpp */
