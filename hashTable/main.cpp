//
//  main.cpp
//  hasTable
//
//  Created by junl on 2019/7/20.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "hash_map.h"

class SampleHash {
public:
    size_t operator()(const int &s) const
    {
        return s % 3;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    hash_map<int, int, SampleHash> test;
    for (int i=0; i<20; i++) {
        test[i] = i;
    }
    std::cout << test[1] << ' ' << test[2] << std::endl;
    return 0;
}
