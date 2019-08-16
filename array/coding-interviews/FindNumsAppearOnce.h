//
//  FindNumsAppearOnce.h
//  array
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef FindNumsAppearOnce_hpp
#define FindNumsAppearOnce_hpp

#include <stdio.h>
#include <vector>
#include <map>
/*
 剑指Offer（四十）：数组中只出现一次的数字

 一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
https://www.nowcoder.com/practice/e02fdb54d7524710a7d664d082bb7811?tpId=13&tqId=11193&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    void FindNumsAppearOnce(std::vector<int> data,int* num1,int *num2) {
        std::map<int,bool> mm;
        for(auto it = data.begin();it!=data.end();it++){
            auto find = mm.find(*it);
            if (find!= mm.end()) {
                mm.erase(find);
            }else{
                mm[*it]=true;
            }
        }
        if (mm.size() == 2) {
            auto begin = mm.begin();
            *num1 = begin->first;
            begin++;
            *num2 = begin->first;
        }
    }
}
#endif /* FindNumsAppearOnce_hpp */
