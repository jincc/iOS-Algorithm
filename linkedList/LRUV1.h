//
//  LRU.h
//  DataStructC++
//
//  Created by junl on 2019/5/23.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef LRU_hpp
#define LRU_hpp
#include <stdio.h>
#include "illegalParameterValue.h"
#include <iostream>
#include <string>
#include <vector>
/*
常见的策略有三种：
先进先出策略 FIFO（First In，First Out)
最少使用策略 LFU（Least Frequently Used)
最近最少使用策略 LRU（Least Recently Used)
*/


template <typename Key_t,typename Value_t>
class LRUNode {
public:
    Key_t key;
    Value_t value;
    LRUNode *next = nullptr;
    LRUNode *pre = nullptr;
    LRUNode(Key_t k,Value_t v):key(k),value(v){}
    LRUNode()=default;
};

/// 通过构建双向链表，每次插入或查询的时候，首先通过key查询是否已存在于链表中，如果存在的话，删除并插入到头节点，如果不存在的话，先判断时候缓存已满，如果满了的话，删除最后节点，然后插入首部.
template <typename Key_t,typename Value_t>
class LRUCacheV1 {
public:
    typedef LRUNode<Key_t,Value_t> node;
    // 初始化缓存
    LRUCacheV1(int cacheSize){
        this->cacheSize = cacheSize;
        this->listSize = 0;
        this->head = new node;
    }
    // 获取节点
    Value_t& get(Key_t key){
        node *ct = head->next;
        while (ct && ct->key != key) {
            ct = ct->next;
        }
        if (!ct)  throw illegalParameterValue("当前值不存在");
        put(ct->key, ct->value);
        return ct->value;
    }
    // 插入节点
    void put(Key_t key, Value_t value){
        //首先查找key对应的节点存在不，如果存在的话，删除当前节点在插入到首部。如果不存在则插入首部
        node *ct = head->next;
        while (ct && ct->key != key) {
            ct = ct->next;
        }
        if (ct) {
            node *pre = ct->pre;
            node *next = ct->next;
            pre->next = next;
            next->pre = pre;
            delete ct;
            listSize--;
        }
        if (listSize == cacheSize) {
            //清除最后没有使用的节点
            ct = head->next;
            while (ct->next) {
                ct = ct->next;
            }
            ct->pre->next = nullptr;
            delete ct;
            listSize--;
        }
        node *first = new node(key,value);
        node *preFirst = head->next;
        //先断开之前的联系
        first->pre = head;
        first->next = preFirst;
        head->next = first;
        if (preFirst) {
            preFirst->pre = first;
        }
        listSize++;
    }
    void display(){
        node *ct = head->next;
        while (ct) {
            std::cout << ct->key << ":" << ct->value << ",  ";
            ct=ct->next;
        }
        std::cout << std::endl;
    }
protected:
    node *head;
    int cacheSize;
    int listSize;
};

namespace Case {
    void testLRU(){
        std:: cout << "start test LRU" << std::endl;
        LRUCacheV1<int, std::string> cache(5);
        cache.put(0, "a");
        cache.put(1, "b");
        cache.put(2, "c");
        cache.put(3, "d");
        cache.put(4, "e");
        cache.put(5, "f");
        cache.put(0, "a");
        cache.put(1, "c");
        try {
            cache.get(4);
            cache.get(11);
        } catch (illegalParameterValue &e) {
            e.outputMessage();
        }
        cache.display();
    }
}


#endif /* LRU_hpp */
