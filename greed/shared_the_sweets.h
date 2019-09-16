//
//  shared_the_sweets.h
//  greed
//
//  Created by junl on 2019/9/9.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef shared_the_sweets_hpp
#define shared_the_sweets_hpp

#include <stdio.h>
#include <vector>

using namespace std;

/**
 分糖果. 把m个糖果分给n个孩子，只有当糖果的大小大于孩子期望的大小时，孩子才会得到满足.

 @param sweets m个糖果分别的大小
 @param childwants 孩子们每个人期望的糖果大小.
 @return 能得到满足的孩子数量
 */
int shared_the_sweets(vector<int> &sweets, vector<int> &childwants){
    /*
     限制条件：一共只有m个糖果。
     期望值: 希望得到满足的孩子数量最大.
     贪心思想: 要求糖果大小越小的孩子越容易满足，对于期望值来说，满足它跟满足要大糖果的孩子是一样的，所以我们优先满足它。
     */
    sort(sweets.begin(), sweets.end());
    sort(childwants.begin(), childwants.end());
    int count = 0;
    for (int i=0,j=0; i<childwants.size() && j<sweets.size();j++) {
        //对于每个糖果，我们先满足需求最小的孩子，如果得到满足，成就+1，不能满足的话，用下一个糖果试试。
        if (sweets[j] >= childwants[i]) {
            count++;//孩子得到了满足
            i++;
        }else{
        }
    }
    return count;
}

#endif /* shared_the_sweets_hpp */
