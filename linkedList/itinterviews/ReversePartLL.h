//
//  ReversePartLL.h
//  linkedList
//
//  Created by junl on 2019/10/31.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef ReversePartLL_hpp
#define ReversePartLL_hpp

#include <stdio.h>
#include "creatlist.h"
#include "ReverseLL.h"
/*
 给定一个单向链表的头结点head，以及链各个整数from和to，在单链表上把第from个节点到第to个节点这一部分进行翻转.
 
 1->2->3->4->5,from=2,to=4
 1->4->3->2->5
 
 
 1->2->3, from=1,to=3
 3->2->1
 
 */
namespace itinterviews {
    class ReversePartLL{
    public:
        /*
         思路:
         将整个链表分成三部分:
         part1，part2，part3
         part1和part3不需要翻转，part2需要翻转，所以需要找到几个节点的位置:第一个是part1的末尾，第二个是part2的开始和结尾节点，最后把他们连接起来.
         */
        ListNode *solve_bad(ListNode *head,int from,int to){
            if (!head || from < 1 || to < 1 || to <= from) {
                return head;
            }
            
            ListNode *part1,*part2,*part3,*ct;
            part1 = part2 = part3 = nullptr;
            ct = head;
            int index = 1;
            while (ct) {
                //1~from-1这部分链表不会被反转
                if (index == from - 1) {
                    part1 = ct;
                }else if (index == from){
                    //这部分的链表需要被反转
                    part2 = ct;
                }else if(index == to){
                    //to后的不需要被反转
                    part3 = ct->next;
                    ct->next = nullptr;
                    break;
                }
                ct = ct->next;
                index++;
            }
            ReverseLL r;
            
            ListNode *part2Tail = part2;
            part2 = r.solveSL(part2);
            if (part1) {
                part1->next = part2;
                part2Tail->next = part3;
                return head;
            }else{
                part2Tail->next = part3;
                return part2;
            }
        };
        
        ListNode *solve(ListNode *head,int from,int to){
            if (!head || from < 1 || to < 1 || to <= from) {
                return head;
            }
            ListNode *fPre,*tPos,*node;
            fPre = tPos = nullptr;
            node = head;
            int len = 0;
            while (node) {
                len++;
                if (len == from-1) {
                    fPre = node;
                }else if (len == to + 1){
                    tPos = node;
                }
                node = node->next;
            }
            
            //fpre之前的不需要翻转，之后的需要翻转
            node = fPre ? fPre->next : head;
            ListNode *n1,*n2;
            n1 = node->next;
            node->next = tPos;
            while (n1 != tPos) {
                n2 = n1->next;
                n1->next = node;
                node = n1;
                n1 = n2;
            }
            if (fPre) {
                fPre->next = node;
                return head;
            }else{
                return node;
            }
        }
    };
    
    
    void test_ReversePartLL(){
        std::cout << "--------test_ReverseLL---------" << std::endl;
        ListNode *head = codinginterviews::creatLists({1,2,3,4,5})->next;
        head->print();
        class ReversePartLL so;
        so.solve(head,2,5)->print();
    
    }
}

#endif /* ReversePartLL_hpp */
