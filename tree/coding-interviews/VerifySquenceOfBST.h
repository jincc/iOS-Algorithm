//
//  VerifySquenceOfBST.h
//  tree
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef VerifySquenceOfBST_hpp
#define VerifySquenceOfBST_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（二十三）：二叉搜索树的后序遍历序列
 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
https://www.nowcoder.com/practice/a861533d45854474ac791d90e447bafd?tpId=13&tqId=11176&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    /*
     后序遍历顺序：左右根.
     思路：先找到左子树和右子树的分界线，然后递归判断是否满足条件
     */
    bool VerifySquenceOfBST(std::vector<int> sequence,int start,int end) {
        if (sequence.empty() || start > end) {
            return false;
        }
        int tail = sequence[end];
        int i = start;
        //找到左右子树分界线
        for (; i < end; i++) {
            if (sequence[i] > tail) {
                break;
            }
        }
        //判断i之后的元素是否都比tail大.
        for (int j=i; j<end; j++) {
            if (sequence[j] < tail) {
                return false;
            }
        }
        bool leftbst = true;
        if (start <= i-1){
            leftbst =  VerifySquenceOfBST(sequence, start, i-1);
        }
        bool rightbst = true;
        if (i <= end - 1) {
            rightbst = VerifySquenceOfBST(sequence, i, end-1);
        }
        return leftbst && rightbst;
    }
    bool VerifySquenceOfBST(std::vector<int> sequence) {
        return VerifySquenceOfBST(sequence, 0, sequence.size()-1);
    }
}
#endif /* VerifySquenceOfBST_hpp */
