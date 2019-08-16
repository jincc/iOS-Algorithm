//
//  reOrderArray.h
//  array
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef reOrderArray_hpp
#define reOrderArray_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（十三）：调整数组顺序使奇数位于偶数前面
 
 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
https://www.nowcoder.com/practice/beb5aa231adc45b2a5dcc5b62c93f593?tpId=13&tqId=11166&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    void reOrderArray(std::vector<int> &array) {
        if (array.empty()) {
            return;
        }
        int i=0;//i保存的是基数的最后一位的位置.
        for (int j=0; j<array.size(); j++) {
            if (array[j] % 2 == 1) {
                //这个位置是基数
                int value = array[j];
                //将i...j-1直接的元素（偶数）向后挪动，然后把value插入到基数序列的末尾。
                for (int k=j-1; j>=1&& k>=i; k--) {
                    array[k+1] = array[k];
                }
                array[i++] = value;
            }
        }
        
    }
    
    void test_reOrderArray(){
        std::cout << "reOrderArray starting......." << std::endl;
        std::vector<int> a{0,1,2,3,4,5,6};
        reOrderArray(a);
        a;
    }
}

#endif /* reOrderArray_hpp */
