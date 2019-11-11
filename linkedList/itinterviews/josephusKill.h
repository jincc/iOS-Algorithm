//
//  josephusKill.h
//  linkedList
//
//  Created by junl on 2019/11/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef josephusKill_hpp
#define josephusKill_hpp

#include <stdio.h>
#include "creatlist.h"
/*
 还原约瑟夫问题
 输入：一个环形单向链表的头节点和报数的值n
 返回:最后生存下来的节点，且这个节点自己组成环形单向链表，其他节点都删除.
 
 
 进阶问题：
 如果链表节点数为N，想要在时间复杂度为o(N)时完成原问题的求解，该怎么实现?
 */
//TODO: 进阶
namespace itinterviews{
    class josephusKill{
    public:
        ListNode* solve(ListNode *head, int n){
            if (!head ||  head->next == head || n < 1 )
                return head;
            
            int ct = 0;
            ListNode *node = head;
            std::cout << "依次删除节点如下: ";
            int __step = 0;
            while (node && node->next != node) {
                ct++;
                __step++;
                if (ct == n - 1) {
                    std::cout << node->next->val << ", ";
                    node->next = node->next->next;
                    ct = 0;
                }
                node = node->next;
            }
            std::cout << "最后剩下的: " << node->val << std::endl;
            std::cout << "一共走了 " << __step  << "步" << std::endl;
            return node;
        }
    };
    
    void test_josephusKill(){
        ListNode *head = codinginterviews::creatLists({1,2,3,4,5})->next;
        ListNode *tail = head;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = head;
        std::cout << "-----test_josephusKill-------" << std::endl;
        class josephusKill so;
        head = so.solve(head, 3);
        
    }
};
#endif /* josephusKill_hpp */
