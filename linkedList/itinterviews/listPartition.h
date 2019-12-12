//
//  listPartition.h
//  linkedList
//
//  Created by junl on 2019/11/11.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef listPartition_hpp
#define listPartition_hpp

#include <stdio.h>
#include "creatlist.h"
#include <stack>
/*
 将单向链表按某值划分成左边小，中间相等，右边大的形式.除了这个要求外，对调整后的节点顺序没有更多的要求.
 
 进阶问题:
 1. 在左中右三个部分的内部也要做顺序要求，要求每个部分和之前链表中节点的先后次序一致.
 2. 如果链表长度为N，时间复杂度请打到O(N),额外空间复杂度请打到O(1)
 */
namespace itinterviews {
    class listPartition{
    public:
        /*
         思路：首先将所有节点放入到一个数组中，然后对数组进行排序:
            小的放左边，大的防右边，最后把他们连接起来
         */
        ListNode *solve(ListNode *head, int pivot){
            if (head == nullptr)
                return head;
            //获取链表长度，构建节点数组
            int len = 0;
            ListNode *node = head;
            while (node) {
                len++;
                node = node->next;
            }
            ListNode* nodes[len];
            node = head;
            for (int i=0; i<len; i++) {
                nodes[i] = node;
                node = node->next;
            }
            //对其排序
            sort(nodes, len, pivot);
            //最后把所有节点连接起来
            int i=0;
            for (; i<len-1; i++) {
                nodes[i]->next = nodes[i+1];
            }
            nodes[i]->next = nullptr;
            return nodes[0];
        }
    private:
        void sort(ListNode* nodes[], int len, int pivot){
            int index,start,end;
            index = 0;
            start = -1;
            end = len;
            
            //小的放左边，相等的不变，大的放右边
            while (index != end) {
                if (nodes[index]->val > pivot) {
                    swap(nodes, index, --end);
                }else if (nodes[index]->val == pivot){
                    index++;
                }else{
                    swap(nodes, index++, ++start);
                }
            }
        }
        
        void swap(ListNode* nodes[],int a, int b){
            ListNode *tmp = nodes[a];
            nodes[a] = nodes[b];
            nodes[b] = tmp;
            for (int i =0; i< 5; i++) {
                std::cout << nodes[i]->val << ", ";
            }
            std::cout << std::endl;
            
        }
    };
    
    class listPartition_advance{
    public:
        /*
         思路：
         进阶问题:将链表分为三个子链表，最后链接起来即可
         */
        ListNode *solve(ListNode *head, int pivot){
            if (head == nullptr)
                return head;
            ListNode *smallhead,*smalltail,*equalhead,*equaltail,*bighead,*bigtail;
            smallhead = smalltail = nullptr;
            equalhead = equaltail = nullptr;
            bighead = bigtail = nullptr;
            ListNode *next;
            while (head) {
                next = head->next;
                head->next=nullptr;
                if (head->val < pivot) {
                    if (!smallhead){
                        smallhead = smalltail = head;
                    }else{
                        smalltail->next = head;
                        smalltail = head;
                    }
                }else if (head->val == pivot){
                    if (!equalhead){
                        equalhead =equaltail = head;
                    }else{
                        equaltail->next = head;
                        equaltail = head;
                    }
                }else{
                    if (!bighead){
                        bighead = bigtail = head;
                    }else{
                        bigtail->next = head;
                        bigtail = head;
                    }
                }
                head = next;
            }
            
            if (smalltail){
                smalltail->next = equalhead;
                equaltail = equaltail ?: smalltail;
            }
            if (equaltail){
                equaltail->next = bighead;
            }
            return smallhead ?: (equalhead?:bighead);
        }
        
    };
    
    void test_listPartition(){
        std::cout << "----将单向链表按某值划分成左边小，中间相等，右边大的形式----" << std::endl;
        ListNode *head = codinginterviews::creatLists({9,0,4,5,1})->next;
//        class listPartition so;
        class listPartition_advance so;
        head = so.solve(head, 4);
        head->print();
    }
}

#endif /* listPartition_hpp */
