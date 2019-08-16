//
//  swapPairs.h
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef swapPairs_hpp
#define swapPairs_hpp

#include <stdio.h>
#include "singlyLinkedList.h"
namespace leetcode {
    /*
     24.给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
     
     你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
     
     示例:
     
     给定 1->2->3->4, 你应该返回 2->1->4->3.
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    ListNode* swapPairs(ListNode* head) {
        //递归解法
        /*
         递归需要关注几个点:
         1. 返回值
         2. 终止条件
         3. 执行什么内容
         */
        //如果少于2个节点，直接返回，说明交互完成
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        //前....->2->3->后...
        //前....->3->2->后....
        ListNode *next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        //现在新的头变成了next
        return next;
    }
    
    ListNode* swapPairs02(ListNode* head) {
        ListNode *temp ,*ct;
        temp  = new ListNode(0);
        temp->next = head;
        ct = temp;
        while (ct->next && ct->next->next) {
            ListNode *step1,*step2;
            step1 = ct->next;
            step2 = step1->next;
            
            //ct->1->2->3->4 step1指向1,step2指向2
            //ct->2->1->3->4
            step1->next = step2->next;
            step2->next = step1;
            //前两步仅仅交换了"1"和"2"的位置,下面连接ct和后面的部分.
            ct->next = step2;
            
            ct = step1;
        }
        return temp->next;
    }
    
    
    void test_swapPairs(){
        singlyLinkedList ll,l2;
        ll.insertTail(1);
        ll.insertTail(2);
        ll.insertTail(3);
        ll.insertTail(4);
        std::cout << "test_swapPairs" << std::endl;
        swapPairs02(ll.start())->print();
    }
}

#endif /* swapPairs_hpp */
