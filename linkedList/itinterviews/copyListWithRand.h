//
//  copyListWithRand.h
//  linkedList
//
//  Created by junl on 2019/11/12.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef copyListWithRand_hpp
#define copyListWithRand_hpp

#include <stdio.h>
#include "creatlist.h"
#include <map>
/*
 复制含有随机指针节点的链表.
 
 进阶：不使用额外的数据结构，只用有限的几个变量，且在时间复杂度为O（n）内完成。
 总结：
 
 两种解析关键点在于：如果通过原节点找到copy的新节点，这样才能设置rand节点值。方法一是通过hashmap，方法二比较取巧，通过构建一个特殊链表.
 */
namespace itinterviews {
    class RNode{
    public:
        int val;
        RNode *next;
        RNode *rand;
        RNode() = delete;
        RNode(int value):val(value),next(nullptr),rand(nullptr){};
    };
    /*
     思路: 关键点在于如何处理rand节点，rand节点是不能new出来的，不然就和新链表的节点对应不上。
     处理: 借助hashmap,O(N),O(N)
     */
    class copyListWithRand{
    public:
        RNode *solve(RNode *head){
            if (!head)
              return head;
            std::map<RNode *,RNode *> m;
            RNode *node = head;
            //一一映射保存到map中，此时next和rand都还没赋值
            while (node) {
                m[node] = new RNode(node->val);
                node = node->next;
            }
            node = head;
            while (node) {
                m[node]->next = m[node->next];
                m[node]->rand = m[node->rand];
                node = node->next;
            }
            return m[head];
        };
    };
    /*
     思路：比如原链表为1->2->3，构建出新链接为1-> 1‘ -> 2 -> 2' -> 3-> 3'，这样可以非常容易的找到原链表节点和新链表节点之间的关系.即:
        node源->next即为node新
     */
    class copyListWithRand_advance{
    public:
        RNode *solve(RNode *head){
            if (!head)
                return head;
            RNode *node = head;
            RNode *next;
            //构建1-> 1‘ -> 2 -> 2' -> 3-> 3'
            while (node) {
                next = node->next;
                node->next = new RNode(node->val);
                node->next->next = next;
                node = next;
            }
            
            //处理rand节点
            node = head;
            while (node) {
                next = node->next->next;//跳过复制的节点
                if (node->rand){
                    node->next->rand = node->rand->next;
                }
                node = next;
            }
            //删除多余节点
            RNode *result = head->next;
            node = head;
            RNode *copyNode;
            while (node) {
                next = node->next->next;
                copyNode = node->next;
                node->next = next;
                copyNode->next = next ? next->next : nullptr;
                node = node->next;
            }
            return result;
        }
    };
    
    void test_copyListWithRand(){
        std::cout << "------复制含有随机指针节点的链表.----------" << std::endl;
        RNode *head = new RNode(1);
        RNode *head2 = new RNode(2);
        RNode *head3 = new RNode(3);
        head->next = head2;
        head->rand = head3;
        head2->next = head3;
        head3->rand = head;
        
//        class copyListWithRand so;
        class copyListWithRand_advance so;
        head = so.solve(head);
        head;
    }
}


#endif /* copyListWithRand_hpp */
