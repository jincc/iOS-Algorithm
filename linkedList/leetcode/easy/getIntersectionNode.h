//
//  getIntersectionNode.h
//  linkedList
//
//  Created by junlongj on 2019/8/10.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef getIntersectionNode_hpp
#define getIntersectionNode_hpp

#include <stdio.h>
#include <math.h>
/*
 编写一个程序，找到两个单链表相交的起始节点。

 */

namespace leetcode{
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int sizeA,sizeB;
        sizeA=0;sizeB=0;
        ListNode *ctA= headA;
        while(ctA){
            sizeA++;
            ctA=ctA->next;
        }
        ListNode *ctB=headB;
        while(ctB){
            sizeB++;
            ctB=ctB->next;
        }
        ListNode *ll = sizeA>sizeB?headA:headB;
        ListNode *ll2 = ll==headA?headB:headA;
        int count=0;
        int step=fabs(sizeA-sizeB);
        while(count < step){
            ll=ll->next;
            count++;
        }
        
        while(ll&&ll2){
            if (ll == ll2)
                return ll;
            ll=ll->next;
            ll2=ll2->next;
        }
        return nullptr;
    }
}
#endif /* getIntersectionNode_hpp */
