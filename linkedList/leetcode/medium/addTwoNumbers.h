//
//  addTwoNumbers.h
//  linkedList
//
//  Created by junlongj on 2019/8/15.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef addTwoNumbers_hpp
#define addTwoNumbers_hpp

#include <stdio.h>
/*
 2.两数相加
 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 
 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
 
 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 
 示例：
 
 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 输出：7 -> 0 -> 8
 原因：342 + 465 = 807
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/add-two-numbers
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1 || !l2) return nullptr;
        int flag = 0;
        ListNode *head = new ListNode(0);
        ListNode *ct = head;
        while(l1 || l2){
            int a1=0,a2=0;
            if (l1){
                a1=l1->val;
                l1=l1->next;
            }
            if (l2){
                a2=l2->val;
                l2=l2->next;
            }
            int v = a1 + a2 + flag;
            flag = v/10;
            ListNode *node = new ListNode(v%10);
            ct->next=node;
            ct=ct->next;
        }
        if (flag)
            ct->next = new ListNode(flag);
        return head->next;
    }
}
#endif /* addTwoNumbers_hpp */
