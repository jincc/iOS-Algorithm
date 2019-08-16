//
//  removeNthFromEnd.h
//  linkedList
//
//  Created by junlongj on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef removeNthFromEnd_h
#define removeNthFromEnd_h
#include "singlyLinkedList.h"

namespace leetcode {
    /*
     19.给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
     
     示例：
     
     给定一个链表: 1->2->3->4->5, 和 n = 2.
     
     当删除了倒数第二个节点后，链表变为 1->2->3->5.
     说明：
     
     给定的 n 保证是有效的。
     
     进阶：
     
     你能尝试使用一趟扫描实现吗？
     
     在真实的面试中遇到过这道题？
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        if (head == nullptr || n <=0){
            return nullptr;
        }
        //技巧，通过构建哨兵对象，可以极大的降低复杂度。
        ListNode *node = new ListNode(0);
        node->next = head;
        head = node;
        
        ListNode *p1, *p2;
        p1=p2=head;
        for(int i=0; i<n; i++){
            if (p2==nullptr) return nullptr;
            p2=p2->next;
        }
        while (p2->next!=nullptr){
            p2=p2->next;
            p1=p1->next;
        }
        
        p1->next = p1->next->next;
        return head->next;
    }
    void test_removeNthFromEnd(){
        singlyLinkedList ll;
        ll.insertTail(1);
        ll.insertTail(2);
//        ll.insertTail(3);
//        ll.insertTail(4);
//        ll.insertTail(5);
//        ll.insertTail(6);
        std::cout << "test_removeNthFromEnd: " <<std::endl;
        removeNthFromEnd(ll.start(), 2)->print();
    }
}

#endif /* removeNthFromEnd_h */
