//
//  rectCover.h
//  recursion
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef rectCover_hpp
#define rectCover_hpp

#include <stdio.h>
/*
 剑指Offer（十）：矩形覆盖
 我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
https://www.nowcoder.com/practice/72a5a919508a4251859fb2cfb987a0e6?tpId=13&tqId=11163&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    /*
     这个问题实际上就是Fibonacci数列的问题。
     就拿2*5的格子来说，定义为f(5).第一行我们可以顺着放，那么f5=f(4).
     如果第一行我们横着放，占用了两格，那么f5=f3;
     所以f5=f4+f3.
     */
    int rectCover(int n) {
        int f0,f1,f2;
        f0 = 0;
        f1 = 1;
        if (n == 0) return f0;
        if (n == 1) return f1;
        for (int i=2; i<=n; i++) {
            f2 = f0+f1;
            f0 = f1;
            f1 = f2;
        }
        return f2;
    }
}

#endif /* rectCover_hpp */
