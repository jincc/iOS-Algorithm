//
//  matrix_move.h
//  dp
//
//  Created by junl on 2019/10/9.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef matrix_move_hpp
#define matrix_move_hpp

#include <stdio.h>
#include <vector>
/*
 和前面的杨辉三角变种有点类似:
 问题是有一个n*n的矩阵，矩阵存储的都是正整数，旗子最开始位于左上角，终止位置在右下角。中间经过的数字是它们的路径和，求最短的路径和.
 
 1,3,5,9
 2,1,3,4
 5,2,6,7
 6,8,4,3
 */
using namespace std;
class matrix_move {
public:
    int solve(vector<vector<int>> &matrix){
        if (matrix.empty() || matrix.size() != matrix[0].size()) {
            return 0;
        }
        solve(matrix, 0, 0, matrix[0][0]);
        return result;
    }
private:
    int result = INT_MAX;
    
    void solve(vector<vector<int>> &matrix, int row,int col ,int pathLen){
        size_t N = matrix.size()-1;
        if (row == N && col == N) {
            result = min(result, pathLen);
            return;
        }
        if (row < N) {
            solve(matrix, row+1, col, pathLen+matrix[row+1][col]);
        }
        if (col < N) {
            solve(matrix, row, col+1, pathLen+matrix[row][col+1]);
        }
    }
};


class matrix_move_dp {
public:
    /*
     思路:
     假设矩阵大小为N*N，那么从左上角移动到右下角一共要移动2*(N-1)次.
     每一次要么向下移动，要么向右移动，每次移动之后，状态(路径和)都会发生变化。该问题符合动态规划的“一个模型三个条件”
     
     怎么定义状态呢?
     -- int min_path[i][j] 里面保存的是从左上角到matrix[i][j]的最小路径和
     状态转移方程是什么?
     -- 走法只有两种，那么到达matrix[i][j]的位置，只有可能是min_path[i-1][j]或者min_path[i][j-1]中的一条.
     -- min_path[i][j] = min(min_path[i-1][j], min_path[i][j-1]) + matrix[i][j];
     */
    int solve(vector<vector<int>> &matrix){
        if (matrix.empty()) {
            return 0;
        }
        size_t N = matrix.size();
        int min_path[N][N];
        memset(min_path, 0, sizeof(min_path));
        
        //设置初始状态
        int sum=0;
        int i;
        for (i=0; i<N; i++) {//第一排的初始状态
            sum+=matrix[0][i];
            min_path[0][i]=sum;
        }
        
        sum=0;
        for (i=0; i<N; i++) { //第一列的初始状态
            sum+=matrix[i][0];
            min_path[i][0]=sum;
        }
        
        //通过初始状态动态向前推导,按照一行行的向下推导
        for (i=1; i<N; i++) {
            for (int j=1; j<N; j++) {
                min_path[i][j] = min(min_path[i-1][j], min_path[i][j-1]) + matrix[i][j];
            }
        }
        return min_path[N-1][N-1];
    };
};

void test_matrix_move(){
    vector<vector<int>> matrix;
    matrix.push_back({1,3,5,9});
    matrix.push_back({2,1,3,4});
    matrix.push_back({5,2,6,7});
    matrix.push_back({6,8,4,3});
    class matrix_move so;
    cout << "----------矩阵移动-----------" << endl;
    cout << so.solve(matrix) << endl;
    
    class matrix_move_dp so_dp;
    cout << so_dp.solve(matrix) << endl;
    
}


#endif /* matrix_move_hpp */
