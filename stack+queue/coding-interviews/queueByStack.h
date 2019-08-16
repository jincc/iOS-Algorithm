//
//  queueByStack.h
//  stack+queue
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef queueByStack_hpp
#define queueByStack_hpp

#include <stdio.h>
#include <stack>
/*
 剑指Offer（五）：用两个栈实现队列
 用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=13&tqId=11158&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking

 */
namespace codinginterviews  {
    class Queue
    {
    public:
        void push(int node) {
            stack1.push(node);
        }
        
        int pop() {
            if (stack2.empty()) {
                while (!stack1.empty()) {
                    stack2.push(stack1.top());
                    stack1.pop();
                }
            }
            if (stack2.size() > 0) {
                int node = stack2.top();
                stack2.pop();
                return node;
            }
            return 0;
        }
        
    private:
        std::stack<int> stack1;
        std::stack<int> stack2;
    };
    
    void test_Queue(){
        Queue q;
        
    }
}


#endif /* queueByStack_hpp */
