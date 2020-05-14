//
//  Print1ToMaxOfNDigits.h
//  other
//
//  Created by junl on 2020/1/3.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef Print1ToMaxOfNDigits_hpp
#define Print1ToMaxOfNDigits_hpp

#include <stdio.h>
/*
 输入数字n，按顺序打印出从1到最大的n位十进制数.比如输入3，则打印出1，2，3一直到最大的3位数999.
 */

namespace codinginterviews {
    /*
     这题最大的陷阱就在于没有限制n的值，即有可能超出了int/long/longlong的范围。
     所以我们采用字符串的方式来解决.
     */
    int increment1(char nums[], int len);
    void printnumber(char nums[], int len);
    void printToMaxOfNDigits(int n){
        if (n <= 0) return;
        
        char nums[n+1];
        memset(nums, '0', n+1);
        nums[n] = '\0';
        
        while (increment1(nums, n)) {
            printnumber(nums, n);
        }
    }
    int increment1(char nums[], int len){
        int overflow = 0, sign;
        int i, num;
        
        sign = 1;
        for(i = len -1; i>=0 ;i--){
            num = nums[i] - '0';
            num += sign;
            if (num == 10){
                if (i == 0){
                    overflow = 1;
                    break;
                }
                sign = 1;
                nums[i] = '0';
            }else{
                sign = 0;
                nums[i] = num + '0';
                break;
            }
        }
        return !overflow;
    }
    void printnumber(char nums[], int len){
        char *p = nums;
        while(*p == '0')
            p++;
        if (*p == '\0') return;
        printf("%s\n", p);
    }

    void recursivePrintToMaxOfNDigits(char nums[], int len, int level);
    void printToMaxOfNDigits2(int n){
        if (n <= 0) return;
        
        char nums[n+1];
        memset(nums, '0', n+1);
        nums[n] = '\0';
        recursivePrintToMaxOfNDigits(nums, n, 0);
    }
    void recursivePrintToMaxOfNDigits(char nums[], int len, int level){
        if (level == len) return;
        for (int i=0; i<10; i++) {
            nums[level] = '0' + i;
            recursivePrintToMaxOfNDigits(nums, len, level+1);
            printnumber(nums, len);
        }
    }
}

#endif /* Print1ToMaxOfNDigits_hpp */
