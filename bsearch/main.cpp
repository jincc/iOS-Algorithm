//
//  main.cpp
//  bsearch
//
//  Created by junl on 2019/7/19.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "bsearch.h"
#include "searchInRotatedSortedArray.h"
#include "isPerfectSquare.h"
#include "mySqrt.h"
#include "searchRange.h"
#include <set>
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "bsearch starting...............\n";
    int nums[] ={1, 4, 5, 9, 12, 19, 21, 28, 31, 36};
    std::cout << bsearch_f1(nums, 10, 12) << std::endl;
    std::cout << bsearch_f2(nums, 10, 0, 9,12) << std::endl;
    int nums2[] = {1,3,4,5,6,8,8,8,11,18};
    std::cout << "bsearch_findFirstElement...............\n";
    std::cout << bsearch_findFirstElement(nums2, 10, 8) << std::endl;
    std::cout << bsearch_findLastElement(nums2, 10, 8) << std::endl;
    std::cout << bsearch_findLastElement(nums2, 10, 9) << std::endl;
    std::cout << bsearch_findFirstElementGreaterOrEqual(nums2, 10, 7) << std::endl;
    std::cout << bsearch_findLastElementLessOrEqual(nums2, 10, 7) << std::endl;
    
    
    std::cout << "search in rotate array...............\n";
    
    std::vector<int> a{4,5,6,7,0,1,2};
    std::vector<int> a2{3,1};
    std::cout << search(a, 1) << std::endl;
    
    std::cout << "isPerfectSquare...............\n";
    std::cout << isPerfectSquare(16) << std::endl;
    std::cout << mySqrt(6) << std::endl;
    return 0;
}
