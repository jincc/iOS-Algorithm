//
//  maxInWindows.h
//  other
//
//  Created by junl on 2019/8/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef maxInWindows_hpp
#define maxInWindows_hpp

#include <stdio.h>
#include <vector>
#include <queue>
/*
 剑指Offer（六十四）：滑动窗口的最大值
 给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。

 https://www.nowcoder.com/practice/1624bc35a45c42c0bc17d17fa0cba788?tpId=13&tqId=11217&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */

namespace codinginterviews {
    
    int maxIndex(const std::vector<int>& num, unsigned int size, int index){
        int maxIndex = index;
        for (int i=index; i<index+size; i++) {
            if (num[maxIndex] < num[i])
                maxIndex = i;
        }
        return maxIndex;
    }
#pragma mark - v1
    /*
     思路：记录下滑动窗口的最大值和最大值对应的下标，然后依次向右移动，如果最大值从窗口范围内移出，那么重新计算最大值的位置，
     如果上一个最大值还是窗口内，则直接将其和新划进元素比较，去最大值。
     最坏情况下复杂度为o(n*logk)
     */
    std::vector<int> maxInWindows(const std::vector<int>& num, unsigned int size)
    {
        if (num.size() == 0 || size == 0 ||  num.size() < size) {
            return {};
        }
        std::vector<int>locations;
        std::vector<int>values;
        int vsize = num.size()-size+1;
        locations.resize(vsize);
        values.resize(vsize);
        locations[0]=maxIndex(num, size, 0);
        values[0]=num[locations[0]];
        for (int i=1; i<=num.size()-size; i++) {
            if (i > locations[i-1]) {
                //需要重新计算
                locations[i] = maxIndex(num, size, i);
            }else{
                locations[i] = num[locations[i-1]] > num[i+size-1] ? locations[i-1] :i+size-1;
            }
            values[i] = num[locations[i]];
        }
        return values;
    }
#pragma mark - v2 利用优先级队列
    std::vector<int> maxInWindows2(const std::vector<int>& num, unsigned int size){
        /*
         思路：这个列子，先进先出，属于队列的结构，问题可以转换为怎么从队列里面快速寻找最大值的位置.
         */
        if (num.size() == 0 || size == 0 ||  num.size() < size) {
            return {};
        }
        typedef std::pair<int , int> Pair;
        std::priority_queue<Pair> queue;
        for (int i=0; i<size-1; i++) {
            queue.push(Pair(num[i], i));
        }
        std::vector<int> result;
        for (int j=size-1; j<num.size(); j++) {
            //新推入新元素
            queue.push(Pair(num[j],j));
            //取最大值
            Pair p = queue.top();
            //如果最大值划出了窗口，则移除.
            while (p.second < j-(size-1)) {
                queue.pop();
                p = queue.top();
            }
            result.push_back(p.first);
        }
        
        return result;
    }
    
    
    void test_maxInWindows(){
        std::cout << "maxInWindows starting........." << std::endl;
        std::vector<int> num{2,3,4,2,6,2,5,1};
        std::vector<int> a = maxInWindows(num, 3) ;
        for (auto &n : a){
            std::cout << n << ", " ;
        }
        std::cout << std::endl;
        
#pragma mark - 使用优先级队列可以非常方便的构建出大顶堆
        std::priority_queue<int> q;
        for (int i=0; i<10; i++) {
            q.push(i);
        }
        while (!q.empty()) {
            std::cout << q.top() << ", ";
            q.pop();
        }
        std::cout << std::endl;
        
#pragma mark - v2
        std::vector<int> a2 = maxInWindows2(num, 3) ;
        for (auto &n : a2){
            std::cout << n << ", " ;
        }
        std::cout << std::endl;
    }
}
#endif /* maxInWindows_hpp */
