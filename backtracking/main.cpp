//
//  main.cpp
//  backtracking
//
//  Created by junl on 2019/7/25.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "eightQueens.h"
#include "knapsack.h"
#include "hasPath.h"
#include <mach/exception_types.h>
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    int nums[8];
    memset(nums, -1, 8*sizeof(int));
    eightQueens(nums, 8, 0);
    
    static const int KNAPSACK[5]={2,2,4,6,3};
    cout << "0-1背包问题" << endl;
    cout << knapsack(KNAPSACK, 5, 9) << endl;
    return 0;
}

