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
#include <vector>
#include <stdlib.h>
#include <map>
using namespace std;
int compare(const void *num1,const  void *num2);
bool isStraight(int* nums, int numsSize){
    if (nums == NULL || numsSize != 5)
        return false;
    qsort(nums, numsSize, sizeof(int), compare);
    int i, zerocnt, dif;
    zerocnt = 0;
    for(i=0; i < numsSize;i++){
        if (nums[i] != 0){
            break;
        }
        zerocnt++;
    }
    dif = 0;
    for(; i < numsSize-1; i++){
        if (nums[i+1] == nums[i])
            return false;
        dif += nums[i+1] - nums[i] - 1;
    }
    return zerocnt >= dif;
}

int compare(const void *num1,const  void *num2){
    int n1 = *(int *)num1;
    int n2 = *(int *)num2;
    return n1 > n2;
}
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
    codinginterviews::test_countDigitOne();
    
//    int nums[] = {9,1,7,9,7,9,7};
//    printf("singleNumber: %d\n",singleNumber(nums, 7));
    int nums[] = {1, 2, 5, 0, 0};
    isStraight(nums, 5);
    
    map<int, int> m;
    cout << m[0] << endl;
    return 0;
}
