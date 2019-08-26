//
//  generateParenthesis.h
//  recursion
//
//  Created by junlongj on 2019/8/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef generateParenthesis_hpp
#define generateParenthesis_hpp

#include <stdio.h>
#include <vector>
#include <string>
/*
22.括号生成
 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
 
 例如，给出 n = 3，生成结果为：
 
 [
 "((()))",
 "(()())",
 "(())()",
 "()(())",
 "()()()"
 ]
 在真实的面试中遇到过这道题？
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/generate-parentheses
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路: 递归法.
     有效的括号组合，必定在每一次遍历的时候，左括号的数量大于等于右括号的数量。可以利用这一点来作为递归的终止条件.
     */
    std::vector<std::string> results;
    void generateParenthesis(int n,int leftParenthesis,int rightParenthesis, std::string s){
        if (leftParenthesis < rightParenthesis)
            return;
        if (leftParenthesis == n && rightParenthesis == n){
            results.push_back(s);
            return;
        }
        if (leftParenthesis < n){
            generateParenthesis(n,leftParenthesis + 1, rightParenthesis, s+'(');
        }
        if (rightParenthesis < n){
            generateParenthesis(n,leftParenthesis, rightParenthesis+1, s+')');
        }
    }
    std::vector<std::string> generateParenthesis(int n) {
        std::string s;
        generateParenthesis(n,0,0,s);
        return results;
    }
    
#pragma mark - v2
    /*
     n对括号组成的有效序列，可以分为下面这几部分组成.
     
     "(" + $1 + ")" + $2
     
     $1,$2分别表示c对有效序列和n-c-1对有效序列
     */
    std::vector<std::string> generateParenthesis2(int n) {
        std::vector<std::string> results;
        if (n == 0) {
//            std::cout << results.size() << std::endl;
            results.push_back("");
        }else{
            for (int i=0; i<n; i++) {
                for (auto &left : generateParenthesis2(i)) {
                    for (auto &right : generateParenthesis2(n-i-1)) {
                        results.push_back("(" + left + ")" + right);
                    }
                }
            }
        }
        return results;
    }
    
    void test_generateParenthesis2(){
        std::cout << "generateParenthesis2 starting......." << std::endl;
        auto x =  generateParenthesis2(3);
        for (auto &s : x) {
            std::cout << s << std::endl;
        }
    }
}
#endif /* generateParenthesis_hpp */
