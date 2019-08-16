//
//  printMatrix.h
//  other
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef printMatrix_hpp
#define printMatrix_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（十九）：顺时针打印矩阵
 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
https://www.nowcoder.com/practice/9b4c81a02cd34f76be2659fa0d54342a?tpId=13&tqId=11172&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    std::vector<int> printMatrix(std::vector<std::vector<int> > matrix) {
        std::vector<int> values;
        int uprow=0;
        int bottomrow=matrix.size()-1;
        int leftcol =0;
        int rightcol = matrix[0].size()-1;
        int count = matrix.size() * matrix[0].size();
        while (uprow <= bottomrow && leftcol <= rightcol) {
            //从左到右
            for (int i=leftcol; i<=rightcol; i++) {
                values.push_back(matrix[uprow][i]);
            }

            //从上到下
            for (int i=uprow+1; i<=bottomrow; i++) {
                values.push_back(matrix[i][rightcol]);
            }
            //从右到左
            if (uprow != bottomrow) {
                for (int i=rightcol-1; i>=leftcol; i--) {
                    values.push_back(matrix[bottomrow][i]);
                }
            }
            //从下到上
            if (leftcol != rightcol) {
                for (int i=bottomrow-1; i>uprow; i--) {
                    values.push_back(matrix[i][leftcol]);
                }
            }
            uprow++;rightcol--; bottomrow--; leftcol++;
        }
        return values;
        
        int rows = matrix.size();            //行数
        int cols = matrix[0].size();        //列数
        std::vector<int> result;
        
        if(rows == 0 && cols == 0){
            return result;
        }
        int left = 0, right = cols - 1, top = 0, bottom = rows - 1;
        
        while(left <= right && top <= bottom){
            //从左到右
            for(int i = left; i <= right; ++i){
                result.push_back(matrix[top][i]);
            }
            //从上到下
            for(int i = top + 1; i <= bottom; ++i){
                result.push_back(matrix[i][right]);
            }
            //从右到左
            if(top != bottom){
                for(int i = right - 1; i >= left; --i){
                    result.push_back(matrix[bottom][i]);
                }
            }
            //从下到上
            if(left != right){
                for(int i = bottom - 1; i > top; --i){
                    result.push_back(matrix[i][left]);
                }
            }
            left++, top++, right--, bottom--;
        }
        return result;
    }
    
    void test_printMatrix(){
        std::vector<std::vector<int> > matrix{{1,2,3,4},{5,6,7,8},{9,10,11,12}};
        
        std::vector<int> values = printMatrix(matrix);
        values;
    }
}

#endif /* printMatrix_hpp */
