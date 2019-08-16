//
//  isPalindrome.h
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef isPalindrome_h
#define isPalindrome_h
#include "reverseList.h"

namespace leetcode {
    /*
     234.请判断一个链表是否为回文链表。
     
     示例 1:
     
     输入: 1->2
     输出: false
     示例 2:
     
     输入: 1->2->2->1
     输出: true
     进阶：
     你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/palindrome-linked-list
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    ListNode* findMiddleNode(ListNode *head){
        ListNode *fast,*slow;
        fast = slow = head;
        while (fast && fast ->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    bool isPalindrome(ListNode* head) {
        if (!head)
            return false;
        
        if (!head->next)
            return true;
        
        ListNode *pMid = findMiddleNode(head);
        //翻转
        ListNode *pRev = reverseList(pMid);
        for(;head!=pMid; head=head->next, pRev=pRev->next) {
            if (head->val != pRev->val) {
                return false;
            }
        }
        return true;
    }
    
    void test_isPalindrome(){
        singlyLinkedList ll;
        ll.insertTail(1);
        ll.insertTail(2);
        ll.insertTail(2);
        ll.insertTail(2);
        ll.insertTail(1);
        std::cout << "test_isPalindrome: " << isPalindrome(ll.start())<<std::endl;
    }
}

#endif /* isPalindrome_h */
