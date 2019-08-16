//
//  Find.h
//  array
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef Find_hpp
#define Find_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（一）：二维数组中的查找
 
 在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&tqId=11154&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    /*
     */
    bool Find(int target, std::vector<std::vector<int> > &array, int row,int column) {
        if (row < 0 || column >= array[0].size()) {
            return false;
        }
        int it = array[row][column];
        if (it == target) {
            return true;
        }else if (it < target){
            return Find(target, array, row, column+1);
        }else{
            return Find(target, array, row-1, column);
        }
    }
    bool Find(int target, std::vector<std::vector<int> > array) {
        return Find(target, array, array.size()-1, 0);
    }
    
    void test_find(){
        std::vector<std::vector<int> > v{{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
        std::cout << "test_find starting........" <<std::endl;
        std::cout << Find(9, v) << std::endl;
    }
}
#endif /* Find_hpp */
