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
#include <string.h>
/*
 正则表达式匹配，假设通配符只有两个，一个是*，一个是?
 * 代表可以匹配任意多个(>=0)任意字符.
 ? 代表匹配另个或一个任意字符
 
 对于字符串的匹配，对于字符来说有两种情况：
    1.如果是非通配符情况下，必须完全匹配
    2.如果是通配字符，就有很多种选择了，就拿*来说，它可以匹配任意多个任意字符，这里我们利用回溯的思想穷举出所有的情况.
 
 */

typedef struct {
    const char *str;
    size_t slen;
    const char *pattern;
    size_t plen;
    bool match;
}match_t;

void match(match_t *context, int pidx, int sidx);
bool isMatch(const char *str, const char *pattern){
    match_t m  = (match_t){str, strlen(str), pattern, strlen(pattern), false};
    match(&m, 0, 0);
    return m.match;
}

void match(match_t *context, int pidx, int sidx){
    if (context->match) return;
    
    if (pidx == context->plen){
        if (sidx == context->slen)
            context->match = true;
    }
    
    char ch = context->pattern[pidx];
    if (ch == '?'){
        match(context, pidx+1, sidx);
        match(context, pidx+1, sidx+1);
    }else if (ch == '*'){
        for (int i=0; i <= context->slen - sidx; i++) {
            match(context, pidx+1, sidx+i);
        }
    }else if (sidx < context->slen && ch == context->str[sidx]){
        match(context, pidx+1, sidx+1);
    }
    
}
#endif /* Pattern_hpp */
