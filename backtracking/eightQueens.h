//
//  eightQueens.h
//  backtracking
//
//  Created by junl on 2019/7/25.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef eightQueens_hpp
#define eightQueens_hpp

#include <stdio.h>
#include <iostream>
/*
 8皇后问题，8*8的棋盘，希望放8个旗子，要求是每个旗子所在的行，列，对角线都不能有另一个旗子.
 
 Q,*,*,*,*,*,*,*,
 *,*,*,*,Q,*,*,*,
 *,*,*,*,*,*,*,Q,
 *,*,*,*,*,Q,*,*,
 *,*,Q,*,*,*,*,*,
 *,*,*,*,*,*,Q,*,
 *,Q,*,*,*,*,*,*,
 *,*,*,Q,*,*,*,*,
 
 */
bool isOK(int nums[],int n, int row ,int column){
    //依次查看前面的行是否满足：行不能放，列不能放，对角线不能放
    int leftup = column - 1;
    int rightup = column + 1;
    for (int i=row-1; i>=0; i--) {
        if (nums[i] == column)  return false;
        if (leftup >=0 &&  nums[i] == leftup) return false;
        if (rightup<=n && nums[i] == rightup) return false;
        leftup--;rightup++;
    }
    return true;
}

void eightQueens(int nums[], int n, int row){
    /*
     思路是回溯，一行一行的放，每次决策的时候，每列都可以放旗子，但是要满足相应的条件.
     */
    if (row == n){
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (nums[i] == j) {
                    std::cout << "Q" << ",";
                }else{
                    std::cout << "*" << ",";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------" << std::endl;
        return;
    }
    for (int c=0; c<n; c++) {//表示第几列
        if (isOK(nums, n, row, c)){
            nums[row]=c;//里面储存的是列,即第row行存的是第c列.
            eightQueens(nums, n, row+1);
        }
    }
}




#endif /* eightQueens_hpp */
