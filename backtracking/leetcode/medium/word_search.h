//
//  word_search.h
//  backtracking
//
//  Created by junl on 2019/9/25.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef word_search_hpp
#define word_search_hpp

#include <stdio.h>
/*
 79.单词搜索
 给定一个二维网格和一个单词，找出该单词是否存在于网格中。
 
 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
 
 示例:
 
 board =
 [
 ['A','B','C','E'],
 ['S','F','C','S'],
 ['A','D','E','E']
 ]
 
 给定 word = "ABCCED", 返回 true.
 给定 word = "SEE", 返回 true.
 给定 word = "ABCB", 返回 false.
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/word-search
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */

namespace leetcode {
    class Solution79 {
    public:
        bool exist(vector<vector<char>>& board, string word) {
            if (board.empty() || word.empty()) return false;
            int st[board.size()*board[0].size()];
            std::memset(st, false ,sizeof(st));
            
            for (int i=0;i<board.size();i++){
                for(int j=0;j<board[0].size();j++){
                    if (exist(board, word, 0, i,j,st))
                        return true;
                }
            }
            return false;
        }
        
        
        bool exist(vector<vector<char>>& board, string word, size_t ctindex, size_t i, size_t j, int st[]){
            if (ctindex == word.size()){
                return true;
            }
            if (i < 0 || i >= board.size()){
                return false;
            }
            if (j < 0 || j>= board[0].size()){
                return false;
            }
            if (st[i*board[0].size()+j] == true){
                return false;
            }
            if (board[i][j] != word[ctindex]){
                return false;
            }
            st[i*board[0].size()+j] = true;
            bool st1 = exist(board, word, ctindex+1, i, j + 1,st) ||
            exist(board, word, ctindex+1, i, j - 1,st) ||
            exist(board, word, ctindex+1, i + 1, j,st) ||
            exist(board, word, ctindex+1, i - 1, j ,st);
            st[i*board[0].size()+j] = false;
            return st1;
        }
    };
    
    void test_word_search(){
        vector<vector<char>> a{{'a','b'},{'c','d'}};
        string s= "acdb";
        Solution79 so;
        bool st = so.exist(a, s);
        cout << "test_word_search starting...... " << endl << st << endl;
    }
}
#endif /* word_search_hpp */
