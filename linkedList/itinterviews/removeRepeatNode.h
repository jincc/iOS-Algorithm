//
//  removeRepeatNode.h
//  linkedList
//
//  Created by junl on 2019/12/16.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef removeRepeatNode_hpp
#define removeRepeatNode_hpp

#include <stdio.h>
#include "creatlist.h"
#include <set>
namespace itinterviews {
    /*
     给定一个无序单链表头节点head，删除其中值重复的节点.
     例如1,2,3,3,4,4,2,1,1,null,删除值重复的节点之后为1,2,3,4,null.
     请按要求实现两种方法：
     方法1：如果链表长度为N，时间复杂度打到O(N)
     方法2：额外空间复杂度为O(1)
     */
    
    class removeRepeatNode{
    public:
        void solve(ListNode *head){
            if (!head)
                return ;
            std::set<int> mm;
            ListNode *ct = head;
            mm.insert(ct->val);
            while (ct && ct->next) {
                int val = ct->next->val;
                if (mm.find(val) != mm.end()) {
                    //find and jump
                    ct->next = ct->next->next;
                }else{
                    mm.insert(val);
                    ct = ct->next;
                }
            }
        }
    };
    
    /*
     要求空间复杂度为O(1),时间复杂度为O(n2)
     方法：类似选择排序，选中当前第i个节点m，依次删除后续值为节点m值的节点.
     */
    class removeRepeatNode2{
    public:
        void solve(ListNode *head){
            if (!head)
                return ;
            ListNode *ct = head;
            while (ct) {
                int val = ct->val;
                ListNode *loopnode = ct;
                while (loopnode && loopnode->next) {
                    if (loopnode->next->val == val) {
                        loopnode->next = loopnode->next->next;
                    }else{
                        loopnode = loopnode->next;
                    }
                }
                ct = ct->next;
            }
        }
    };
    
    void test_removeRepeatNode(){
        std::cout << "给定一个无序单链表头节点head，删除其中值重复的节点" << std::endl;
        ListNode *head = codinginterviews::creatLists({1,2,3,3,4,4,2,1,1})->next;
        class removeRepeatNode2 so;
        so.solve(head);
        head->print();
    }
}

#endif /* removeRepeatNode_hpp */
