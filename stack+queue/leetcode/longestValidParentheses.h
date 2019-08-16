//
//  longestValidParentheses.h
//  stack+queue
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef longestValidParentheses_hpp
#define longestValidParentheses_hpp

#include <stdio.h>
#include <string>
#include <stack>
namespace leetcode {
    /*
     32.给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
     
     示例 1:
     
     输入: "(()"
     输出: 2
     解释: 最长有效括号子串为 "()"
     示例 2:
     
     输入: ")()())"
     输出: 4
     解释: 最长有效括号子串为 "()()"
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/longest-valid-parentheses
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    int longestValidParentheses(std::string &s) {
        int maxlen = 0;
        
        std::stack<int> stk;//栈里面只存储***左括号****的位置
        int errorindex = -1;
        for(int i=0;i<s.size();i++){
            if (s[i] == '('){
                stk.push(i);
            }else{
                if (stk.empty()){
                    //说明当前)是无效的
                    errorindex = i;
                }else{
                    stk.pop();//弹出一个"("
                    if (stk.empty()) {
                        maxlen = std::max(maxlen, i-errorindex);
                    }else{
                        maxlen = std::max(maxlen, i-stk.top());
                    }
                    
                }
            }
        }
        return maxlen;
    }
    
}


#endif /* longestValidParentheses_hpp */
