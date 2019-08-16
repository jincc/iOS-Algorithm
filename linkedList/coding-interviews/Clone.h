//
//  Clone.h
//  linkedList
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef Clone_hpp
#define Clone_hpp

#include <stdio.h>
#include <map>
/*
 剑指Offer（二十五）：复杂链表的复制

 输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
 https://www.nowcoder.com/practice/f836b2c43afc4b35ad6adc41ec941dba?tpId=13&tqId=11178&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    struct RandomListNode {
        int label;
        struct RandomListNode *next, *random;
        RandomListNode(int x) :
        label(x), next(NULL), random(NULL) {
        }
    };
    
    RandomListNode* Clone(RandomListNode* pHead)
    {
        RandomListNode *root = new RandomListNode(0);
        RandomListNode *newct = root;
        RandomListNode *ct = pHead;
        std::map<int , RandomListNode *> maps;
        //第一次循环构建出单链表
        while (ct) {
            newct->next = new RandomListNode(ct->label);
            maps[ct->label] = newct->next;
            newct = newct->next;
            ct = ct->next;
        }
        //第二次循环构建random节点
        ct = pHead;
        newct = root->next;
        while (ct) {
            if (ct->random) {
                newct->random = maps[ct->random->label];
            }
            ct = ct->next;
            newct = newct->next;
        }
        return root->next;
    }
}


#endif /* Clone_hpp */
