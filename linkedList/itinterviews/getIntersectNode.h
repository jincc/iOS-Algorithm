//
//  getIntersectNode.h
//  linkedList
//
//  Created by junl on 2019/11/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef getIntersectNode_hpp
#define getIntersectNode_hpp

#include <stdio.h>
#include "creatlist.h"
#include "ReverseLL.h"
/*
 两个单链表相交的一系列问题.
 
 在本题中，单链表可能有环，也可能无环。给定两个单链表的头节点head1和head2，这两个链表可能相交，也可能不相交。
 请实现一个函数，如果两个链表相交，则返回相交的第一个节点，如果不相交，返回null
 */
namespace itinterviews {
    /*
     分情况处理:
     如果两个单链表都无环,..........
     如果两个单链表都有环,..........
     如果一个有环，一个无环，则不可能相交.
     */
    class getIntersectNode{
    public:
        bool solve(ListNode *head1, ListNode *head2){
            if (!head1 || !head2)
                return false;
            ListNode* loopNode1 = getLoopNode(head1);
            ListNode* loopNode2 = getLoopNode(head2);
            if (loopNode1 != nullptr && loopNode2 != nullptr){
                //如果两个链表都有环，而且loopNode1 == loopNode2,那么交点在环节点之前,即转换为getNoLoopIntersectNode问题
                //如果loopNode1 != loopNode2，那么可能不存在交点，也有可能存在两个交点,类似天线宝宝那两根天线的结构
                return getLoopIntersectNode(head1, loopNode1, head2, loopNode2) != nullptr;
            }else if(loopNode1 == nullptr && loopNode2 == nullptr){
                return getNoLoopIntersectNode(head1, head2) != nullptr;
            }
            return false;
        }
    private:
        //是否有环，如果有环则返回入口地址
        //设置快慢指针，如果无环，那么fast指针一定先到达尾部.如果有环，那么一定在环中的某个节点相遇。
        //假设他们在距离环入口地址y的位置相遇，环的入口地址为x，那么就有如下:v * t = x + y; 2vt = x + R + y; 得出R = x + y;
        //这个时候让快指针从首部重新触发，每次只移动一步，那么快慢指针再移动x步都会可到达环入口地址
        ListNode* getLoopNode(ListNode *head){
            if (!head)
                return nullptr;
            ListNode *fast,*slow;
            fast = slow = head;
            while (fast && fast->next) {
                fast = fast->next->next;
                slow = slow->next;
                if (fast == slow){
                    //存在环
                    fast = head;
                    while (fast != slow) {
                        fast = fast->next;
                        slow = slow->next;
                    }
                    return fast;
                }
            }
            return nullptr;
        }
        int listsize(ListNode *head){
            ListNode *node = head;
            int cnt=0;
            while (node) {
                ++cnt;
                node = node->next;
            }
            return cnt;
        }
        //获取无环链表的相交节点，首先记录两个链表的长度和尾节点，如果尾节点一样，那么肯定相交，如果尾节点不一样则不相交。
        ListNode *getNoLoopIntersectNode(ListNode *head1, ListNode *head2){
            if (!head1 || !head2){
                return nullptr;
            }
            int cnt = 0;
            int cnt2 = 0;
            ListNode *ct = head1;
            ListNode *ct2 = head2;
            while (ct->next != nullptr) {
                cnt++;
                ct = ct->next;
            }
            
            while (ct2->next != nullptr) {
                cnt2++;
                ct2 = ct2->next;
            }
            if (ct != ct2) {
                return nullptr;
            }
            
            ListNode *fast ,*slow;
            fast = cnt>cnt2 ? head1:head2;
            slow = fast == head1 ? head2 : head1;
            int s = cnt > cnt2 ? cnt - cnt2 : cnt2-cnt;
            cnt = 0;
            while (cnt < s) {
                cnt++;
                fast = fast->next;
            }
            while (fast!=nullptr && slow!=nullptr) {
                
                if (fast == slow)
                    return fast;
                fast = fast->next;
                slow = slow->next;
            }
            return nullptr;
        }
        
        ListNode *getLoopIntersectNode(ListNode *head1,ListNode*tail1, ListNode *head2, ListNode*tail2){
            if (!head1 || !head2){
                return nullptr;
            }
            if (tail1 != tail2){
                ListNode *node = tail1->next;
                //如果赚了一圈还没遇到tail2这个交点，证明他们不相交
                while (node != tail1) {
                    if (node == tail2){
                        return node;
                    }
                    node = node->next;
                }
                return nullptr;
            }else{
                int cnt = 0;
                int cnt2 = 0;
                ListNode *ct = head1;
                ListNode *ct2 = head2;
                while (ct!= tail1) {
                    cnt++;
                    ct = ct->next;
                }
                
                while (ct2 != tail2) {
                    cnt2++;
                    ct2 = ct2->next;
                }
                
                ListNode *fast ,*slow;
                fast = cnt>cnt2 ? head1:head2;
                slow = fast == head1 ? head2 : head1;
                int s = cnt > cnt2 ? cnt - cnt2 : cnt2-cnt;
                cnt = 0;
                while (cnt < s) {
                    cnt++;
                    fast = fast->next;
                }
                while (fast != slow) {
                    
                    fast = fast->next;
                    slow = slow->next;
                }
                return fast;
            }
        }
    };
    
    void test_getIntersectNode(){
        std::cout << "------- 两个单链表相交的一系列问题-----------" << std::endl;
        class getIntersectNode so;
        ListNode *head1 ,*head2 , *common, *node;
        common = codinginterviews::creatLists({4,5,6})->next;
        head1 = codinginterviews::creatLists({1,2})->next; //1,2,4,5,6
        node = head1;
        while (node->next) {
            node = node->next;
        }
        node->next = common;

        head2 = codinginterviews::creatLists({3})->next;
        head2->next = common;
        std::cout << "1,2,4,5,6和3,4,5,6是否相交: " << so.solve(head1, head2)<< std::endl ;
        head2->next = nullptr;
        std::cout << "1,2,4,5,6和3是否相交: " << so.solve(head1, head2)<< std::endl ;
        
        
        //构造循环链表
        node = common;
        while (node->next) {
            node = node->next;
        }
        node->next = common;
//        head1->print() ; 1, 2, 4, 5, 6, 4, 5, 6.........
        head2->next = common;
//        head2->print();3, 4, 5, 6, 4, 5, 6...........
        std::cout << "1,2,4,5,6,4,5,6....和3,4,5,6,4,5,6....是否相交: " << so.solve(head1, head2)<< std::endl ;
        
    }
}
#endif /* getIntersectNode_hpp */
