//
//  getMaxWindow.h
//  stack+queue
//
//  Created by junl on 2019/10/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef getMaxWindow_hpp
#define getMaxWindow_hpp

#include <stdio.h>
#include <queue>
#include <vector>
/*
 生成窗口最大值数组
 
 有一个整形数组arr和大小为w的窗口，从数组的最左边滑动到最右边，窗口每次只能向右边滑动一个位置。
 
 求每次窗口中的最大值。
 */
//using namespace std;
//最坏情况:比如7,6,5,4,3,2,1 会退化到n*w

class __getMaxWindow_bad {
public:
    std::vector<int> solve(std::vector<int> &arr, int w){
        std::vector<int> results;
        std::deque<int> dq;
        int count = arr.size() - w + 1;
        if (w == 0 || arr.empty() || count <= 0) {
            return results;
        }
        int maxv = INT_MIN;
        for (int i=0; i<arr.size(); i++) {
            if (dq.size() < 3) {
                dq.push_back(arr[i]);
                maxv = std::max(maxv, arr[i]);
            }else{
                results.push_back(maxv);
                
                int front =  dq.front();
                dq.pop_front();
                if (front == maxv) {
                    //更新现在最大的值
                    int secondmaxv = dq[0];
                    for (int j=0; j<dq.size(); j++) {
                        secondmaxv = std::max(secondmaxv, dq[j]);
                    }
                    maxv = secondmaxv;
                }
                dq.push_back(arr[i]);
                maxv = std::max(maxv, arr[i]);
            }
        }
        results.push_back(maxv);
        return results;
    }
};


class getMaxWindow {
public:
    /*
     思路：
     题目的关键在于如何维护最大值的跟新.比如当最大值出窗口以后，第二大值能马上补位.
     所以我们要维护一个队列，里面保存着最大值元素的位置信息:
     我们通过新元素和队尾元素的大小关系，在队列的尾部进行数据的更新，始终保持队尾的元素大于等于当前元素.这样队首元素肯定是窗口最大值.
     */
    std::vector<int> solve(std::vector<int> &arr, int w){
        std::vector<int> results;
        if (arr.empty() || w < 1) {
            return results;
        }
        
        std::deque<int> dq;
        for (int i=0; i<arr.size(); i++) {
            //如果新元素比队列尾部元素大的话，删除队尾元素
            while (!dq.empty() && arr[i] >= arr[dq.back()]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            //如果队列首元素离开窗口的话，弹出去
            if (!dq.empty() && dq.front() == i-w) {
                dq.pop_front();
            }
            
            if (i >= w-1) {
                results.push_back(arr[dq.front()]);
            }
        }
        
        
        return results;
    }
};

void test_getMaxWindow(){
    std::cout << "-------test_getMaxWindow---------" << std::endl;
    std::vector<int> arr{4,3,5,4,3,3,6,7};
    getMaxWindow so;
    std::vector<int> resutls = so.solve(arr, 3);
    for (int r: resutls) {
        std::cout << r << ", ";
    }
    std::cout << std::endl;
}
#endif /* getMaxWindow_hpp */
