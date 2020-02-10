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
    bool IncrementNumber(char * number){
        //每次把最后一位加一
        int len = strlen(number);
        int flag = 0;//是否产生了进位
        for (int i=len-1; i>=0; i--) {
            int sum = number[i] - '0' + flag;
            if (i == len-1)
                sum++;
            if (sum >= 10){
                //产生了进位
                if (i == 0){
                    return false;//越界，退出
                }
                flag = 1;
                sum -= 10;
                number[i] = '0' + sum;
            }else{
                //没有产生进位
                number[i] = '0' + sum;
                break;
            }
        }
        return true;
    }
    void PrintNumber(char *number){
        //跳过前面的0打印
        int len = strlen(number);
        bool begin0 = true;
        for (int i=0; i<len; i++) {
            if (begin0 && number[i] != '0')
                begin0 = false;
            if (!begin0) {
                printf("%c", number[i]);
            }
        }
        printf("\n");
    }
    void Print1ToMaxOfNDigits(int n){
        if (n <= 0) return;
        
        char *buf = (char *)malloc(n+1);
        memset(buf, '0', n);
        buf[n] = '\0';
    
        while (IncrementNumber(buf)) {
            PrintNumber(buf);
        }
        delete [] buf;
    }
    
    
}

#endif /* Print1ToMaxOfNDigits_hpp */
