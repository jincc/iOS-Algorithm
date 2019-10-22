//
//  reverseStack.h
//  stack+queue
//
//  Created by junl on 2019/10/15.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef reverseStack_hpp
#define reverseStack_hpp

#include <stdio.h>
#include <stack>
/*
 如何仅仅会用递归函数和栈操作逆序一个栈?
 
 比如一个栈一次压入1，2，3，4，5，那么从栈顶到栈底分别是5，4，3，2，1.将整个栈转置后，从栈顶到栈底为1，2，3，4，5，也就是栈的逆序，但是只能用递归函数来实现，不能运用其他数据结构.
 */
class reverseStack {
    /*
     思路：
     利用递归的思想，“递”和“归”:
     | 1       1
     | 2       2
     | 3       3
     | 4       4
     | 5  ---- 5
     
     如果递的过程我们依次拿到1，2，3，4，5，那么归的过程，我们就可以依次处理5，4，3，2，1，分别将它们入栈，就是我们要的答案。
     
     那么怎么依次获取到1，2，3，4，5呢？
     这正好就是从栈的栈底元素到栈顶元素，所以我们先定义一个函数申明getAndRemoveLastElement.
     伪代码如下:
     reverse:
         if (stk.empty())
            return;
     
         int v = getAndRemoveLastElement(stk);
         reverse(stk);
         stk.push(v);
     
     */
public:
    void reverse(std::stack<int> &stk){
        if (stk.empty()) {
            return;
        }
        int v = getAndRemoveLastElement(stk);
        reverse(stk);
        stk.push(v);
    }
    
    int getAndRemoveLastElement(std::stack<int> &stk){
        int top = stk.top();
        stk.pop();
        if (stk.empty()) {
            return top;
        }else{
            //如果当前不是栈底元素的话，继续深度搜索,直到找到栈底元素
            int v = getAndRemoveLastElement(stk);
            stk.push(top);
            return v;
        }
    }
    
};

void printStack(std::stack<int> stk){
    while (!stk.empty()) {
        std::cout << stk.top() << ", ";
        stk.pop();
    }
    std::cout << std::endl;
}

void test_reverseStack(){
    std::stack<int> stk({5,4,3,2,1});
    std::cout << "--------test_reverseStack -----------" << std::endl;
    std::cout << "原始数据为：";
    printStack(stk);
    std::cout << "翻转数据为：";
    reverseStack so;
    so.reverse(stk);
    printStack(stk);
    
    
}


#endif /* reverseStack_hpp */
