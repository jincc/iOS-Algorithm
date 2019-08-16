//
//  MinStack.h
//  stack+queue
//
//  Created by junlongj on 2019/8/11.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef MinStack_hpp
#define MinStack_hpp

#include <stdio.h>
#include <stack>
/*
 155. 最小栈
 
 设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。
 
 push(x) -- 将元素 x 推入栈中。
 pop() -- 删除栈顶的元素。
 top() -- 获取栈顶元素。
 getMin() -- 检索栈中的最小元素。
 示例:
 
 MinStack minStack = new MinStack();
 minStack.push(-2);
 minStack.push(0);
 minStack.push(-3);
 minStack.getMin();   --> 返回 -3.
 minStack.pop();
 minStack.top();      --> 返回 0.
 minStack.getMin();   --> 返回 -2.
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/min-stack
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    class MinStack {
    public:
        /** initialize your data structure here. */
        MinStack() {
            
        }
        
        void push(int x) {
            astk.push(x);
            if(bstk.empty()){
                bstk.push(x);
            }else{
                if (bstk.top() >= x){
                    bstk.push(x);
                }
            }
        }
        
        void pop() {
            if (astk.empty() || bstk.empty()) return;
            int v = astk.top();
            astk.pop();
            if (v == bstk.top()){
                bstk.pop();
            }
        }
        
        int top() {
            if (astk.empty()) return 0;
            return astk.top();
        }
        
        int getMin() {
            if (bstk.empty()) return 0;
            return bstk.top();
        }
        std::stack<int> astk;
        std::stack<int> bstk;
    };
}
#endif /* MinStack_hpp */
