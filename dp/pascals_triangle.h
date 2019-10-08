//
//  pascals_triangle.h
//  dp
//
//  Created by junl on 2019/10/8.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef pascals_triangle_hpp
#define pascals_triangle_hpp

#include <stdio.h>
#include <vector>
/*
 
 如下是杨辉三角的变种，每个位置的数字可以随便填写，经过每个数字只能到达下面一层相邻的两个数字。
 假设我们从第一层开始，求到达最底层所经过的所有数字之和最小.
            5
           / \
          7   6
         / \ / \
        2   4   7
       / \ / \ / \
      4   9   6   1
 
 */
using std::vector;
using std::min;
typedef vector<vector<int>> Matrix;
class pascals_triangle{
public:
    int solve(Matrix &matrix){
        return backstraking(matrix);
    }
    int backstraking(Matrix &matrix){
        if (matrix.empty()) {
            return 0;
        }
        backstraking(matrix, 1, matrix[0][0], 0);
        return result;
    }
    
private:
    int result = INT_MAX;
    void backstraking(Matrix &matrix, int level, int ctValue, int lastIndex){
        if (level == matrix.size()) {
            result = min(ctValue, result);
            return;
        }
        int leftChild = lastIndex;
        int rightChild = lastIndex+1;
        backstraking(matrix, level+1, ctValue + matrix[level][leftChild], leftChild);
        backstraking(matrix, level+1, ctValue + matrix[level][rightChild], rightChild);
    }
};


class pascals_triangle_dp{
public:
    int solve(Matrix& matrix){
        if (matrix.empty()) return 0;
        int st[matrix.size()][matrix.size()];
        memset(st, 0, sizeof(st));
        
        st[0][0] = matrix[0][0];
        for (int i=1; i<matrix.size(); i++) {
            //保存所有路径的路径和
            for (int j=0; j<matrix[i].size(); j++) {
                if (j == 0) {
                    //左边路线
                    st[i][j] = st[i-1][j] + matrix[i][j];
                }else if ( j == matrix[i].size()-1){
                    //右边路线
                    st[i][j] = st[i-1][j-1] + matrix[i][j];
                }else{
                    //中间路径，取两台路线的最小值
                    st[i][j] = min(st[i-1][j-1], st[i-1][j]) + matrix[i][j];
                }
            }
        }
        
        int result = INT_MAX;
        int lastRow = matrix.size()-1;
        for (int i=0; i<matrix[lastRow].size(); i++) {
            if (result > st[lastRow][i]) {
                result = st[lastRow][i];
            }
        }
        return result;
    };
};

void test_pascals_triangle(){
    vector<vector<int>> matrix;
    matrix.push_back({5});
    matrix.push_back({7,8});
    matrix.push_back({2,3,4});
    matrix.push_back({4,9,6,1});
    class pascals_triangle so;
    class pascals_triangle_dp so_dp;
    std::cout << "--------杨辉三角变种---------" << std::endl;
    std::cout << so.solve(matrix) << std::endl;
    std::cout << so_dp.solve(matrix) << std::endl;
}

#endif /* pascals_triangle_hpp */
