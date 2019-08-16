//
//  GetNumberOfK.h
//  array
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef GetNumberOfK_hpp
#define GetNumberOfK_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（三十七）：数字在排序数组中出现的次数
 统计一个数字在排序数组中出现的次数。
https://www.nowcoder.com/practice/70610bf967994b22bb1c26f9ae901fa2?tpId=13&tqId=11190&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */
namespace codinginterviews {
    /*
     先找出第一个出现k的位置，然后在统计个数
     */
    int GetNumberOfK(std::vector<int> data ,int k) {
        int count = 0;
        int left =0;
        int right = data.size()-1;
        int minKindex = 0;
        while (left <= right) {
            int mid = left + (right- left)/2;
            if (data[mid] == k) {
                //找到第一个k
                if (mid != 0 && data[mid-1] != k) {
                    minKindex = mid;
                    break;
                }
                right = mid-1;
            }else if (data[mid] < k){
                left = mid+1;
            }else{
                right = mid-1;
            }
        }
        while (minKindex < data.size()) {
            if (data[minKindex++] == k) {
                count++;
            }
        }
        return count;
    }
    void test_GetNumberOfK(){
        std::cout << "GetNumberOfK: starting....... " << std::endl;
        std::vector<int> a{1,2,3,3,3,4,4};
        std::cout << GetNumberOfK(a, 5) << std::endl;
    }
}

#endif /* GetNumberOfK_hpp */
