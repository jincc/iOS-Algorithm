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
#include "permutation_sequence.h"
#include "combinations.h"
#include "subsets.h"
#include "word_search.h"
#include "gray_code.h"
#include "subsets_ii.h"
#include "restore_ip_addresses.h"
bool isFindNum(int num){
    int sum = 0;
    for (int i=1; i<num; i++) {
        if (num % i == 0) {
            sum+=i;
        }
    }
    if (sum == num) {
        return true;
    }
    return false;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
//    for (int i=2; i<=1000; i++) {
//        if (isFindNum(i)) {
//            cout << i << endl;
//        }
//    }
//    return 1;
    
    
    eightQueue(4);
    
    int KNAPSACK[5]={2,2,4,6,3};
    cout << "0-1背包问题" << endl;
    cout << backpack01(KNAPSACK, 5, 9) << endl;
    
    leetcode::test_letterCombinations();
    leetcode::test_combinationSumII();
    //字符串匹配
    cout << "字符串匹配 :"<< isMatch("acddf","ac*") << endl;
    
    leetcode::test_permutation_sequence();
    leetcode::test_combinations();
    leetcode::test_word_search();
    leetcode::test_gray_code();
    
    string s ="123456";
    cout << s.substr(0,2) << endl;
    s.erase(0,1);
    return 0;
}

