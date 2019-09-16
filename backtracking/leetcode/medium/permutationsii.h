//
//  permutationsii.h
//  backtracking
//
//  Created by junl on 2019/9/13.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef permutationsii_hpp
#define permutationsii_hpp

#include <stdio.h>
#include <vector>
/*
 47.全排列II
 给定一个可包含重复数字的序列，返回所有不重复的全排列。
 
 示例:
 
 输入: [1,1,2]
 输出:
 [
 [1,1,2],
 [1,2,1],
 [2,1,1]
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/permutations-ii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    using namespace std;
    /*
     思路：
     和46题相比，关键在于如何去除重复集合。首先应该联想到对数组进行排序，这样递归的时候很容易发现重复数字，然后跳过重复数字即可.
     
     对于这题来说，因为每个数字只能使用一次，首先，肯定需要一个状态来保存元素的使用情况，即visited.
     后面画出树状图，根据nums[i] == nums[i-1] && !visited[i-1]可以准确的过滤掉重复的数据
     */
    class Solution47 {
    public:
        vector<vector<int>> permuteUnique(vector<int>& nums) {
            vector<int> elements;
            vector<bool> visited;
            visited.resize(nums.size());
            fill(visited.begin(),visited.end(),false);
            sort(nums.begin(), nums.end());
            permuteUnique(nums, elements, visited);
            return results;
        }
        
    private:
        vector<vector<int>> results;
        
        void  permuteUnique(vector<int>& nums, vector<int> elements, vector<bool> visited){
            if (nums.size() == elements.size()){
                results.push_back(elements);
                return;
            }
            
            for(int i=0;i<nums.size();i++){
                //如果当前元素已经被选中中，跳过
                if (visited[i])
                    continue;
                /*
                 如果有重复元素，比如有{s1,s1,..s1,[....]}，那么结果只有一种情况:即{s1,[后面的元素....]}
                 怎么过滤到重复数字呢？有两种方法:
                 1). !visited[i-1] and continue，相当于选择第一个s1
                 2).  visited[i-1] and continue, 相当于选择最后一个s1
                 */
                if ( i > 0 && nums[i] == nums[i-1] && !visited[i-1])
                    continue;
                elements.push_back(nums[i]);visited[i] = true;
                permuteUnique(nums, elements, visited);
                elements.pop_back();visited[i] = false;
            }
            
        }
    };
}
#endif /* permutationsii_hpp */
