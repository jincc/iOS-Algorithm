//
//  ReOrder.h
//  array
//
//  Created by junl on 2020/1/4.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef ReOrder_hpp
#define ReOrder_hpp

#include <stdio.h>
#include <vector>
/*
 面试题14. 调整数组顺序使得奇数位于偶数前面
 */

namespace codinginterviews {
    void ReOrder(std::vector<int> &nums){
        if (nums.empty())
            return;
        
        int pos1 = 0;
        int pos2 = nums.size() - 1;
        if (pos1 == pos2)
            return;
        while (pos1 < pos2) {
            //寻找前面第一个偶数
            while (nums[pos1] & 0x1) {
                pos1++;
            }
            if (pos1 == nums.size()+1)
                break;
            while (!(nums[pos2] & 0x1)) {
                pos2--;
            }
            if (pos2 == -1)
                break;
            std::swap(nums[pos1], nums[pos2]);
            pos1++;pos2--;
        }
    }
    
    void test_ReOrder(){
        std::cout << "调整数组顺序使得奇数位于偶数前面" << std::endl;
        std::vector<int> nums{2,4,6,8};
        ReOrder(nums);
        for(auto &x : nums){
            std::cout << x << std::endl;
        }
    }
}
#endif /* ReOrder_hpp */
