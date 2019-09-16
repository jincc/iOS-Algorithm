//
//  combinationSum.h
//  array
//
//  Created by junlongj on 2019/8/28.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef combinationSum_hpp
#define combinationSum_hpp

#include <stdio.h>
#include <vector>
/*
 39. 组合总和
 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 
 candidates 中的数字可以无限制重复被选取。
 
 说明：
 
 所有数字（包括 target）都是正整数。
 解集不能包含重复的组合。
 示例 1:
 
 输入: candidates = [2,3,6,7], target = 7,
 所求解集为:
 [
 [7],
 [2,2,3]
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/combination-sum
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    /*
     解题思路:
     回溯枚举法.我们的目的是要在目标数组里面找N个数字和等于一个给定的数，那么我们可以利用枚举法，每次递归把candidates里面的每一个值拿来试试，如果不满足的话，那么拿下一个值再来试试。
     
        为了保证不出现重复的集合，我们只从ctindex向后查找，这避免了重复集合的产生.
    
     */
    using namespace std;
    vector<vector<int>> results;
    void _combinationSum(vector<int>& candidates,vector<int> elements, int target, int ctindex){
        if (target == 0){
            results.push_back(elements);
            return;
        }
        for (int i=ctindex;i<candidates.size();i++){
            if (target >= candidates[i]){
                elements.push_back(candidates[i]);
                _combinationSum(candidates ,elements , target-candidates[i],i);
                elements.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if (candidates.empty()) return {};
        vector<int> elements;
        _combinationSum(candidates, elements, target, 0);
        return results;
    }
}
#endif /* combinationSum_hpp */
