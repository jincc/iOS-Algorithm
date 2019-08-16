//
//  hasCycle.h
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef hasCycle_hpp
#define hasCycle_hpp

#include <stdio.h>
#include "singlyLinkedList.h"
namespace leetcode {
    /*
     141.给定一个链表，判断链表中是否有环。
     
     为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
     
      
     
     示例 1：
     
     输入：head = [3,2,0,-4], pos = 1
     输出：true
     解释：链表中有一个环，其尾部连接到第二个节点。
     
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/linked-list-cycle
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    bool hasCycle(ListNode *head) {
        ListNode *fast,*slow;
        fast = slow = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }
    
    void test_hasCycle(){
        singlyLinkedList ll;
        ll.insertTail(3);
        ll.insertTail(2);
        ll.insertTail(0);
        ll.insertTail(-4);
        ListNode *l2 = ll.findByValue(2);
        ListNode *l4 = ll.findByValue(-4);
        l4->next = l2;
        std::cout << "test_hasCycle: " <<  hasCycle(ll.start()) << std::endl;
 
    }
}

#endif /* hasCycle_hpp */
