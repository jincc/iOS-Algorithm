//
//  Pattern.h
//  backtracking
//
//  Created by junl on 2019/9/12.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef Pattern_hpp
#define Pattern_hpp

#include <stdio.h>
#include <string>
/*
 正则表达式匹配，假设通配符只有两个，一个是*，一个是?
 * 代表可以匹配任意多个(>=0)任意字符.
 ? 代表匹配另个或一个任意字符
 
 对于字符串的匹配，对于字符来说有两种情况：
    1.如果是非通配符情况下，必须完全匹配
    2.如果是通配字符，就有很多种选择了，就拿*来说，它可以匹配任意多个任意字符，这里我们利用回溯的思想穷举出所有的情况.
 
 */
class Pattern {
public:
    Pattern(const std::string &p):pattern(p){}
    //原文本 abcdefg  模式串ac*f
    bool match(std::string txt){
        isMatch = false;
        match(txt, 0, 0);
        return isMatch;
    }
private:
    std::string pattern;
    bool isMatch = false;
    void match(std::string &txt,size_t pi, size_t tj){
        //终止条件
        if (isMatch) 
            return;
        
        if (tj == txt.size()) {
            if (pi == pattern.size()) {
                isMatch = true;
                return;
            }
        }
        //处理流程
        if (pi < pattern.size() && pattern[pi] == '*') {
            //匹配任意多个任意字符
            for (int i=0; i<txt.size()-tj; i++) {
                match(txt, pi+1, tj+i);
            }
        }else if (pi < pattern.size()  && pattern[pi] == '?'){
            //匹配0/1个任意字符
            match(txt, pi+1, tj);
            match(txt, pi+1, tj+1);
        }else if (pi < pattern.size()  && tj<txt.size() && pattern[pi] == txt[tj]){
            match(txt, pi+1, tj+1);
        }
    }
};


#endif /* Pattern_hpp */
