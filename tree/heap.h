//
//  heap.h
//  tree
//
//  Created by junl on 2019/7/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef heap_hpp
#define heap_hpp

#include <stdio.h>

/*
  堆的概念：
    1. 它是完全二叉树，所有可以用数组来存储
    2. 分为大顶堆和小顶堆；大顶堆中每个节点的值都大于等于子树所有节点的值.
   堆的主要操作：
    1.插入一个元素
    2.删除堆顶元素
   ***因为堆是完全二叉树，所有为了保护完全二叉树的结构(完全二叉树值得是除了叶子节点，其他节点都是满的)，我们都是操作数组末尾元素，然后将整个堆进行堆化.****
 
 */


class heap{
public:
    void insert(int val){
        if (count >= capacity) {
            return;
        }
        count++;
        elements[count] = val;
        //堆结构化
        int i=count;
        //如果父节点小于当前节点，交换
        while (i/2 > 0 && elements[i/2] < elements[i]) {
            std::swap(elements[i/2], elements[i]);
            i = i/2;
        }
    }
    void removemax(){
        if (count == 0)
            return;
        //先将末尾节点移到堆头部，然后删除尾结点
        elements[1] = elements[count];
        count--;
        
        //堆结构化
        int i=1;
        while (2*i+1<=count) {
            int maxindex = i;
            if (elements[2*i] > elements[2*i+1]) {
                maxindex = 2*i;
            }else if (elements[2*i] < elements[2*i+1]){
                maxindex = 2*i+1;
            }
            if (maxindex != i) {
                std::swap(elements[i], elements[maxindex]);
                i = maxindex;
            }else{
                break;
            }
        }
    }
    heap(int capacity_=10){
        capacity = capacity_;
        count = 0;
        elements = new int[capacity_];
    }
    ~heap(){
        delete [] elements;
    }
    void print(){
        for(int i=1;i<=count;i++){
            printf("%i ,",elements[i]);
        }
        putchar('\n');
    }
protected:
    int capacity;
    int *elements;
    int count;
};


#endif /* heap_hpp */
