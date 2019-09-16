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
#include "letter_combinations_of_a_phone_number.h"
#include "Pattern.h"
#include "combinationSumII.h"
#include "permutationsii.h"
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
    
    leetcode::test_letterCombinations();
    leetcode::test_combinationSumII();
    //字符串匹配
    Pattern pattern = Pattern("ac??f");
    cout << "是否能匹配: " << pattern.match("acddf") << endl;
    return 0;
}

