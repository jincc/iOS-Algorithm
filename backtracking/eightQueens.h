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

void backtrack(int *nums, int n, int level);
void printQueues(int *nums, int n);
bool isOk(int *nums, int row, int col, int n);
void eightQueue(int n){
    int nums[n];
    memset(nums, 0, sizeof(nums));
    
    backtrack(nums, n, 0);
};

void backtrack(int *nums, int n, int level){
    if (level == n){
        //print queues
        printQueues(nums, n);
        return;
    };
    
    for(int i=0; i < n;i++){
        if (isOk(nums, level, i, n)){
            nums[level] = i;
            backtrack(nums, n, level+1);
            nums[level] = 0;
        }
    }
}
bool isOk(int *nums, int row, int col, int n){
    int leftup = col - 1;
    int rightup = col + 1;
    for (int i = row-1; i>=0; i--) {
        if (nums[i] == col) return false;
        if (leftup>=0 && nums[i] == leftup) return false;
        if (rightup <= n-1 && nums[i] == rightup) return false;
        
        leftup--;rightup++;
    }
    return true;
}

void printQueues(int *nums, int n){
    for(int i=0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (nums[i] == j) {
                printf("1 ");
            }else{
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("-----------------\n");
    printf("-----------------\n");
}
#endif /* eightQueens_hpp */
