//
//  middleNode.h
//  linkedList
//
//  Created by junlongj on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef middleNode_h
#define middleNode_h
#include "singlyLinkedList.h"

namespace leetcode {
    /*
     876.给定一个带有头结点 head 的非空单链表，返回链表的中间结点。
     
     如果有两个中间结点，则返回第二个中间结点。
     
      
     
     示例 1：
     
     输入：[1,2,3,4,5]
     输出：此列表中的结点 3 (序列化形式：[3,4,5])
     返回的结点值为 3 。 (测评系统对该结点序列化表述是 [3,4,5])。
     注意，我们返回了一个 ListNode 类型的对象 ans，这样：
     ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, 以及 ans.next.next.next = NULL.
     示例 2：
     
     输入：[1,2,3,4,5,6]
     输出：此列表中的结点 4 (序列化形式：[4,5,6])
     由于该列表有两个中间结点，值分别为 3 和 4，我们返回第二个结点。
      
     
     提示：
     
     给定链表的结点数介于 1 和 100 之间。
     在真实的面试中遇到过这道题？
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/middle-of-the-linked-list
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    
    ListNode* middleNode(ListNode* head) {
        if (!head->next) {
            return head;
        }
        ListNode *fast,*slow;
        fast = slow = head;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (fast->next) {
            return slow->next;
        }
        return slow;
    }
    void test_middleNode(){
        singlyLinkedList ll;
        ll.insertTail(1);
        ll.insertTail(2);
        ll.insertTail(3);
        ll.insertTail(4);
        ll.insertTail(5);
        std::cout << "test_middleNode: " << middleNode(ll.start())->val <<std::endl;
    }
}

#endif /* middleNode_h */
