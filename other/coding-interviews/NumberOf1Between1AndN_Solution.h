//
//  NumberOf1Between1AndN_Solution.h
//  other
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef NumberOf1Between1AndN_Solution_hpp
#define NumberOf1Between1AndN_Solution_hpp

#include <stdio.h>
#include <string>
#include <math.h>
/*
 剑指Offer（三十一）：整数中1出现的次数（从1到n整数中1出现的次数）
 求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。
https://www.nowcoder.com/practice/bd7f978302044eee894445e244c7eee6?tpId=13&tqId=11184&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
int NumberOfStr(const char *str);
int countDigitOne(int n){
    if (n <= 0) return 0;

    char s[BUFSIZ];
    sprintf(s, "%d", n);
    return NumberOfStr(s);
}

int NumberOfStr(const char *str){
    //21345
    if (str == NULL || *str < '0' || *str > '9'||  *str == '\0')
        return 0;
    
    int highPosition = str[0] - '0';
    size_t len = strlen(str);
    if (len == 1 && highPosition == 0)
        return 0;
    if (len == 1 && highPosition > 0){
        return 1;
    }
    int highNumber, tailNumber, numRecursive;
    if (highPosition == 1){
        highNumber = atoi(str+1) + 1;
    }else if(highPosition > 1){
        highNumber = pow(10, len-1);
    }else{
        highNumber = 0;
    }
    tailNumber = highPosition * (len - 1) * pow(10, len-2);
    numRecursive = NumberOfStr(str+1);
    return highNumber + tailNumber + numRecursive;
}

void test_countDigitOne(){
    int n = 20000;
    printf("test_countDigitOne: %d\n",countDigitOne(n));
}
}
#endif /* NumberOf1Between1AndN_Solution_hpp */
