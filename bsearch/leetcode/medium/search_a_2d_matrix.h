//
//  search_a_2d_matrix.h
//  bsearch
//
//  Created by junl on 2019/9/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef search_a_2d_matrix_hpp
#define search_a_2d_matrix_hpp

#include <stdio.h>
#include <vector>
/*
 74.搜索二位矩阵
 编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：
 
 每行中的整数从左到右按升序排列。
 每行的第一个整数大于前一行的最后一个整数。
 示例 1:
 
 输入:
 matrix = [
 [1,   3,  5,  7],
 [10, 11, 16, 20],
 [23, 30, 34, 50]
 ]
 target = 3
 输出: true
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/search-a-2d-matrix
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    using namespace std;
#pragma mark - 常规解法
    //bad
    bool searchMatrix2(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        size_t row = matrix.size();
        size_t col = matrix[0].size();
        
        for (size_t i=row-1,j=0; i >=0 && j < col;){
            if (matrix[i][j] == target)
                return true;
            if (matrix[i][j] < target){
                j++;
            }else{
                i--;
            }
        }
        return false;
    }
    /*
     注意题目还有一个条件是每行的第一个整数大于前一行的最后一个整数。即整个数组实际上就是一个有序数组.
     我们可以利用二分搜索来完成查找
     */
    //good
    bool searchMatrix(vector<vector<int>>& matrix, int target){
        if (matrix.empty()) return false;
        size_t row = matrix.size();
        size_t col = matrix[0].size();
        
        size_t left=0;
        size_t right = row*col - 1;
        while(left<=right){
            size_t mid = left + ((right-left)>>1);
            int ct = matrix[mid/col][mid%col];
            if (ct == target){
                return true;
            }else if (ct < target){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        return false;
    }
}
#endif /* search_a_2d_matrix_hpp */
