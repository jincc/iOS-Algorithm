//
//  queue.h
//  stack+queue
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <stdio.h>
#include <iostream>
#include "singlyLinkedList.h"
template <typename Value>
class queue {
public:
    virtual bool enqueue(const Value &v) = 0;
    virtual Value& dequeue() = 0;
    virtual void print() = 0;
};

/*
 队列：操作受限的线性表。有入队和出队的操作，所以需要两个指针。
 队列的几种实现形式:
 1. 基于数组，需求是容量固定，比如线程池这种结构肯定不支持无线扩容
 2. 基于链表,这种q结构的队列，支持无线扩容。
 3. 为了解决第一种方式c中的数据搬运，于是出现了循环队列
 */


template <typename Value>
class queue_on_array: public queue<Value> {
public:
    bool enqueue(const Value &v) {
        //tail指针到达边界
        if (tail == capacity) {
            //队列满了
            if (head == 0) {
                return false;
            }
            //将head-tail之间的数据搬移到数组前面部分
            for (int i=head; i <= tail; i++) {
                elements[i-head] = elements[i];
            }
            tail -= head;
            head = 0;
        }
        elements[tail++] = v;
        return true;
    }
    Value& dequeue() {
        if (head == tail)
            throw "队列为空";
        Value &v = elements[head];
        head++;
        return v;
    }
    queue_on_array(int capacity_){
        capacity = capacity_;
        head = tail = 0;
        elements = new Value[capacity_];
    }
    ~queue_on_array(){
        delete [] elements;
    }
    void print(){
        for (int i=head; i<tail; i++) {
             std::cout << elements[i] << ", ";
        }
        std::cout << std::endl;
    }
protected:
    Value *elements;
    int capacity;
    int head;
    int tail;
};


template <typename Value>
class queue_on_linkedlist : public queue<Value> {
public:
    bool enqueue(const Value &v) {
        ListNode *node = new ListNode(v);
        if (!head) {
            head = tail = node;
            return true;
        }
        tail->next = node;
        tail = tail->next;
        return true;
    }
    Value& dequeue() {
        if (!head)
            throw "队列为空";
        Value & v = head->val;
        head=head->next;
        if (head==nullptr) {
            tail = nullptr;
        }
        return v;
    }
    void print(){
        ListNode *ct = head;
        while (ct) {
            std::cout << ct->val << ", ";
            ct = ct->next;
        }
        std::cout << std::endl;
    }
    queue_on_linkedlist():head(nullptr),tail(nullptr){}
    ~queue_on_linkedlist(){
        //释放内存
        while (head) {
            ListNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
private:
    ListNode *head;
    ListNode *tail;
};


//循环队列
template <typename Value>
class queue_on_circular : public queue_on_array<Value> {
    
public:
    using queue_on_array<Value>::queue_on_array;
    bool enqueue(const Value &v){
        //说明队列满了
        if ((this->tail + 1) % this->capacity == this->head) {
            return false;
        }
        this->elements[this->tail] = v;
        this->tail = (this->tail + 1) % this->capacity;
        return true;
    }
    Value& dequeue(){
        if (this->head == this->tail)
            throw "队列为空";
        Value &v = this->elements[this->head];
        this->head = (this->head + 1) % this->capacity;
        return v;
    }
    void print(){}
private:
    int tag;
};


#endif /* queue_hpp */
