//
//  match.h
//  string
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef match_hpp
#define match_hpp

#include <stdio.h>
/*
 剑指Offer（五十二）：正则表达式匹配
 
请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配
 
 https://www.nowcoder.com/practice/45327ae22b7b413ea21df13ee7d6429c?tpId=13&tqId=11205&tPage=3&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
#pragma mark - 有bug
    bool match(char* str, char* pattern)
    {
        int i=0;//指向sstr
        int j=0;//指向pattern
        char lastc = -1;
        while (pattern[j] != '\0' && str[i] != '\0') {
            char p = pattern[j];
            char s = str[i];
            if (p == '.') {
                j++;i++;
            }else if (p == '*'){
                if (j == 0) {
                    return false;
                }
                while (str[i] == lastc &&  str[i+1]!= pattern[j+1]) {
                    i++;
                }
                j++;
            }else{
                if (p == s) {
                    i++;
                    j++;
                }else{
                    if (pattern[j+1] != '*') {
                        return false;
                    }
                    j++;
                }
            }
            
            lastc = p;
        }
        return str[i] == '\0' && pattern[j] == '\0';
    }
    
    void test_match(){
        
        char *s1 = "ab*ac*a";
        char *s2 = "aaa";
        std::cout << "match starting........." << std::endl;
        std::cout << match(s2, s1) << std::endl;
    }
}
#endif /* match_hpp */
