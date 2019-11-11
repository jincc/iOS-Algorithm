//
//  creatlist.h
//  linkedList
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef creatlist_hpp
#define creatlist_hpp

#include <stdio.h>
#include <vector>

namespace codinginterviews {
    ListNode *creatLists(const std::vector<int> &s){
        ListNode *root = new ListNode(0);
        ListNode *node = root;
        auto it = s.begin();
        while (it != s.end()) {
            node->next = new ListNode(*it);
            node = node->next;
            it++;
        }
        return root;
    }
    DoubleNode *creatDoubleLists(const std::vector<int> &s){
        DoubleNode *root = new DoubleNode(0);
        DoubleNode *node = root;
        auto it = s.begin();
        while (it != s.end()) {
            node->next = new DoubleNode(*it);
            node->next->pre = node;
            node = node->next;
            it++;
        }
        return root;
    }
}

#endif /* creatlist_hpp */
