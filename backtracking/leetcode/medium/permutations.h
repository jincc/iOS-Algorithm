//
//  permutations.h
//  recursion
//
//  Created by junlongj on 2019/8/30.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef permutations_hpp
#define permutations_hpp

#include <stdio.h>
#include <vector>
#include <string>
/*
 46.全排列
 给定一个没有重复数字的序列，返回其所有可能的全排列。
 
 示例:
 
 输入: [1,2,3]
 输出:
 [
 [1,2,3],
 [1,3,2],
 [2,1,3],
 [2,3,1],
 [3,1,2],
 [3,2,1]
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/permutations
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    using namespace std;
    /*
     思路:符合"在一组可能的解中，选出符合期望的结果"题型，首先联想到回溯算法。
     
     我们将求解全排列求解过程，划分为N个阶段.
     每个阶段我们穷举出所有可能的情况,即在数组中选择一个数:
        1. 如果是已经选择过的直接掉过
        2. 如果未选中，进入下一轮阶段。
     
     直到N次排列完成.
     */
    class Solution_46 {
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            vector<int> elements;
            permute(nums, elements);
            return results;
        }
    private:
        vector<vector<int>> results;
        void  permute(vector<int>& nums, vector<int> elements) {
            //终止条件
            if (elements.size() == nums.size()){
                results.push_back(elements);
                return;
            }
            //递归公式
            for (auto &num : nums){
                if(find(elements.begin(),elements.end(),num) != elements.end())
                    continue;
                elements.push_back(num);
                permute(nums, elements);
                elements.pop_back();
            }
        }
    };
}

#endif /* permutations_hpp */
