//
//  main.cpp
//  dp
//
//  Created by junlongj on 2019/7/23.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "knapsack.h"
#include "minPathSum.h"
#include "climbStairs.h"
#include "double11advance.h"
#include "coinChange.h"
#include "levenshtein_distance.h"
#include "pascals_triangle.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    test_double11advance();
    test_knapsack();
    test_coinChange();
    test_levenshtein_distance();
    test_pascals_triangle();
    return 0;
}
