//
//  addList.h
//  linkedList
//
//  Created by junl on 2019/11/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef addList_hpp
#define addList_hpp

#include <stdio.h>
#include "creatlist.h"
#include <stack>
/*
 两个单链表生成相加链表
 例如：链表1位9->3->7,链表2位6->3，结果链表为1->0->0->0
 */
namespace itinterviews {
    class addList{
    public:
        /*
         思路：利用栈后进先出的结构O(N+M),O(N+M)
         */
        ListNode *solve(ListNode * head1, ListNode *head2){
            if (!head1 || !head2)
                return nullptr;
            std::stack<int> stk1;
            std::stack<int> stk2;
            ListNode *node = head1;
            while (node) {
                stk1.push(node->val);
                node=node->next;
            }
            node = head2;
            while (node) {
                stk2.push(node->val);
                node=node->next;
            }
            int flag=0;
            ListNode *pre = nullptr;
            node = nullptr;
            while (!stk1.empty() || !stk2.empty()) {
                int n1= 0, n2= 0;
                if (!stk1.empty()) {
                    n1 = stk1.top();
                    stk1.pop();
                }
                if (!stk2.empty()){
                    n2 = stk2.top();
                    stk2.pop();
                }
                int n = n1+n2+flag;
                flag = n / 10;
                pre = node;
                node = new ListNode(n%10);
                node->next = pre;
            }
            if (flag){
                pre = node;
                node = new ListNode(flag);
                node->next = pre;
            }
            return node;
        }
    };
    
    /*
     思路:
     通过反转两个链表，可以节省掉栈空间的消耗
     */
    class addList2{
    public:
        ListNode *solve(ListNode *head1,ListNode *head2){
            if (!head1 || !head2)
                return nullptr;
            head1 = reverse(head1);
            head2 = reverse(head2);
            ListNode *ct,*pre;
            ct = pre = nullptr;
            int co=0;
            ListNode *node1 = head1;
            ListNode *node2 = head2;
            while (node1 || node2) {
                int n1 = 0;
                int n2 = 0;
                if (node1){
                    n1 = node1->val;
                    node1 = node1->next;
                }
                if (node2){
                    n2 = node2->val;
                    node2 = node2->next;
                }
                int n = n1 + n2 + co;
                co = n/10;
                pre = ct;
                ct = new ListNode(n%10);
                ct->next = pre;
            }
            if (co){
                pre = ct;
                ct = new ListNode(co);
                ct->next = pre;
            }
            head1 = reverse(head1);
            head2 = reverse(head2);
            return ct;
        }
    private:
        ListNode* reverse(ListNode *head){
            ListNode *pre,*ct,*next;
            pre=head;
            ct=pre->next;
            pre->next=nullptr;
            while (ct) {
                next = ct->next;
                ct->next = pre;
                pre = ct;
                ct = next;
            }
            return pre;
        }
        
    };
    
    void test_addList(){
        std::cout << "---两个单链表生成相加链表---------" << std::endl;
//        class addList so;
        class addList2 so;
        ListNode *head1 = codinginterviews::creatLists({9,3,7})->next;
        ListNode *head2 = codinginterviews::creatLists({6,3})->next;
        so.solve(head1, head2)->print();
    }
}

#endif /* addList_hpp */
