//
//  FirstNotRepeatingChar.h
//  string
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef FirstNotRepeatingChar_hpp
#define FirstNotRepeatingChar_hpp

#include <stdio.h>
#include <string>
#include <map>
/*
 剑指Offer（三十四）：第一个只出现一次的字符
 
 在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）.
https://www.nowcoder.com/practice/1c82e8cf713b4bbeb2a5b31cf5b0417c?tpId=13&tqId=11187&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    int FirstNotRepeatingChar(std::string &str) {
        int length = str.size();
        if(length == 0){
            return -1;
        }
        std::map<char, int> item;
        for(int i = 0; i < length; i++){
            item[str[i]]++;
        }
        for(int i = 0; i < length; i++){
            if(item[str[i]] == 1){
                return i;
            }
        }
        return -1;
    }
    
    void test_FirstNotRepeatingChar(){
        std::cout << "FirstNotRepeatingChar starting......" << std::endl;
        std::string s{"google"};
        std::cout << FirstNotRepeatingChar(s) << std::endl;
    }
}

#endif /* FirstNotRepeatingChar_hpp */
