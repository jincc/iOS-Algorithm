//
//  IsContinuous2.h
//  other
//
//  Created by junl on 2020/1/13.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef IsContinuous2_hpp
#define IsContinuous2_hpp

#include <stdio.h>
#include <vector>

namespace codinginterviews {
    using namespace std;
    bool IsContinuous2( vector<int> numbers ) {
        sort(numbers.begin(), numbers.end());
        
        int offset = 0;
        int zerocount = numbers[0] == 0;
        for (int i=1;i < numbers.size();i++){
            if (numbers[i] == 0){
                zerocount++;
                continue;
            }
            if (numbers[i] == numbers[i-1]){
                return false;
            }
            offset += numbers[i] - numbers[i-1] - 1;
        }
        return offset <= zerocount ? true : false ;
    }
    
    void test_IsContinuous2(){
        vector<int> nums{1,3,4,6,0};
        cout << "-------test_IsContinuous2------" << endl;
        cout << IsContinuous2(nums) << endl;
    }
}

#endif /* IsContinuous2_hpp */
