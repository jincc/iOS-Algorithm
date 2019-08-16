//
//  detectCycle.h
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef detectCycle_hpp
#define detectCycle_hpp

#include <stdio.h>
#include "singlyLinkedList.h"

namespace leetcode {
    /*
     142.给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
     
     为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
     
     说明：不允许修改给定的链表。
     
      
     
     示例 1：
     
     输入：head = [3,2,0,-4], pos = 1
     输出：tail connects to node index 1
     解释：链表中有一个环，其尾部连接到第二个节点。
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/linked-list-cycle-ii
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    ListNode *fast_,*slow_;
    bool hasCycle_(ListNode *head) {
        fast_ = slow_ = head;
        while (fast_ && fast_->next) {
            slow_ = slow_->next;
            fast_ = fast_->next->next;
            if (slow_ == fast_) {
                return true;
            }
        }
        return false;
    }
    ListNode *detectCycle(ListNode *head) {
        /*
         version1: 可以借助map等结构，
         version2: 先记录快慢指针第一次相遇的地方,当他们再次相遇的时候正好是入口点.
         证明如下:
         设环的长度为R， 头部离环口的距离为x,环口离相聚点为y，有:
         
         V*T = x + y;
         2V*T = x + y + R;
         
         得到VT = R;也就是说慢指针走的距离为环的长度. 也就是 x + y = R;
         当它们再次相遇的时候, 正好在入环口。
         */
        
        //先计算第一次相遇的点
        
        if (!hasCycle_(head)) {
            return nullptr;
        }
        slow_ = head;
        while (slow_ != fast_) {
            slow_ = slow_->next;
            fast_ = fast_->next;
        }
        return slow_;
    }
    
    void test_detectCycle(){
        singlyLinkedList ll;
        ll.insertTail(3);
        ll.insertTail(2);
        ll.insertTail(0);
        ll.insertTail(-4);
        ListNode *l2 = ll.findByValue(2);
        ListNode *l4 = ll.findByValue(-4);
        l4->next = l2;
        
        ListNode *node = detectCycle(ll.start());
        std::cout << "detectCycle------------\n" << node->val << std::endl;
    }
}

#endif /* detectCycle_hpp */
