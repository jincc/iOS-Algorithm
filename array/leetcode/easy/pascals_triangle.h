//
//  pascals_triangle.h
//  array
//
//  Created by junlongj on 2019/8/8.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef pascals_triangle_hpp
#define pascals_triangle_hpp

#include <stdio.h>
#include <vector>
/*
 118. 杨辉三角
 在杨辉三角中，每个数是它左上方和右上方的数的和。
 
 示例:
 
 输入: 5
 输出:
 [
        [1],
       [1,1],
      [1,2,1],
     [1,3,3,1],
    [1,4,6,4,1]
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/pascals-triangle
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
https://leetcode-cn.com/problems/pascals-triangle/
 */

namespace leetcode {
    /*
     思路: 下一行的内容是由上一行产生的，所以内存循环遍历上一次的vec就行了
     */
    std::vector<std::vector<int>> generate(int numRows) {
        if (numRows == 0) return {};
        std::vector<std::vector<int>> result;
        std::vector<int> lastVec;
        result.push_back({1});
        for(int i=1;i<numRows;i++){
            std::vector<int> vec;
            vec.push_back(1);
            if (lastVec.size()>=2){
                for (int j=0; j+1<lastVec.size();j++){
                    vec.push_back(lastVec[j]+lastVec[j+1]);
                }
            }
            vec.push_back(1);
            lastVec = vec;
            result.push_back(vec);
        }
        return result;
    }
}
#endif /* pascals_triangle_hpp */
