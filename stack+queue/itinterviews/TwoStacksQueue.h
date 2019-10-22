//
//  TwoStacksQueue.h
//  stack+queue
//
//  Created by junl on 2019/10/14.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef TwoStacksQueue_hpp
#define TwoStacksQueue_hpp

#include <stdio.h>
#include <stack>
/*
 思路:
 两个栈正好可以实现倒序.关键点把pushStack的数据倒序放到popStack中:
    1.如果popStack包含元素了的话，那么不能将数据从pushStack移动到popStack
    2.必须一次性的把pushStackd里面的元素移动到popStack中
 */
class TwoStacksQueue {
public:
    typedef int Value_t;
    void add(Value_t x)//添加元素
    {
        pushStack.push(x);
    }
    void poll()//删除队列首元素
    {
        move();
        if (popStack.empty()) {
            throw stackEmpty();
        }
        popStack.pop();
    }
    Value_t peek()//获取首元素
    {
        if (popStack.empty() && pushStack.empty()) {
            throw stackEmpty();
        }
        move();
        return popStack.top();
    }
private:
    std::stack<Value_t> pushStack;
    std::stack<Value_t> popStack;
    void move(){
        if (popStack.empty()) {
            //如果popStack为空，则把pushStack的所有元素倒序加入.
            while (!pushStack.empty()) {
                popStack.push(pushStack.top());
                pushStack.pop();
            }
        }
    }
};


void test_TwoStacksQueue(){
    std::cout << "-----------test_TwoStacksQueue-----------" << std::endl;
    TwoStacksQueue queue;
    queue.add(1);
    queue.add(2);
    queue.add(3);
    std::cout << "peek: "<< queue.peek() << std::endl;//1
    queue.poll();
    std::cout << "peek: "<< queue.peek() << std::endl;//2

}

#endif /* TwoStacksQueue_hpp */
