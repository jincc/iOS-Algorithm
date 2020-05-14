//
//  Expression.hpp
//  stack+queue
//
//  Created by junl on 2020/3/15.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef Expression_hpp
#define Expression_hpp
#include <string>
#include <stack>
#include <stdio.h>
#include <vector>
using namespace std;
/*
  表达式求值运算。
  我们假设只有加减乘除运算，并且表达式输入是合法的.
 */
class Expression{
    enum ExpressionOperator {
         number,
         add = 1,
         sub = 2,
         mult = 3,
         division = 4
    };
    
public:
    int execut(vector<string> &expr){
        int result = 0;
        if (expr.size() == 0){
            return 0;
        }
        
        std::stack<int> stk_nums;
        std::stack<ExpressionOperator> stk_operator;
        
        for (int i = 0; i < expr.size();i++){
            ExpressionOperator opt = transferOperator(expr[i]);
            if (opt != number){
                if (stk_operator.empty()){
                    stk_operator.push(opt);
                }else if (opt > stk_operator.top()){
                    stk_operator.push(opt);
                }else{
                    while (!stk_operator.empty() && needCalt(opt, stk_operator.top()) && stk_nums.size() >= 2) {
                        //计算当前运算优先级比栈顶运算符的优先级小的话，计算之前的值
                        ExpressionOperator lastOperator = stk_operator.top();
                        stk_operator.pop();
                        int b = stk_nums.top();stk_nums.pop();
                        int a = stk_nums.top();stk_nums.pop();
                        int c = calt(a, b, lastOperator);
                        stk_nums.push(c);
                    }
                    stk_operator.push(opt);
                }
            }else{
                stk_nums.push(atoi(expr[i].c_str()));
            }
        }
        while (!stk_operator.empty() && stk_nums.size() >= 2) {
            //计算当前运算优先级比栈顶运算符的优先级小的话，计算之前的值
            ExpressionOperator lastOperator = stk_operator.top();
            stk_operator.pop();
            int b = stk_nums.top();stk_nums.pop();
            int a = stk_nums.top();stk_nums.pop();
            int c = calt(a, b, lastOperator);
            stk_nums.push(c);
        }
        return stk_nums.top();
    }
    
    ExpressionOperator transferOperator(string &str){
        if (str == "+"){
            return add;
        }else if (str == "-"){
            return sub;
        }else if (str == "*"){
            return mult;
        }else if (str == "/"){
            return division;
        }else {
            return number;
        }
    }
    bool needCalt(ExpressionOperator opt, ExpressionOperator top){
        if (opt == add || opt == sub){
            return true;
        }
        return top == mult || top == division;
    }
    int calt(int a, int b, ExpressionOperator opt){
        if (opt == number){
            return 0;//error
        }else if (opt == add){
            return a + b;
        }else if (opt == sub){
            return a - b;
        }else if (opt == mult){
            return a * b;
        }else {
            return a / b;
        }
        
    }
};

#endif /* Expression_hpp */
