//
//  GetLeastNumbers_Solution.h
//  other
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef GetLeastNumbers_Solution_hpp
#define GetLeastNumbers_Solution_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（二十九）：最小的K个数
 输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。

https://www.nowcoder.com/practice/6a296eb82cf844ca8539b57c23e6e9bf?tpId=13&tqId=11182&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */

namespace codinginterviews {
    
    void swap_(int &a,int &b){
        int temp = a;
        a = b;
        b = temp;
    }
    void heapify(std::vector<int> &input,int k, int index){
        //判断叶子节点是不是比跟小.
        while (true) {
            int lc = 2*index+1;
            if (lc+1 <k &&input[lc] < input[lc+1]) {
                lc++;
            }
            if (lc < k && input[lc] > input[index]) {
                swap_(input[lc], input[index]);
                index = lc;
            }else{
                break;
            }
        }
    }

    std::vector<int> GetLeastNumbers_Solution(std::vector<int> input, int k) {
        if (input.size() < k ) {
            return input;
        }
        std::vector<int> heap(input.begin(),input.begin()+k);
        //创建大顶堆
        for (int i=k/2-1; i>=0; i--) {
            //跳转堆结构
            heapify(heap, k, i);
        }
        
        for (int i=k; i<input.size(); i++) {
            if (input[i] < heap[0]) {
                heap[0] = input[i];
                heapify(heap, k, 0);
            }
        }
        //排序
        for (int i=k-1; i>0; i--) {
            swap_(heap[0], heap[i]);
            heapify(heap, --k, 0);
        }
        return heap;
    }
    
    void test_GetLeastNumbers_Solution(){
        std::vector<int> a{4,5,1,6,2,7,3,8};
        std::cout << "test_GetLeastNumbers_Solution starting,....." << std::endl;
        std::vector<int> b = GetLeastNumbers_Solution(a, 4);
        b;
    }
}
#endif /* GetLeastNumbers_Solution_hpp */
