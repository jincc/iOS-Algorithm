//
//  main.cpp
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "singlyLinkedList.h"
#include <iostream>
#include "mergeTwoLists.h"
#include "swapPairs.h"
#include "hasCycle.h"
#include "detectCycle.h"
#include "reverseList.h"
#include "isPalindrome.h"
#include "middleNode.h"
#include "removeNthFromEnd.h"
#include "FindKthToTail.h"
#include "ReverseList.h"
#include "printListFromTailToHead.h"
#include "Clone.h"
#include "FindFirstCommonNode.h"
#include "deleteDuplication.h"
#include "deleteDuplicates.h"
#include "addTwoNumbers.h"
#include "getIntersectionNode.h"
#include "printCommonPart.h"
#include "removeLastKthNode.h"
#include "removeMidNode.h"
#include "ReverseLL.h"
#include "ReversePartLL.h"
#include "josephusKill.h"
#include "isPalindrome2.h"
#include "listPartition.h"
#include "copyListWithRand.h"
#include "addList.h"
#include "getIntersectNode.h"
#include "reverseKNodes.h"
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    singlyLinkedList ll;
    ll.insertToHead(3);
    ll.insertToHead(2);
    ll.insertToHead(1);
    //1.2.3
    ll.insertTail(4);
    cout << ll ; //1, 2, 3, 4,
    
    singlyLinkedList::Node *it2 = ll.findByValue(2);
    ll.insertAfter(it2, 5);//1, 2,5, 3, 4,
    ll.insertBefore(it2, 6);//1, 2, 6, 5, 3, 4,
    ll.deleteByNode(2);
    cout << ll; //1, 6, 5, 3, 4,
    
    
#pragma mark - leetcode
    leetcode::test_mergeTwoLists();
    leetcode::test_swapPairs();
    leetcode::test_hasCycle();
    leetcode::test_detectCycle();
    leetcode::test_reverseList();
    leetcode::test_isPalindrome();
    leetcode::test_middleNode();
    leetcode::test_removeNthFromEnd();
    
#pragma mark - code-interviews
    
    codinginterviews::test_FindKthToTail();
    codinginterviews::test_ReverseList();
    codinginterviews::test_deleteDuplication();
    
    
#pragma mark - itinterviews
    itinterviews::test_printCommonPart();
    itinterviews::test_removeLastKthNode();
    itinterviews::test_removeMidNode();
    itinterviews::test_ReverseLL();
    itinterviews::test_ReversePartLL();
    itinterviews::test_josephusKill();
    itinterviews::test_isPalindrome2();
    itinterviews::test_listPartition();
    itinterviews::test_copyListWithRand();
    itinterviews::test_addList();
    itinterviews::test_getIntersectNode();
    itinterviews::test_reverseKNodes();
    return 0;
}
