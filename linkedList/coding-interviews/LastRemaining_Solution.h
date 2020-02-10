//
//  LastRemaining_Solution.h
//  linkedList
//
//  Created by junl on 2020/1/13.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef LastRemaining_Solution_hpp
#define LastRemaining_Solution_hpp

#include <stdio.h>
namespace codinginterviews{
    class Solution_LastRemaining {
    public:
        class Node{
        public:
            int val;
            Node *next;
            Node(int v):val(v),next(nullptr){};
        };
        int LastRemaining_Solution(int n, int m)
        {
            if (n <= 0 || m <=0 || m >= n)
                return -1;
            Node *head = new Node(0);
            Node *node = head;
            Node *pre;
            for(int i=0;i<n;i++){
                node->next = new Node(i);
                node = node->next;
            }
            head = head->next;
            node->next = head;
            pre = node;
            node = head;
            int cnt =0;
            
            while(node->next != node){
                if (cnt == m-1){
                    if (pre->next){
                        pre->next = pre->next->next;
                    }
                    cnt = 0;
                    node = pre->next;
                }else{
                    pre = node;
                    node = node->next;
                    cnt++;
                }
            }
            return node->val;
        }
    };
    
    void test_Solution_LastRemaining(){
        std::cout << "-----LastRemaining_Solution-------" << std::endl;
        class Solution_LastRemaining so;
        std::cout << so.LastRemaining_Solution(5,3) << std::endl;
    }
};
#endif /* LastRemaining_Solution_hpp */
