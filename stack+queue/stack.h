//
//  stack.h
//  stack+queue
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include <iostream>
#include "illegalParameterValue.h"


template <typename Value>
class stack {
public:
    void push(const Value &v){
        Node *node = new Node(v);
        if (top) {
            node->next = top;
            top = node;
        }else{
            top = node;
        }
    }
    Value& pop(){
        if (top == nullptr)
            throw stackEmpty();
        Value &v = top->val;
        top = top->next;
        return v;
    }
    Value& topElement(){
        if (top == nullptr)
            throw stackEmpty();
        Value &v = top->val;
        return v;
    }
    void print(){
        Node *ct = top;
        while (ct) {
            std::cout <<  ct->val << ", ";
            ct = ct->next;
        }
        std::cout << std::endl;
    }
private:
    class Node{
    public:
        Value val;
        Node *next;
        Node(const Value &v):val(v),next(nullptr){}
    };
    Node *top;
};

#endif /* stack_hpp */
