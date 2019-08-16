//
//  pascals_triangle_ii.h
//  array
//
//  Created by junlongj on 2019/8/8.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef pascals_triangle_ii_hpp
#define pascals_triangle_ii_hpp

#include <stdio.h>
#include <vector>
/*
 119. 杨辉三角 II
 给定一个非负索引 k，其中 k ≤ 33，返回杨辉三角的第 k 行。
 https://leetcode-cn.com/problems/pascals-triangle-ii/
 
 你可以优化你的算法到 O(k) 空间复杂度吗？
 */

namespace leetcode {
    /*
     思路：通过上一行内容推算出下行的内容,比如:
     1,1
  1 , 2  + 1
     
     1,2,1    如果j指向这一行的话
  1,  3 3   +1  结果：result[j]=result[j]+result[j-1];
     */
    std::vector<int> getRow(int rowIndex) {
        if (rowIndex<0) return {};
        std::vector<int> result;
        for (int i=0;i<=rowIndex;i++){
            if (i==0) {
                result.push_back(1);
            }else{
                for(int j=i-1;j-1>=0;j--){
                    result[j]=result[j]+result[j-1];
                }
                result.push_back(1);
            }
        }
        return result;
    }
}

#endif /* pascals_triangle_ii_hpp */
