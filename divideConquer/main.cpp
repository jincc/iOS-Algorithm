//
//  main.cpp
//  divideConquer
//
//  Created by junlongj on 2019/7/25.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "reversedOrderPairs.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    cout << "数组里面的逆序对 starting.........." << endl;
    
    int nums[] = {3,1,2,7,4,3};
//    reversedOrderPairs(nums, 6, 0, 5);
    cout << reversedOrderPairs(nums, 6) << endl;
    return 0;
}
