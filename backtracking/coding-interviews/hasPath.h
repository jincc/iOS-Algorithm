//
//  hasPath.h
//  backtracking
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef hasPath_hpp
#define hasPath_hpp

#include <stdio.h>
/*
 剑指Offer（六十五）：矩阵中的路径
 
 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。 例如 a b c e s f c s a d e e 这样的3 X 4 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。
https://www.nowcoder.com/practice/c61c6999eecb4b8f88a98f66b273a3cc?tpId=13&tqId=11218&tPage=4&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    bool hasPath(char** matrix, int rows, int cols, char* str,int ctrow,int ctcol,bool **states)
    {
        if (ctrow<=0 || ctrow>=rows) {
            return false;
        }
        if (ctcol <=0 || ctcol >= cols) {
            return false;
        }
        if (*str == '\0') {
            return true;
        }
        if (matrix[ctrow][ctcol] == *str) {
            str++;
        }
        return hasPath(matrix, rows, cols, str, ctrow+1, ctcol,states);
    }
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        return false;
    }
}
#endif /* hasPath_hpp */
