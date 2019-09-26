//
//  subsets_ii.h
//  backtracking
//
//  Created by junl on 2019/9/26.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef subsets_ii_hpp
#define subsets_ii_hpp

#include <stdio.h>
/*
 90.子集II
 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 
 说明：解集不能包含重复的子集。
 
 示例:
 
 输入: [1,2,2]
 输出:
 [
 [2],
 [1],
 [1,2,2],
 [2,2],
 [1,2],
 []
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/subsets-ii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    class Solution90{
    public:
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            //如果前一个选中的话，后一个不选.
            if (nums.empty()) return {};
            //先排个序方便过滤重复数字
            sort(nums.begin(), nums.end());
            vector<vector<int>> results;
            vector<int> st;
            vector<int> elements;
            st.resize(nums.size());
            subsetsWithDup(nums, results,0,st,elements);
            return results;
            
        }
        
        void subsetsWithDup(vector<int>& nums, vector<vector<int>>& results, int index, vector<int> st,vector<int> elements){
            
            if (index == nums.size()){
                results.push_back(elements);
                return;
            }
            subsetsWithDup(nums, results,index+1,st,elements);
            //过滤掉重复的值，比如【1，2，2】的序列，之前第2轮已经选择了2的话，那么第三轮可以继续选择2,或者不选择.那么就可以得到[1,2,2]或者[1,2]. 如果之前没有选择2的话，那么第三轮不能在选择2，得到[1]
            if(index>0 && nums[index-1] == nums[index] && !st[index-1])
                return;
            
            elements.push_back(nums[index]);
            st[index]=true;
            subsetsWithDup(nums, results,index+1,st,elements);
            elements.pop_back();
            st[index]=false;
        }
    };
}
#endif /* subsets_ii_hpp */
