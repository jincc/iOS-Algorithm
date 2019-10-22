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
class MinStack {
public:
    typedef int Value_t;
    void push(Value_t x){
        dataStack.push(x);
        
        if (minStack.empty()) {
            minStack.push(x);
        }else{
            if (minStack.top() >= x) {
                minStack.push(x);
            }
        }
    }
    void pop(){
        if (dataStack.empty()) {
            return;
        }
        Value_t t = dataStack.top();
        dataStack.pop();
        if (t == minStack.top()) {//minStack.top()即是minStack中的最小值也是dataStack中的最小值,所以t 不可能比它小
            minStack.pop();
        }else if (t > minStack.top()){}
    }
    Value_t top(){
        if (dataStack.empty()) {
            throw stackEmpty();
        }
        return dataStack.top();
    }
    Value_t getMin(){
        if (minStack.empty()) {
            throw stackEmpty();
        }
        return minStack.top();
    }
private:
    std::stack<Value_t> dataStack;
    std::stack<Value_t> minStack;
};

/*
 思路:
 任然用两个栈来保存数据，dataStack用来存储数据，minStack用来存储最小值.
 存储最小值的逻辑如下:
 如果newValue比minValue大的话,那么存储最小值minValue.
 如果newValue比minValue小或者等的话，那么存储newValue.
 */
class MinStack2 {
public:
    typedef int Value_t;
    void push(Value_t x){
        dataStack.push(x);
        if (minStack.empty()) {
            minStack.push(x);
        }else if (x > minStack.top()){
            minStack.push(minStack.top());
        }else{
            minStack.push(x);
        }
    }
    void pop(){
        dataStack.pop();
        minStack.pop();
    }
    Value_t top(){
        if (dataStack.empty()) {
            throw stackEmpty();
        }
        return dataStack.top();
    }
    Value_t getMin(){
        if (minStack.empty()) {
            throw stackEmpty();
        }
        return minStack.top();
    }
private:
    std::stack<Value_t> dataStack;
    std::stack<Value_t> minStack;
};

void test_Minstack(){
//    typedef MinStack Stack_t;
    typedef MinStack2 Stack_t;
    Stack_t stack;
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(1);
    stack.push(2);
    stack.push(1);
    
    std::cout << "-----test_Minstack----------" << std::endl;
    std::cout << stack.getMin() << std::endl;
    
    stack.pop();
    stack.pop();
    stack.pop();
    std::cout << stack.top() << ",min: "<< stack.getMin() << std::endl; //5
    
}

#endif /* MinStack_hpp */
