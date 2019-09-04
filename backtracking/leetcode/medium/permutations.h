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
