//
//  main.cpp
//  other
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "NumberOf1.h"
#include "Power.h"
#include "printMatrix.h"
#include "NumberOf1Between1AndN_Solution.h"
#include "GetLeastNumbers_Solution.h"
#include "maxInWindows.h"
#include "IsContinuous.h"
#include "FindNumbersWithSum.h"
#include "FindContinuousSequence.h"
#include "GetUglyNumber_Solution.h"
#include "reverse_integer.h"
#include "palindrome_number.h"
#include "romanToInt.h"
#include "next_permutation.h"
#include "isValidSudoku.h"
#include "Print1ToMaxOfNDigits.h"
#include "IsContinuous2.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    codinginterviews::test_NumberOf1();
    codinginterviews::test_Power();
    codinginterviews::test_printMatrix();
    codinginterviews::test_GetLeastNumbers_Solution();
//    codinginterviews::test_NumberOf1Between1AndN_Solution();
    
    codinginterviews::test_maxInWindows();
    codinginterviews::test_IsContinuous();
    codinginterviews::test_FindNumbersWithSum();
    codinginterviews::test_FindContinuousSequence();
    codinginterviews::test_GetUglyNumber_Solution();
    
    leetcode::test_isValidSudoku();
    codinginterviews::printToMaxOfNDigits(3);
    codinginterviews::test_IsContinuous2();
    return 0;
}
