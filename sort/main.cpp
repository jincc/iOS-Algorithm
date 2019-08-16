//
//  main.cpp
//  sort
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "bubbleSort.h"
#include "insertSort.h"
#include "selectSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "kthSmallest.h"
#include "countingSort.h"
#include "heapSort.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int num[] = {3, 4, 2, 1, 5, 6, 7, 8};
    
#pragma mark - o(n^2)
//    bubbleSort(num, 8);
//    insertSort(num,8);
//    selectSort(num, 8);
    
#pragma mark -
    
//    mergeSort(num, 8);
//    quickSort(num, 8);
//    int n = kthSmallest(num, 8, 0, 7, 5);
    
//    countingSort(num, 8);
    heapSort(num, 8);
    return 0;
}
