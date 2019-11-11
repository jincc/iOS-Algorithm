//
//  singlyLinkedList.h
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef singlyLinkedList_hpp
#define singlyLinkedList_hpp

#include <stdio.h>
#include <iostream>

class singlyLinkedList {
public:
    friend std::ostream& operator<<(std::ostream &cout,singlyLinkedList& chain);
    typedef int  Value;
    struct Node{
        Value val;
        Node* next = nullptr;
        Node(const Value &d,Node* next_ = nullptr):val(d),next(next_){}
        void print(){
            Node *ct = this;
            while (ct) {
                std::cout << ct->val << ", ";
                ct = ct->next;
            }
            std::cout << std::endl;
        }
    };
    singlyLinkedList(){
        head = new Node(0);
    }
    ~singlyLinkedList(){
//        while (head) {
//            Node *pre = head;
//            head = head->next;
//            delete pre;
//        }
    }
#pragma mark - AST
    Node* start() const{
        return head->next;
    }
    
    Node* findByValue(const Value &v) const;
    Node* findByIndex(int index) const;
    void insertToHead(const Value &v);
    void insertTail(const Value &v);
    void insertAfter(Node * &p, const Value &v);
    void insertAfter(Node * &p,  Node* &v);
    void insertBefore(Node * &p, const Value &v);
    void deleteByNode(const Value &p);
protected:
    Node *head;
};
class DoubleNode {
public:
    DoubleNode *pre;
    DoubleNode *next;
    typedef int  Value;
    Value val;
    DoubleNode(Value val1):val(val1),pre(nullptr),next(nullptr){}
    void print(){
        DoubleNode *ct = this;
        while (ct) {
            std::cout << ct->val << ", ";
            ct = ct->next;
        }
        std::cout << std::endl;
    }
};

typedef singlyLinkedList::Node ListNode;
std::ostream& operator<<(std::ostream &cout,singlyLinkedList& chain);
#endif /* singlyLinkedList_hpp */
