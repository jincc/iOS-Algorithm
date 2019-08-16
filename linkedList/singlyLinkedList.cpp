//
//  singlyLinkedList.cpp
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#include "singlyLinkedList.h"

singlyLinkedList::Node* singlyLinkedList::findByValue(const Value &v)const{
    Node *ct = head->next;
    while (ct && ct->val != v) {
        ct = ct->next;
    }
    return ct;
}

singlyLinkedList::Node* singlyLinkedList::findByIndex(int index) const{
    int c_ = 0;
    Node *ct = head->next;
    while (ct && c_ < index) {
        ct = ct->next;
        c_++;
    }
    return ct;
}

void singlyLinkedList::insertToHead(const Value &v){
    Node *node = new Node(v);
    //将之前的节点放在新node之后
    node->next = head->next;
    head->next = node;
}

void singlyLinkedList::insertTail(const Value &v){
    Node *ct = head;
    while (ct->next) {
        ct=ct->next;
    }
    Node *node = new Node(v);
    ct->next = node;
}

void singlyLinkedList::insertAfter(Node * &p, const Value &v){
    if (p == nullptr) {
        return;
    }
    Node *node = new Node(v);
    node->next = p->next;
    p->next = node;
}

void singlyLinkedList::insertAfter(Node * &p, Node* &v){
    if (p == nullptr || v == nullptr) {
        return;
    }
    v->next = p->next;
    p->next = v;
}

void singlyLinkedList::insertBefore(Node * &p, const Value &v){
    if (p == nullptr) {
        return;
    }
    Node *ct = head;
    while (ct->next != p) {
        ct=ct->next;
    }
    Node *node = new Node(v);
    node->next = p;
    ct->next = node;
}

void singlyLinkedList::deleteByNode(const Value &p){
    Node *ct = head;
    while (ct->next && ct->next->val != p) {
        ct=ct->next;
    }
    //找到前驱节点ct
    if (!ct->next) {
        return;
    }
    Node *last = ct->next->next;
    Node *deleteNode = ct->next;
    ct->next = last;
    delete deleteNode;
}

std::ostream& operator<<(std::ostream &cout,singlyLinkedList& chain){
    singlyLinkedList::Node *ct = chain.head->next;
    while (ct) {
        cout << ct->val << ", ";
        ct = ct->next;
    }
    cout << std::endl;
    return cout;
}
