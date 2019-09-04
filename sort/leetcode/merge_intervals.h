//
//  merge_intervals.h
//  sort
//
//  Created by junlongj on 2019/9/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef merge_intervals_hpp
#define merge_intervals_hpp

#include <stdio.h>
#include <vector>
/*
 56.合并空间
 给出一个区间的集合，请合并所有重叠的区间。
 
 示例 1:
 
 输入: [[1,3],[2,6],[8,10],[15,18]]
 输出: [[1,6],[8,10],[15,18]]
 解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 示例 2:
 
 输入: [[1,4],[4,5]]
 输出: [[1,5]]
 解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/merge-intervals
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    
    /*
     解题思路:
     输入: [[1,3],[2,6],[8,10],[15,18]]
     输出: [[1,6],[8,10],[15,18]]
     
     先将输入数组按照顺序排好序. 然后两个指针i,j从头到尾开始遍历，i指针前面的子数组，j指向后面的子数组。
     判断 vecs[i][1] 和 vecs[j][0]的大小关系：
        1. 如果 vecs[i][1] >= vecs[j][0]，那么需要合并这两个序列.
        2. 否则的话，它们不相交，vecs[i][1]加入到结果里面去. 然后继续遍历i = j;
     */
    using namespace std;
    static bool compare(vector<int> &a,vector<int> &b){
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        //sort
        if (intervals.empty()) return {};
        sort(intervals.begin(),intervals.end(),compare);
        
        //增加一个哨兵对象.
        intervals.push_back({INT_MAX,INT_MAX});
        int i=0;
        vector<vector<int>> results;
        for (int j=1;j<intervals.size();j++){
            if (intervals[i][1] >= intervals[j][0]){
                intervals[i][1] = max(intervals[i][1], intervals[j][1]);
            }else{
                results.push_back(intervals[i]);
                i=j;
            }
        }
        return results;
    }
    /*
     解题思路v2:
     
     先将intervals[0]入栈，然后通过results的栈顶元素和intervals[i]的关系，判断是将栈顶元素和intervals[i]的相交关系.
     */
    vector<vector<int>> merge_v2(vector<vector<int>>& intervals) {
        //sort
        if (intervals.empty()) return {};
        sort(intervals.begin(),intervals.end(),compare);
        
        vector<vector<int>> results;
        int i=0;
        for (;i<intervals.size();i++){
            if (results.empty()) {
                results.push_back(intervals[i]);
                continue;
            }
            int size =results.size();
            if (results[size-1][1] >= intervals[i][0]) {
                //需要合并
                results[size-1][1] = max(results[size-1][1], intervals[i][1]);
            }else{
                results.push_back(intervals[i]);
            }
        }
        return results;
    }
    
    
    
    
    
    void test_merge_intervals(){
        vector<vector<int>> a{{8,10},{15,18},{1,3},{2,6}};
        auto x = merge_v2(a);
        x;
    }
}
#endif /* merge_intervals_hpp */
