//
//  main.cpp
//  array
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "base.h"
#include "DSArray.h"
#include "maxArea.h"
#include "removeDuplicates.h"
#include "plusOne.h"
#include "rotate.h"
#include "moveZeroes.h"
#include "Find.h"
#include "minNumberInRotateArray.h"
#include "reOrderArray.h"
#include "MoreThanHalfNum_Solution.h"
#include "PrintMinNumber.h"
#include "GetNumberOfK.h"
#include "FindNumsAppearOnce.h"
#include "twosum.h"
#include "removeElement.h"
#include "searchInsert.h"
#include "maxSubArray.h"
#include "merge.h"
#include "pascals_triangle.h"
#include "pascals_triangle_ii.h"
#include "best_time_to_buy_and_sell_stock.h"
#include "best_time_to_buy_and_sell_stock_ii.h"
#include "twoSum_ii.h"
#include "majorityElement.h"
#include "3sum.h"
#include "3SumClosest.h"
#include "combinationSum.h"
#include "ReOrder.h"
#include <vector>

#define max(x, y) ((x) > (y) ? (x) : (y))
int largestRectangleArea(int* heights, int heightsSize){
    /*
     矩形在位置i的面积:
     宽度：位置i左边第一个比heights[i]小的位置，位置i右边第一个比heights[i]小的位置之间的宽度
     高度: height[i]
     */
    if (heights == NULL || heightsSize <= 0)
        return 0;
    int l_minheights[heightsSize], r_minheights[heightsSize];
    l_minheights[0] = -1;
    r_minheights[heightsSize-1] = heightsSize;
    
    for(int i=1; i < heightsSize; i++){
        //选择左边第一个比heights[i]小的位置
        int val = i-1;
        while(val >= 0 && heights[val] >= heights[i]){
            val = l_minheights[val];
        }
        l_minheights[i] = val;
    }
    
    for(int i=heightsSize-2; i >= 0; i--){
        int val = i + 1;
        while(val < heightsSize && heights[val] >= heights[i]){
            val = r_minheights[val];
        }
        r_minheights[i] = val;
    }
    int result = 0;
    for(int i=0; i < heightsSize; i++){
        result = max(result, heights[i] * (r_minheights[i] - l_minheights[i] - 1));
    }
    return result;
}

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    testDSArray();
    
    cout << "盛最多水的容器 starting......." << endl;
    vector<int> heights = {1,8,6,2,5,4,8,3,7};
    vector<int> heights2 = {1,3,2,5,25,24,5};
    cout << maxArea(heights) << endl;
    vector<int> a{0,0,1,1,1,2,2,3,3,4};
    cout << "删除数组中重复项: starting......." << endl;
    int len = removeDuplicates(a);
    for (int i = 0; i < len; i++) {
        cout << a[i]  << ", ";
    }
    cout << "加一: starting......." << endl;
    vector<int> b1{1,2,3,4,5,6};
    vector<int> b2 = plusOne(b1);
    
    cout << "旋转数组 starting......" << endl;
    rotate3(b1,2);
    
    cout << "移动0 starting........." << endl;
    vector<int> c{1,0,1};
    moveZeroes3(c);
    
    codinginterviews::test_find();
    codinginterviews::test_minNumberInRotateArray();
    codinginterviews::test_reOrderArray();
    codinginterviews::test_MoreThanHalfNum_Solution();
    codinginterviews::test_PrintMinNumber();
    codinginterviews::test_GetNumberOfK();
    codinginterviews::test_ReOrder();
    int heights22[] = {2,1,5,6,2,3};
    int v = largestRectangleArea(heights22, 6);
    return 0;
}
