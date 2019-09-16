//
//  main.cpp
//  greed
//
//  Created by junl on 2019/9/9.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "shared_the_sweets.h"
#include "coin_dispenser.h"
#include "region_overlapping.h"
#include "jump_game.h"
#include "gas_station.h"
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<int> childwants{5,10,2,9,15,9};
    vector<int> sweets{6,1,20,3,8};
    int sharecount = shared_the_sweets(sweets, childwants);
    cout << "分糖果: " << sharecount << endl;
    
    vector<int> cointypes{ 1, 2, 5, 10, 20,50,100};
    vector<int> coincounts{10,0, 0, 1,  2, 0, 2};//2*100+20*2+10*1+1*2 = 7
    
    int ccount = coin_dispenser(cointypes, coincounts, 252);
    cout << "钱币找零: " << ccount << endl;
    
    vector<vector<int>> areas;
    areas.push_back({6,8});
    areas.push_back({2,4});
    areas.push_back({3,5});
    areas.push_back({1,5});
    areas.push_back({5,9});
    areas.push_back({8,10});
    cout << "区域覆盖：" << region_overlapping(areas) << endl;
    return 0;
}
