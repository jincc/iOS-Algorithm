//
//  printCommonPart.h
//  linkedList
//
//  Created by junl on 2019/10/27.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef printCommonPart_hpp
#define printCommonPart_hpp

#include <stdio.h>
#include "creatlist.h"

/*
 给定两个有序链表的头指针head1和head2，打印两个链表的公共部分
 */

namespace itinterviews {
    class printCommonPart{
    public:
        void solve(ListNode *head1, ListNode *head2){
            while (head1 && head2) {
                if (head1->val == head2->val) {
                    std::cout << head1->val << ", ";
                    head1 = head1->next;
                    head2 = head2->next;
                }else if (head1->val < head2->val){
                    head1 = head1->next;
                }else{
                    head2 = head2->next;
                }
            }
            std::cout << std::endl;
        }
    };
    
    void test_printCommonPart(){
        std::cout << "---给定两个有序链表的头指针head1和head2，打印两个链表的公共部分----" << std::endl;
        class printCommonPart so;
        ListNode *head1 =  codinginterviews::creatLists({2,4,6,8})->next;
        ListNode *head2 = codinginterviews::creatLists({2,3,4})->next;
        so.solve(head1, head2);
    }
}


#endif /* printCommonPart_hpp */
