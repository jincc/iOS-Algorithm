//
//  twoSum.h
//  array
//
//  Created by junlongj on 2019/8/6.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef twoSum_hpp
#define twoSum_hpp

#include <stdio.h>
#include <vector>
namespace leetcode {
    /*
     1.两数之和
     
     思路:通过集合来保存之前遍历过的元素，这样每次查找的时候先判断target-当前值的元素在不在hash table里面，就可以计算出结果了.
     */
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::map<int,int> mm;//key为当前值，value为下标
        std::vector<int> result;
        for (int i=0;i<nums.size();i++){
            if(mm.find(target-nums[i]) == mm.end()){
                mm[nums[i]]=i;
            }else{
                result.push_back(mm[target-nums[i]]);
                result.push_back(i);
            }
        }
        return result;
    }
}

#endif /* twoSum_hpp */
