//
//  sortStackByStack.h
//  stack+queue
//
//  Created by junl on 2019/10/16.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef sortStackByStack_hpp
#define sortStackByStack_hpp

#include <stdio.h>
#include <stack>
#include "reverseStack.h"
/*
 用一个栈实现另一个栈的排序
 
 一个栈中元素的类型为整形，现在想将该栈从顶到底c按照从大到小的顺序排序，只允许借助另一个栈，除此之外可以申请临时变量，但不能借助额外的数据结构。如何完成排序?
 */


class sortStackByStack {
public:
    /*
     思路:
     首先构建一个临时栈，我们按照从大到小的顺序依次将原始数据放进temp_stk去，然后再将temp_stk依次pop进stk，即是答案.
     
     那么如果保证temp_stk是有序的呢？
     比如我们要向temp_stk插入newValue，比如当前栈顶元素比newValue小的话，那么将栈顶元素出栈然后重新压入源栈。
     否则的话，直接将newValue压入temp_stk.
     */
    void solve(std::stack<int> &stk){
        std::stack<int> temp_stk;
        if (stk.empty()) {
            return;
        }
        
        while (!stk.empty()) {
            int newValue = stk.top();
            stk.pop();
            
            if (temp_stk.empty()) {
                temp_stk.push(newValue);
            }else{
                while (!temp_stk.empty() && temp_stk.top() < newValue) {
                    stk.push(temp_stk.top());
                    temp_stk.pop();
                }
                temp_stk.push(newValue);
            }
        }
        
        while (!temp_stk.empty()) {
            stk.push(temp_stk.top());
            temp_stk.pop();
        }
    }
};


void test_sortStackByStack(){
    std::stack<int> stk({5,4,8,7});
    class sortStackByStack so;
    std::cout << "------test_test_sortStackByStack---------" << std::endl;
    std::cout << "原始数据为：";
    printStack(stk);
    so.solve(stk);
    std::cout << "排序后数据为：";
    printStack(stk);
}


#endif /* sortStackByStack_hpp */
