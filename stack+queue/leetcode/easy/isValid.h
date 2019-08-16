//
//  isValid.h
//  stack+queue
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef isValid_hpp
#define isValid_hpp

#include <stdio.h>
#include <string>
#include <stack>
namespace leetcode {
    /*
     20. 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
     
     有效字符串需满足：
     
     左括号必须用相同类型的右括号闭合。
     左括号必须以正确的顺序闭合。
     注意空字符串可被认为是有效字符串。
     
     示例 1:
     
     输入: "()"
     输出: true
     示例 2:
     
     输入: "()[]{}"
     输出: true
     示例 3:
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/valid-parentheses
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    
    bool isValid(const std::string &s) {

        std::stack<char> st;
        for (auto &c : s){
            if (c == '('  ||
                c == '{'  ||
                c == '['){
                st.push(c);
            }else if(c == ')'  ||
                     c == '}'  ||
                     c == ']'){
                if (st.empty())
                    return false;
                auto &last =  st.top();
                if ((c == ')'  && last == '(') ||
                    (c == ']'  && last == '[') ||
                    (c == '}'  && last == '{')) {
                    st.pop();
                }else{
                    return false;
                }
            }else{
                return false;
            }
            
            
            
            
            
//            if (st.empty()) {
//                st.push(c);
//            }else{
//                auto &last =  st.top();
//                if ((c == ')'  && last == '(') ||
//                    (c == ']'  && last == '[') ||
//                    (c == '}'  && last == '{')) {
//                    st.pop();
//                }else{
//                    st.push(c);
//                }
//            }
        }
        
        return st.empty();
    }
}


#endif /* isValid_hpp */
