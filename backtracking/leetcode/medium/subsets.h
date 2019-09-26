//
//  subsets.h
//  backtracking
//
//  Created by junl on 2019/9/23.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef subsets_hpp
#define subsets_hpp

#include <stdio.h>
/*
 78.子集
 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 
 说明：解集不能包含重复的子集。
 
 示例:
 
 输入: nums = [1,2,3]
 输出:
 [
 [3],
   [1],
   [2],
   [1,2,3],
   [1,3],
   [2,3],
   [1,2],
   []
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/subsets
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路:
     有点类似0,1背包的问题，我们把问题的求解分成N个阶段，每个阶段，我们可以选择数组nums第n个数字是否放进结果里面,最终回溯出结果.
     */
    class Solution78 {
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            vector<int> elements;
            subsets(nums, elements, 0);
            return results;
        }
        
    private:
        vector<vector<int>> results;
        void subsets(vector<int>& nums, vector<int> elements, int ctindex){
            if (ctindex == nums.size()){
                results.push_back(elements);
                return;
            }
            
            //对于数组里面的每一个元素，我们可以选择把他放进去，也可以选择不放进去.
            subsets(nums, elements, ctindex+1);
            
            elements.push_back(nums[ctindex]);
            subsets(nums, elements, ctindex+1);
            elements.pop_back();
        }
    };
}

#endif /* subsets_hpp */
