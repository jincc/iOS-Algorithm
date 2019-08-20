//
//  main.cpp
//  string
//
//  Created by junlongj on 2019/7/22.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "matching.h"
#include "replaceSpace.h"
#include "Permutation.h"
#include "FirstNotRepeatingChar.h"
#include "ReverseSentence.h"
#include "StrToInt.h"
#include "match.h"
#include "longestCommonPrefix.h"
#include "strStr.h"
#include "addBinary.h"
#include "lengthOfLastWord.h"
#include "lengthOfLongestSubstring.h"
#include "longestPalindrome.h"
#include "zigzag_conversion.h"
#include "string_to_integer_atoi.h"
#include "integer_to_roman.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    string a = "Hello, World!\n";
    string b = "Wo";
    cout << "BF: " << BF_matching(a, b) << endl;
    cout << "RK: " << RK_matching(a, b) << endl;
    
    codinginterviews::test_replaceSpace();
    codinginterviews::test_Permutation();
    codinginterviews::test_FirstNotRepeatingChar();
    codinginterviews::test_ReverseSentence();
    codinginterviews::test_StrToInt();
    codinginterviews::test_match();
    leetcode::test_addBinary();
    leetcode::test_longestPalindrome();
    leetcode::test_convert();
    leetcode::test_myAtoi();
    return 0;
}
