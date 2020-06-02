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
    
    {
        int nums[] = {7,5,6,4,3,2,1};
        printf("%d\n", reversedOrderPairs(nums, 7));
        for(int i=0; i < 7; i++)
            printf(" %d",nums[i]);
    };
    {   
        int nums[] = {7,5,6,4,3,2,1};
        printf("\n%d\n", reversePairs(nums, 7));
        for(int i=0; i < 7; i++)
            printf(" %d",nums[i]);
    };
    return 0;
}
