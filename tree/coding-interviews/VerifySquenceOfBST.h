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
    bool verifyPostorder(int* postorder, int postorderSize){
        if (postorder == NULL || postorderSize == 0) return true;

        int rootvalue = postorder[postorderSize-1];
        int i, j;
        for(i=0;i < postorderSize-1; i++){
            if (postorder[i] > rootvalue)
                break;
        }
        for(j = i; j < postorderSize-1; j++){
            if (postorder[j] < rootvalue)
                return false;
        }
        int result = 1;
        if (i > 0)
            result = verifyPostorder(postorder, i);
        if (result && i < postorderSize-1) //如果左子树已经不满足，那么久没有必要监测右子树了.
            result &= verifyPostorder(postorder+i, postorderSize-i-1);

        return result;
    }
    void test_verifyPostorder(){
        int post[] = {1,3,2,6,5};
        int result = verifyPostorder(post, 5);
        printf("test_verifyPostorder: %d\n",result);
    }
}
#endif /* VerifySquenceOfBST_hpp */
