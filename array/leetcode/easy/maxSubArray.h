//
//  maxSubArray.h
//  array
//
//  Created by junlongj on 2019/8/7.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef maxSubArray_hpp
#define maxSubArray_hpp

#include <stdio.h>
#include <vector>
/*
 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 
 示例:
 
 输入: [-2,1,-3,4,-1,2,1,-5,4],
 输出: 6
 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/maximum-subarray
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
#pragma mark - o(2n)
    /*
     思路: DP[0......i]  dp[i]里面存储的是，之前元素到i的连续数组的最大值。
     这样我们可以通过dp[i-1]推导出dp[i]的状态.
     如果 dp[i-1] > 0, dp[i] = dp[i-1] + nums[i];
     否则 : dp[i] = nums[i];
     */
    int maxSubArray(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        int dp[nums.size()];//dp里面存储的是到数组i位置以前，最大的子序列和.
        dp[0]=nums[0];
        for (int i=1;i<nums.size();i++){
            if (dp[i-1] > 0){
                dp[i] = dp[i-1] + nums[i];
            }else{
                dp[i] = nums[i];
            }
        }
        //这样dp数组里面存储的都是到当前下标(包括下标)位置之前的最大值.求最大值.
        int max = dp[0];
        for (int i=0;i<nums.size();i++){
            max = std::max(max,dp[i]);
        }
        return max;
    }
    
#pragma mark - o(n)
    int maxSubArray2(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        int dp[nums.size()];//dp里面存储的是到数组i位置以前，最大的子序列和.
        dp[0]=nums[0];
        int max = dp[0];
        for (int i=1;i<nums.size();i++){
            if (dp[i-1] > 0){
                dp[i] = dp[i-1] + nums[i];
            }else{
                dp[i] = nums[i];
            }
            max = std::max(max,dp[i]);
        }
        return max;
    }
}
#endif /* maxSubArray_hpp */
