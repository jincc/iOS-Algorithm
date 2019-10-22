//
//  main.cpp
//  stack+queue
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "stack.h"
#include "sampleBrowser.h"
#include "queue.h"
#include "isValid.h"
#include "longestValidParentheses.h"
#include "queueByStack.h"
#include "MinStack.h"
#include <string>
#include "TwoStacksQueue.h"
#include "reverseStack.h"
#include "sortStackByStack.h"
#include "hanoiProblem.h"
#include "getMaxWindow.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    stack<int> stk;
    printf("stack test starting..........\n");
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.print();
    stk.pop();
    stk.pop();
    stk.print();
    
    printf("sampleBrowser starting..........\n");
    sampleBrowser browser;
    browser.open("http://www.baidu.com");
    browser.open("http://news.baidu.com/");
    browser.open("http://news.baidu.com/ent");
    browser.goBack();
    browser.goBack();
    browser.goForward();
    browser.open("http://www.qq.com");
    browser.goForward();
    browser.goBack();
    browser.goForward();
    browser.checkCurrentPage();
    browser.goBack();
    browser.goBack();
    browser.goBack();
    browser.checkCurrentPage();
    
    printf("queue_on_array starting..........\n");
#if true
    queue_on_circular<int> queue1(5);
#else
    queue_on_linkedlist<int> queue1;
#endif
    queue1.enqueue(10);
    queue1.enqueue(20);
    queue1.enqueue(30);
    queue1.dequeue();
    queue1.print();
    queue1.enqueue(40);
    queue1.enqueue(50);
    queue1.print();
    
    
    std::string s = "{()[]{}}";
    std::cout << "有效字符串：()[]{}, " << leetcode::isValid(s) << std::endl;
    s = ")()())";
    std::cout << "最长有效括号: )()())" << leetcode::longestValidParentheses(s) << std::endl;
    
    test_Minstack();
    test_TwoStacksQueue();
    test_reverseStack();
    test_sortStackByStack();
    test_hanoiProblem();
    test_getMaxWindow();
    return 0;
}
