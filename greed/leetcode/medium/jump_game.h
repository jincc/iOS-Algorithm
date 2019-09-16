//
//  jump_game.h
//  greed
//
//  Created by junl on 2019/9/10.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef jump_game_hpp
#define jump_game_hpp

#include <stdio.h>
#include <vector>
/*
 55. 跳跃游戏
 给定一个非负整数数组，你最初位于数组的第一个位置。
 
 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 
 判断你是否能够到达最后一个位置。
 
 示例 1:
 
 输入: [2,3,1,1,4]
 输出: true
 解释: 从位置 0 到 1 跳 1 步, 然后跳 3 步到达最后一个位置。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/jump-game
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    bool canJump(vector<int>& nums) {
        //贪心思想，始终选择当前跳和下一跳加起来最远的那个
        if (nums.empty()) return false;
        int destination = nums.size()-1;
        for (int i=0;i<nums.size();){
            
            int maxstep=0;
            int nexstep=0;
            if (nums[i] == 0) {
                return i == destination;
            }
            //寻找从当前位置出发，跳的最远的那个位置.
            for(int j=1;j <= nums[i];j++){
                if (i + j >= destination)
                    return true;
                if (maxstep < j+nums[i+j]){
                    maxstep =j+nums[i+j];
                    nexstep = j;
                }
            }
            i += nexstep;
        }
        return false;
    }
}
#endif /* jump_game_hpp */
