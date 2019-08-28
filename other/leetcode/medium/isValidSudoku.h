//
//  isValidSudoku.h
//  other
//
//  Created by junlongj on 2019/8/27.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef isValidSudoku_hpp
#define isValidSudoku_hpp

#include <stdio.h>
#include <vector>
#include <set>
/*
 36。有效的数独
 判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
 
 数字 1-9 在每一行只能出现一次。
 数字 1-9 在每一列只能出现一次。
 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/valid-sudoku
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    using namespace  std;
    
    bool isValidSudoku(vector<vector<char>>& board) {
        /*
         思路：isValidSudoku2 的解法没有利用到数字只有1-9这一点。时间复杂度为n^2.
         
         思路是，根据某个数，然后判断它是否存在于某一行或某一列或某个格子里面.
        
         那么对于每一行来说，状态数组为st_row[row][number];
         对于每一列来说，状态数组为st_col[col][number];
         对于每个矩形内部，我们从左到右从上到下，将每个3*3的格子编号顺序，那么对于的关系就为st_area[(row/3)*3+col/3][number]
         */
        
        const int len=9;
        bool st_row[len][len] = {false};
        bool st_col[len][len] = {false};
        bool st_area[len][len] = {false};
        for (int i = 0 ;i < len ;i ++){
            for (int j=0;j<len;j++){
                if (board[i][j] == '.')
                    continue;
                int idx = board[i][j] - '0' - 1; //1-9
                if (st_row[i][idx] == true) {
                    return false;
                }//第x行的idx这个数字是否出现过
                st_row[i][idx] = true;
                
                if (st_col[j][idx] == true) {
                    //第x列的idx这个数字是否出现过
                    return false;
                }
                st_col[j][idx] = true;
                
                int area = (i/3)*3 + j/3;
                if (st_area[area][idx] == true){
                    return false;
                }
                st_area[area][idx] = true;
            }
        }
        
        return true;
    }
    
    
    //bad
    bool isValidSudoku2(vector<vector<char>>& board) {
        //先判断行
        //在判断列
        //在判断3*3宫格
        set<char> s;
        set<char> s2;
        set<char> s3;
        for(int i=0;i<9;i++){//行
            s.clear();
            s2.clear();
            for(int j=0;j<9;j++){ //列
                if (board[i][j] != '.' && s.count(board[i][j]) != 0){
                    return false;
                }
                s.insert(board[i][j]);
                
                if (board[j][i] != '.' && s2.count(board[j][i]) != 0){
                    return false;
                }
                s2.insert(board[j][i]);
                
                if (i % 3 == 2 && j % 3 == 2){
                    //小格子
                    s3.clear();
                    for(int k=i;k>=i-2;k--){
                        for (int m=j;m>=j-2;m--){
                            if (board[k][m] != '.' && s3.count(board[k][m]) != 0){
                                return false;
                            }
                            s3.insert(board[k][m]);
                        }
                    }
                }
            }
        }
        return true;
    }
    
    void test_isValidSudoku(){
        vector<vector<char>> a ;
        a= {{'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}};
        
        
            std::cout << 'test_isValidSudoku starting.......' << std::endl;
            std::cout << isValidSudoku(a) << std::endl;
    }
}
#endif /* isValidSudoku_hpp */
