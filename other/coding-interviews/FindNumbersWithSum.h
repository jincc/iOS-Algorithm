//
//  FindNumbersWithSum.h
//  other
//
//  Created by junl on 2019/8/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef FindNumbersWithSum_hpp
#define FindNumbersWithSum_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（四十二）：和为S的两个数字
 题目描述
 输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。
 输出描述:
 对应每个测试案例，输出两个数，小的先输出。
 
 https://www.nowcoder.com/practice/390da4f7a00f44bea7c2f3d19491311b?tpId=13&tqId=11195&tPage=3&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    std::vector<int> FindNumbersWithSum(std::vector<int> array,int sum) {
        if (array.empty()) return {};
        int i=0;
        int j=array.size()-1;
        std::vector<int> result;
        while (i < j) {
            int ctv = array[i] + array[j];
            if (ctv == sum) {
                if (result.empty()) {
                    result.push_back(array[i]);
                    result.push_back(array[j]);
                }else{
                    if (array[i] * array[j] < result[0] * result[1]) {
                        result[0] = array[i];
                        result[1] = array[j];
                    }
                }
                i++;
                j--;
            }else if(ctv < sum){
                i++;
            }else{
                j--;
            }
        }
        return result;
    }
    
    void test_FindNumbersWithSum(){
        std::cout << "FindNumbersWithSum starting........" << std::endl;
        std::vector<int> a{1,2,3,4,5,7,8};
        std::vector<int> result = FindNumbersWithSum(a, 7);
        if (!result.empty()) {
            std::cout << result[0] << ", " << result[1] << std::endl;
        }
    }
}
#endif /* FindNumbersWithSum_hpp */
