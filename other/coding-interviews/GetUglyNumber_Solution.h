//
//  GetUglyNumber_Solution.h
//  other
//
//  Created by junl on 2019/8/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef GetUglyNumber_Solution_hpp
#define GetUglyNumber_Solution_hpp

#include <stdio.h>
/*
 剑指Offer（三十三）：丑数
 把只包含质因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含质因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
https://www.nowcoder.com/practice/6aa9e04fc3794f68acf8778237ba065b?tpId=13&tqId=11186&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    int GetUglyNumber_Solution(int index) {
        /*
         丑数 = 另一个丑数 * (2/3/5), 所以我们需要构建一个排序的丑数数组，然后依次把之前丑数列表某个丑数来乘以2/3/5，取最小的一个.
         */
        if (index <=0) return 0;
        int uglys[index];
        memset(uglys, 0, sizeof(uglys));
        uglys[0]=1;
        int index2 = 0;
        int index3 = 0;
        int index5 = 0;
        int i = 1;
        while (i < index) {
            int new_ugly2 = uglys[index2] * 2;
            int new_ugly3 = uglys[index3] * 3;
            int new_ugly5 = uglys[index5] * 5;
            int min = std::min(new_ugly5, std::min(new_ugly2, new_ugly3));
            uglys[i++] = min;
            
            if (min == new_ugly2) { //因为之前的丑数*2已经被放进排序数组里了，所以需要新增下标，这样下次将会比较新值.
                index2++;
            }
            if (min == new_ugly3){
                index3++;
            }
            if (min == new_ugly5){
                index5++;
            }
        }
        return uglys[index-1];
    }
    
    void test_GetUglyNumber_Solution(){
        std::cout << "GetUglyNumber_Solution starting......." << std::endl;
        std::cout << GetUglyNumber_Solution(10) << std::endl;
    }
}
#endif /* GetUglyNumber_Solution_hpp */
