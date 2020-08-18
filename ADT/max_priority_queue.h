//
//  max_priority_queue.h
//  ADT
//
//  Created by junl on 2020/7/14.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef max_priority_queue_h
#define max_priority_queue_h

/*
 优先级队列是基于二叉堆来实现的。 二叉堆是什么？ 它是一种特殊的二叉树(完全二叉树),只不过一般存储在数组里面.
 二叉堆有大顶堆和小顶堆. 大顶堆就是说根节点比子节点都大，这对应到优先级队列就是arr[1] 一定是所有元素中最大的元素. 小顶堆同理.
 
 要维持二叉堆的这样结构，我们需要sink下沉和上浮swim操作，它们的目的是为了维护二叉堆的结构.
 */
class max_priority_queue{
public:
    max_priority_queue(int cap){
        this->cap = cap;
        this->cnt = 0;
        this->elements = new int[cap+1];//下标0不使用
    }
    void insert(int val){
        if (cnt >= cap) return;
        elements[++cnt] = val;
        swim(cnt);
    }
    int remove_max(){
        if (cnt == 0) return -1;
        int max = elements[1];
        std::swap(elements[1], elements[cnt]);
        cnt--;
        sink(1);
        return max;
    }
    int max(){
        if (cnt == 0) return -1;
        return elements[1];
    }
private:
    //获取左节点下标
    int left(int idx){
        return 2 * idx;
    }
    //获取右节点下标
    int right(int idx){
        return 2 * idx + 1;
    }
    int parent(int idx){
        return idx / 2;
    }
    //下沉操作
    void sink(int idx){
        int leftidx;
        while ((leftidx = left(idx)) < cnt) {
            //获取左右节点中的最大值
            if (leftidx+1 < cnt && elements[leftidx] < elements[leftidx+1])
                leftidx++;
            if (elements[leftidx] <= elements[idx])
                break;
            std::swap(elements[idx], elements[leftidx]);
            idx = leftidx;
        }
    }
    //上浮操作
    void swim(int idx){
        int parentidx;
        while((parentidx = parent(idx)) >= 1 && elements[idx] > elements[parentidx]){
            std::swap(elements[idx], elements[parentidx]);
            idx = parentidx;
        }
    }
    int cap;//容量
    int cnt;//当前数据个数
    int *elements;//存储地址
};

#endif /* max_priority_queue_h */
