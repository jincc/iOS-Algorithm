//
//  main.cpp
//  bsearch
//
//  Created by junl on 2019/7/19.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "bsearch.h"
#include "bsearch_findFirstElement.h"
#include "bsearch_findLastElement.h"
#include "searchInRotatedSortedArray.h"
#include "bsearch_findFirstElementGreaterOrEqual.h"
#include "bsearch_findLastElementLessOrEqual.h"
#include "isPerfectSquare.h"
#include "mySqrt.h"
#include "searchRange.h"
#include "powx.h"
#include "search_a_2d_matrix.h"
#include "searchInRotatedSortedArrayII.h"
#include "find_minimum_in_rotated_sorted_array.h"
#include <set>
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "bsearch starting...............\n";
    int nums[] ={1, 4, 5, 9, 12, 19, 21, 28, 31, 36};
    std::cout << bsearch_f1(nums, 10, 12) << std::endl;
    std::cout << bsearch_f2(nums, 10, 0, 9,12) << std::endl;
    int nums2[] = {1,3,4,5,6,8,8,8,11,18};
    std::cout << "bsearch_findFirstElement...............\n";
    std::cout << bsearch_findFirstElement(nums2, 10, 8) << std::endl;//5
    std::cout << bsearch_findLastElement(nums2, 10, 8) << std::endl;//7
    std::cout << bsearch_findLastElement(nums2, 10, 9) << std::endl;//-1
    std::cout << bsearch_findFirstElementGreaterOrEqual(nums2, 10, 7) << std::endl;//5
    std::cout << bsearch_findLastElementLessOrEqual(nums2, 10, 7) << std::endl;//4
    
    
    std::cout << "search in rotate array...............\n";
    
    std::vector<int> a{4,5,6,7,0,1,2};
    std::vector<int> a2{3,1};
    std::cout << search(a, 1) << std::endl;
    
    std::cout << "isPerfectSquare...............\n";
    std::cout << isPerfectSquare(16) << std::endl;
    std::cout << mySqrt(6) << std::endl;
    
    leetcode::test_pow();
    return 0;
}
