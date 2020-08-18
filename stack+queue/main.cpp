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
//#include "queue.h"
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
#include "getMaxRectSize.h"
#include "Expression.h"
#include "validateStackSequences.h"
#include <deque>
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        /*
        每次滑动窗口，窗口的最大值都会更新，问题的关键在于最后最大值被划出去了，怎么样快速求出第二个最大值，因此需要保存的是最大值的列表，而不是单个值.

        维护一个大顶堆的结构
        */
        if (nums.size() == 0 || k<=1) return nums;

        priority_queue<int, vector<int>, greater<int>> q;
        vector<int> results;
        for(int i=0; i < nums.size(); i++){
            q.push(i);
            if (i >= k-1){
                if (q.top() + k <= i ){
                    q.pop();
                }
                results.push_back(nums[q.top()]);
            }
        }
        return results;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
//    stack<int> stk;
//    printf("stack test starting..........\n");
//    stk.push(1);
//    stk.push(2);
//    stk.push(3);
//    stk.print();
//    stk.pop();
//    stk.pop();
//    stk.print();
    
//    deque<int> dq;
//    dq.push_back(1);
//    dq.push_back(2);
//    while (!dq.empty()) {
//        printf("%d \n",dq.back());
//        dq.pop_back();
//    }
    deque<int> dq;
    dq.push_front(1);
    dq.push_front(2);
    while (!dq.empty()) {
        printf("%d \n",dq.back());
        dq.pop_back();
    }
    /*
     pop_front()
     2
     1
     pop_back()
     1
     2
     */
    
    
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
//#if true
//    queue_on_circular<int> queue1(5);
//#else
//    queue_on_linkedlist<int> queue1;
//#endif
//    queue1.enqueue(10);
//    queue1.enqueue(20);
//    queue1.enqueue(30);
//    queue1.dequeue();
//    queue1.print();
//    queue1.enqueue(40);
//    queue1.enqueue(50);
//    queue1.print();
    
    
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
    test_validateStackSequences();
    
    Expression expr;
    vector<string> strs{"3", "+", "5", "-", "6", "*", "8" , "-" , "6"};
    int i = expr.execut(strs);
    printf("expr = [ %i]\n", i);
    
    Solution so;
    vector<int> a1{1,3,-1,-3,5,3,6,7};
    so.maxSlidingWindow(a1, 3);
    return 0;
}
