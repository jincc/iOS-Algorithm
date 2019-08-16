//
//  MoreThanHalfNum_Solution.h
//  array
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef MoreThanHalfNum_Solution_hpp
#define MoreThanHalfNum_Solution_hpp

#include <stdio.h>
#include <vector>
#include <stack>
/*
 剑指Offer（二十八）：数组中出现次数超过一半的数字
 
 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
 https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=13&tqId=11181&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    int MoreThanHalfNum_Solution(std::vector<int> numbers) {
        int temp = numbers[0];
        int markcount = 1;
        for (int i=1; i<numbers.size(); i++) {
            if (markcount == 0) {
                temp = numbers[i];
                markcount =1;
            }else if (temp != numbers[i]){
                markcount--;
            }else{
                markcount++;
            }
        }
        int result = temp;
        int count = 0;
        for (int i=0; i<numbers.size(); i++) {
            if (numbers[i] == result) {
                count++;
            }
        }
        if (count > numbers.size()/2) {
            return result;
        }
        return 0;
    }
    
    void test_MoreThanHalfNum_Solution(){
        std::vector<int> a{1,2,3,2,4,2,5,2,3};
        std::cout << "test_MoreThanHalfNum_Solution starting........" << std::endl;
        std::cout << MoreThanHalfNum_Solution(a) << std::endl;
    }
}
#endif /* MoreThanHalfNum_Solution_hpp */
