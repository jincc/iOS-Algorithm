//
//  LRUV2.h
//  DataStructC++
//
//  Created by junl on 2019/5/23.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef LRUV2_hpp
#define LRUV2_hpp
#include <stdio.h>
#include <map>
#include <unordered_map>
#include <utility>
#include <sstream>
/*
 LRUCache的升级版. 因为LRUCacheV1::get(key)查询操作，每次查询都需要把链表重头到尾遍历一遍，时间为o(n). 所以这里的优化版使用map结构来保存节点，这样查找就为o(1).
 
 新增能力:
    1. 使用map结构，c查找o(1)
    2. 除了节点个数限制以外，新增权重限制.
 
 需要注意的地方:
    插入删除，需要更新head和tail指针
 
 TODO:
 权重限制，还没完成
 */
template <typename Key_t,typename Value_t>
class LRUV2Node {
public:
    Key_t key;
    Value_t value;
    LRUV2Node *next = nullptr;
    LRUV2Node *pre = nullptr;
    LRUV2Node(Key_t k,Value_t v):key(k),value(v){}
    LRUV2Node()=default;
    ~LRUV2Node(){
//        std::cout << "~LRUV2Node" << std::endl;
    }
};
template <typename Key_t,typename Value_t>
bool
operator==(const LRUV2Node<Key_t , Value_t>& __x,
           const LRUV2Node<Key_t , Value_t>& __y){
    return __x.key == __y.key && __x.value == __y.value;
}

//链表结构，用来存储节点用的.
template <typename Key_t,typename Value_t>
class LRUV2Map{
public:
    typedef LRUV2Node<Key_t,Value_t> node;
    LRUV2Map(){
        head=tail=nullptr;
        node_count=0;
    }
    ~LRUV2Map(){
    }
    void bring_to_head(node *n);
    void insert_to_head(node *n);
    Key_t remove_tail();
    void display();
    void clear();
    int get_count(){
        return node_count;
    };
protected:
    node *head;
    node *tail;
    int node_count;
};

template <typename Key_t,typename Value_t>
class LRUCacheV2 {
public:
    typedef LRUV2Node<Key_t,Value_t> node;
    LRUCacheV2(){
        count_limit=10;
        cost_limit=20;
    };
    LRUCacheV2(int count_limit,int cost_limit){
        this->count_limit=count_limit;
        this->cost_limit=cost_limit;
    };
    ~LRUCacheV2(){};
    Value_t& get(Key_t key);
    void put(Key_t key, Value_t value);
    void display();
    void clear();
    //切割
    void trim_to_count(int count);
    void trim_to_cost(int cost);
protected:
    //用来管理LRU的结构，最常使用的在前，不常用的在后，方便limitcount,cost控制.
    LRUV2Map<Key_t, Value_t> lru_chain;
    // 用来快速查找key对应的节点,o(1)
    std::unordered_map<Key_t, node*> lru_map;
    int count_limit;
    int cost_limit;
};

#pragma mark -  LRUV2Map实现
template <typename Key_t,typename Value_t>
void LRUV2Map<Key_t,Value_t>::bring_to_head(node *n){
    if (n == head) return;
    if (n != tail) {
        n->pre->next = n->next;
        n->next->pre = n->pre;
    }else{
        tail = n->pre;
        tail->next=nullptr;

    }
    n->next = head;
    n->pre = nullptr;
    head->pre = n;
    head = n;
}

template <typename Key_t,typename Value_t>
void LRUV2Map<Key_t,Value_t>::insert_to_head(node *n){
    if (head) {
        n->next = head;
        head->pre = n;
        head = n;
    }else{
        head = tail = n;
    }
    node_count++;
}

template <typename Key_t,typename Value_t>
Key_t LRUV2Map<Key_t,Value_t>::remove_tail(){
    node *temp = tail;
    Key_t remove_key = temp->key;
    tail = tail->pre;
    tail->next = nullptr;
    delete temp;
    node_count--;
    return remove_key;
}

template <typename Key_t,typename Value_t>
void LRUV2Map<Key_t,Value_t>::display(){
    node *ct = head;
    while (ct) {
        std::cout << ct->key << ":" << ct->value << ",  ";
        ct=ct->next;
    }
    std::cout << std::endl;
}

template <typename Key_t,typename Value_t>
void LRUV2Map<Key_t,Value_t>::clear(){
    while (head) {
        node *temp = head;
        head = head->next;
        delete temp;
    }
    head=tail=nullptr;
}

#pragma mark - LRUCacheV2

template <typename Key_t,typename Value_t>
void LRUCacheV2<Key_t, Value_t>::put(Key_t key, Value_t value){
    auto it = lru_map.find(key);
    if (it != lru_map.cend()) {
        //已经存在节点，先删除在添加到head.
        node *_n = it->second;
        _n->value = value;
        lru_chain.bring_to_head(_n);
    }else{
        //not found
        node *_n = new node(key,value);
        lru_chain.insert_to_head(_n);
        lru_map[key] = _n;
//        lru_map.insert(make_pair(key, _n));
    }
    //切割如果满了的话
    trim_to_count(count_limit);
}

template <typename Key_t,typename Value_t>
Value_t& LRUCacheV2<Key_t, Value_t>::get(Key_t key){
    auto it = lru_map.find(key);
    if (it == lru_map.cend()) {
        std::ostringstream ss;
        ss << key << "不存在" << std::endl;
        throw illegalParameterValue(ss.str());
    }
    lru_chain.bring_to_head(it->second);
    return it->second->value;
}

template <typename Key_t,typename Value_t>
void LRUCacheV2<Key_t, Value_t>::trim_to_count(int count){
    while (lru_chain.get_count() > count) {
        Key_t key = lru_chain.remove_tail();
        lru_map.erase(key);
    }
}

template <typename Key_t,typename Value_t>
void LRUCacheV2<Key_t, Value_t>::display(){
    lru_chain.display();
}

template <typename Key_t,typename Value_t>
void LRUCacheV2<Key_t, Value_t>::clear(){
    lru_chain.clear();
    lru_map.erase(lru_map.begin(), lru_map.end());
}

namespace Case {
    void testLRUCacheV2(){
        LRUCacheV2<int , int> cache;
        for (int i=0; i<10; i++) {
            cache.put(i, i);
        }
        for (int i = 9; i>=0; i--) {
            cache.put(i, i);
        }
        cache.get(4);
        cache.display();
        cache.trim_to_count(8);
        cache.display();
    }
}

#endif /* LRUV2_hpp */
